#ifndef PARALLELBFS_GRAPH_H
#define PARALLELBFS_GRAPH_H

#include <vector>
#include <iostream>
#include "edge.h"

using std::vector;


class Graph {
 public:
  // explicit Graph(int size=0, bool directed=false, bool weighted=false): numVertices(size), directed(directed), weighted(weighted) {};
  explicit Graph(unsigned long size = 0, bool directed=false, bool weighted=false);
  vector<Vertex> getAdjacent(Vertex src) const;
  void insertEdge(Vertex v1, Vertex v2);
  void setEdgeWeight(Vertex v1, Vertex v2, double weight);
  double getEdgeWeight(Vertex v1, Vertex v2) const;
  vector<Vertex> getAllVertices() const;
  unsigned long size() const;

  const static Vertex INVALID_VERTEX;
  const static double INVALID_WEIGHT;
  const static Edge INVALID_EDGE;
  const static unsigned long MAX_VERTICES = 1000;

 private:
  friend std::ostream& operator<<(std::ostream& out, Graph const &graph);
  bool directed;
  bool weighted;
  unsigned long numVertices;
  vector<vector<Edge>> adjList;
  Edge& findEdge(vector<Edge> &neighbors, Vertex dest);
};


#endif //PARALLELBFS_GRAPH_H
