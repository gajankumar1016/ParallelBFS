#ifndef PARALLELBFS_RANDOMGRAPHGENERATOR_H
#define PARALLELBFS_RANDOMGRAPHGENERATOR_H

#include "graph.h"

class RandomGraphGenerator {
 public:
  RandomGraphGenerator(unsigned long num_vertices, float density): _num_vertices(num_vertices), _density(density){};
  Graph *generateGraph();

 private:
  unsigned long _num_vertices;
  float _density;

};

#endif //PARALLELBFS_RANDOMGRAPHGENERATOR_H
