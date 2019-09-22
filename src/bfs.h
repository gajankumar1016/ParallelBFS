#ifndef PARALLELBFS_BFS_H
#define PARALLELBFS_BFS_H

#include "graph.h"

class BFS {
 public:
  BFS(const Graph& g, Vertex src);
  bool hasPathTo(Vertex dest);
  std::vector<Vertex> pathTo(Vertex dest);

 private:
  Vertex _src;
  std::vector<bool> visited;
  std::vector<Vertex> edgeTo;
  void performBFS(const Graph& g, Vertex src);
};

#endif // PARALLELBFS_BFS_H
