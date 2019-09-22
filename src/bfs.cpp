#include "bfs.h"
#include <queue>
#include <stack>

BFS::BFS(const Graph &g, Vertex src) {
  this->_src = src;
  visited.resize(g.size(), false);
  edgeTo.resize(g.size(), -1);
  performBFS(g, src);
}

void BFS::performBFS(const Graph &g, Vertex src) {
  auto curr_level = new std::vector<Vertex>();
  auto next_level = new std::vector<Vertex>();

  curr_level->push_back(src);
  visited[src] = true;
  while (!curr_level->empty()) {
    for (const auto & curr_vertex : *curr_level) {
      for (const Vertex& v : g.getAdjacent(curr_vertex)) {
        if (!visited[v]) {
          visited[v] = true;
          next_level->push_back(v);
          edgeTo[v] = curr_vertex;
        }
      }
    }

    delete curr_level;
    curr_level = next_level;
    next_level = new std::vector<Vertex>();
  }

  delete curr_level;
  delete next_level;
}

bool BFS::hasPathTo(Vertex dest) {
  return visited[dest];
}


vector<Vertex> BFS::pathTo(Vertex dest) {
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



