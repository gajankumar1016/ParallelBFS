#include "bfsmultithreaded.h"
#include <stack>
//https://stackoverflow.com/questions/32986572/c-main-thread-notifying-threads-notifying-main-thread


BFSMultithreaded::BFSMultithreaded(const Graph &g, Vertex src, size_t num_threads) {
  this->_src = src;
  this->_num_threads = num_threads;
  this->stop_th = false;
  visited.resize(g.size(), false);
  edgeTo.resize(g.size(), -1);
  mtxes = new std::vector<std::mutex>(g.size());
  frontier_partition.resize(num_threads, std::vector<Vertex>());
  performMultithreadedBFS(g, src);
}

BFSMultithreaded::~BFSMultithreaded() {
  delete mtxes;
  mtxes = nullptr;
}

size_t BFSMultithreaded::partition_vertices() {
  for (size_t i = 0; i < this->next_level.size(); i++) {
    size_t idx = i % _num_threads;
    frontier_partition[idx].push_back(next_level[i]);
  }

  size_t retval = this->next_level.size();
  this->next_level.clear();
  return retval;
}

void BFSMultithreaded::performMultithreadedBFS(const Graph &g, Vertex src) {

  barrier b(static_cast<unsigned int>(_num_threads) + 1);

  std::vector<BFSThread*> bfsthreads;
  bfsthreads.reserve(_num_threads);
  for (int i = 0; i < _num_threads; i++) {
    bfsthreads.push_back(new BFSThread(i, this));
  }

  for (auto &bt : bfsthreads) {
    bt->start(g, b);
  }

  visited[src] = true;
  this->next_level.push_back(src);
  size_t batch_size = partition_vertices();
  while (batch_size > 0) {
    //Partition vertices
    for (auto &bt : bfsthreads) bt->process_frontier_batch();
    g_nextbatch.notify_all();

    //wait until all threads have finish their batch
    b.wait();

    //Prepare next BFS batch
    batch_size = partition_vertices();
    next_level.clear();
  }

  //TODO: possible race condition?
  this->stop_th = true;
  for (auto &bfst : bfsthreads) {
    bfst->stop();
  }

  for (auto &bt : bfsthreads) bt->process_frontier_batch();
  g_nextbatch.notify_all();

  for (auto &bfst : bfsthreads) {
    bfst->wait_until_stopped();
  }
  for (auto &th : bfsthreads) {
    delete th;
    th = nullptr;
  }
}

bool BFSMultithreaded::hasPathTo(Vertex dest) {
  return visited[dest];
}


vector<Vertex> BFSMultithreaded::pathTo(Vertex dest) {
  if (!hasPathTo(dest)) {
    return vector<Vertex>{};
  }

  std::stack<Vertex> s;
  for (Vertex v = dest; v != this->_src; v = edgeTo[v]) {
    s.push(v);
  }

  s.push(this->_src);

  vector<Vertex> pathTo;
  while (!s.empty()) {
    pathTo.push_back(s.top());
    s.pop();
  }

  return pathTo;
}
