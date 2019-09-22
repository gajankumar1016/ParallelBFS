//
// Created by foobar on 9/21/19.
//

#ifndef PARALLELBFS_BFSMULTITHREADED_H
#define PARALLELBFS_BFSMULTITHREADED_H

#include "graph.h"
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

class BFSMultithreaded {
 public:
  BFSMultithreaded(const Graph& g, Vertex src, size_t num_threads);
  ~BFSMultithreaded();
  bool hasPathTo(Vertex dest);
  std::vector<Vertex> pathTo(Vertex dest);

 private:
  Vertex _src;
  std::vector<bool> visited;
  std::vector<Vertex> edgeTo;

  std::atomic<bool> stop_th;
  std::mutex g_lock_print;
  std::mutex g_lockbatch;
  std::condition_variable g_nextbatch;

  std::mutex next_level_lock;

  size_t _num_threads;
  std::vector<std::mutex> *mtxes = nullptr;
  std::vector<std::vector<Vertex>> frontier_partition;
  std::vector<Vertex> next_level;

  void performMultithreadedBFS(const Graph& g, Vertex src);
  size_t partition_vertices();


  friend class BFSThread;

};

class barrier
{
  unsigned const count;
  std::atomic<unsigned> spaces;
  std::atomic<unsigned> generation;

 public:
  explicit barrier(unsigned count_) :
      count(count_), spaces(count), generation(0) {}

  void wait()
  {
    unsigned const my_generation = generation;
    if (!--spaces)
    {
      spaces = count;
      ++generation;
    }
    else
    {
      while (generation == my_generation)
        std::this_thread::yield();
    }
  }
};

class BFSThread {
 private:
  int _id;
  std::thread _th;
  BFSMultithreaded *_bfs_context;
  std::atomic<bool> _next_batch;

 public:
  //TODO: what does _th() do?
  BFSThread(int id, BFSMultithreaded *bfs_context) : _id(id), _next_batch(false),_bfs_context(bfs_context){};
  void process_frontier_batch() {_next_batch = true;}
  void start(const Graph &g, barrier& b) {
    _th = std::thread(&BFSThread::run, this, std::ref(g), std::ref(b));
  }

  void stop() {
    this->_bfs_context->stop_th = true;
  }
  void wait_until_stopped() {
    _th.join();
  }

  void run(const Graph &g, barrier& b) {
    while (!_bfs_context->stop_th) {
      {
        std::unique_lock<std::mutex> lk(_bfs_context->g_lockbatch);
        _bfs_context->g_nextbatch.wait(lk, [&](){return _next_batch == true;});
      }

//      {
//        std::unique_lock<std::mutex> locker(_bfs_context->g_lock_print);
//        std::cout << "[bfs_thread " << _id << " running]" << std::endl;
//      }

        if (_bfs_context->stop_th) return;

      //Update frontier
      for (const auto &curr_vertex : _bfs_context->frontier_partition[_id]) {
        for (const Vertex& v : g.getAdjacent(curr_vertex)) {
          if (!_bfs_context->visited[v]) {
            _bfs_context->visited[v] = true;
            _bfs_context->edgeTo[v] = curr_vertex;

            _bfs_context->next_level_lock.lock();
            _bfs_context->next_level.push_back(v);
            _bfs_context->next_level_lock.unlock();
          }
        }
      }

      _next_batch = false;
      b.wait();
    }

  }
};
#endif //PARALLELBFS_BFSMULTITHREADED_H
