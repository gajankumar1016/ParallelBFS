//
// Created by foobar on 7/11/19.
//

#ifndef PARALLELBFS_EDGE_H
#define PARALLELBFS_EDGE_H


#include <string>
#include <iostream>

using std::string;

typedef long Vertex;

class Edge {
 public:
  Vertex src;
  Vertex dest;
  double weight;
  //friend std::ostream &operator<<(std::ostream &out, const Edge &edge);

  Edge(Vertex v1, Vertex v2, double weight=-1, string label=""): src(v1), dest(v2), weight(weight), label(label) {};
  void setWeight(double weight) {
    this->weight = weight;
  }

 private:
  string label;
};

std::ostream& operator<<(std::ostream& out, const Edge &edge);

//TODO: perhaps subclass Edge with weighted edge

#endif //PARALLELBFS_EDGE_H
