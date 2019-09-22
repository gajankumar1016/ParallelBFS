#include "edge.h"

std::ostream& operator<<(std::ostream& out, const Edge &edge)
{
  out << edge.src << "--(" << edge.weight << ")->" << edge.dest << std::endl;
  return out;
}
