#include "randomgraphgenerator.h"
#include <random>

Graph* RandomGraphGenerator::generateGraph() {
  std::random_device rd; //Used to seed random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<double> dis(0.0, 1.0);

  auto *g = new Graph(this->_num_vertices);

  for (unsigned long i = 0; i < _num_vertices; i++) {
    for (unsigned long j = 0; j < _num_vertices; j++) {
      if (i >= j) {
        continue;
      }

      double rand_num = dis(gen);
      bool should_add_edge = rand_num < _density;

      if (should_add_edge) {
        g->insertEdge(i, j);
      }

    }
  }

  return g;
}
