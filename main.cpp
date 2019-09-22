#include <iostream>
#include <vector>
#include <chrono>
#include "src/graph.h"
#include "src/randomgraphgenerator.h"
#include "src/bfs.h"
#include "src/bfsmultithreaded.h"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;


void test_graph(const Graph &g) {
  //warmup
  BFS bfs_warmup(g, 0);

  const auto start_time = high_resolution_clock::now();
  BFS bfs(g, 0);
  const auto end_time = high_resolution_clock::now();
  const auto total_time = duration_cast<duration<double, milli>>(end_time - start_time).count();
  std::cout << "Total time for serial bfs: " << total_time << "ms" << std::endl;;

  if (bfs.hasPathTo(1000)) {
    vector<Vertex> path = bfs.pathTo(1000);
    for (const auto &v : path) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }

  size_t num_threads = 15;
  const auto start_time_mt = high_resolution_clock::now();
  BFSMultithreaded bfsMultithreaded(g, 0, num_threads);
  const auto end_time_mt = high_resolution_clock::now();
  const auto total_time_mt = duration_cast<duration<double, milli>>(end_time_mt - start_time_mt).count();
  std::cout << "Total time for bfs multithreaded (" << num_threads << " threads) " << total_time_mt << "ms" << std::endl;;

  if (bfsMultithreaded.hasPathTo(1000)) {
    vector<Vertex> path = bfsMultithreaded.pathTo(1000);
    for (const auto &v : path) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
}


int main() {
  RandomGraphGenerator rg(2000, 0.15);
  Graph *g = rg.generateGraph();
  test_graph(*g);
  delete g;
  return 0;
}