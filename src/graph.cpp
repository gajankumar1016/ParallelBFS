#include "graph.h"
#include <limits>

const Vertex Graph::INVALID_VERTEX = INT32_MIN;
const double Graph::INVALID_WEIGHT = std::numeric_limits<double>::lowest();
const Edge Graph::INVALID_EDGE = Edge(INVALID_VERTEX, INVALID_VERTEX, INVALID_WEIGHT);

Graph::Graph(unsigned long size, bool directed, bool weighted) {
  this->numVertices = size;
  this->directed = directed;
  this->weighted = weighted;
  adjList.resize(size, vector<Edge>());
}

unsigned long Graph::size() const {
  return this->numVertices;
}

vector<Vertex> Graph::getAllVertices() const {
  vector<Vertex> vertices;
  vertices.reserve(adjList.size());
  for (int i = 0; i < adjList.size(); i++) {
    vertices.push_back(i);
  }
  return vertices;
}

vector<Vertex> Graph::getAdjacent(Vertex src) const {
  vector<Edge> adjEdges = adjList[src];
  vector<Vertex> neighbors;
  neighbors.reserve(adjEdges.size());
  for (auto &adjEdge : adjEdges) {
    neighbors.push_back(adjEdge.dest);
  }

  return neighbors;
}

void Graph::insertEdge(Vertex v1, Vertex v2) {
  adjList[v1].push_back(Edge(v1, v2));
  if (!this->directed) {
    adjList[v2].push_back(Edge(v2, v1));
  }
}

void Graph::setEdgeWeight(Vertex v1, Vertex v2, double weight) {
  Edge &e1 = findEdge(adjList[v1], v2);
  e1.setWeight(weight);

  if (!this->directed) {
    Edge &e2 = findEdge(adjList[v2], v1);
    e2.setWeight(weight);
  }
}

double Graph::getEdgeWeight(Vertex v1, Vertex v2) const {
  for (auto e : adjList[v1]) {
    if (e.dest == v2) {
      return e.weight;
    }
  }

  return -1;
}

Edge& Graph::findEdge(vector<Edge> &neighbors, Vertex dest) {
  for (auto &n: neighbors) {
    if (n.dest == dest) {
      return n;
    }
  }
  //TODO: throw an exception
}

std::ostream& operator<<(std::ostream &out, Graph const &graph) {
  vector<Vertex> vertices = graph.getAllVertices();
  for (auto &v: vertices) {
    vector<Edge> edgesToNeigbors = graph.adjList[v];
    std::cout << "Vertex " << v << ": ";
    for (auto &e: edgesToNeigbors) {
      std::cout << "(" << e.src << "," << e.dest << "," << e.weight << "), ";
    }
    std::cout << "NULL" << std::endl;
  }

  return out;
}