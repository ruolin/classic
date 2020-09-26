#include <iostream>
#include "Graph.h"

int main() {
  std::cout << "Hello, World!" << std::endl;
  auto g = Graph::CreateSimpleGraph();
  g.TopologySort();
  return 0;
}

