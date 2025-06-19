#include "../graph.hpp"
#include <iostream>
#include <cassert>

namespace bipartite_test {

void test_bipartite_easy();

std::vector<void(*)()> tests = {test_bipartite_easy};

void test_bipartite_easy() {
  Graph g = Graph::complete_bipartite(3, 12);
  assert(g.is_bipartite());

  g = Graph::cycle(20000);
  assert(g.is_bipartite());

  g = Graph::complete(4);
  assert(!g.is_bipartite());

  g = Graph::path(12);
  assert(g.is_bipartite());

  g = Graph("graphs/0.txt");
  assert(!g.is_bipartite());

  g = Graph("graphs/1.txt");
  assert(g.is_bipartite());

  Graph g1 = Graph::complete_bipartite(12, 11);
  Graph g2 = Graph::complete_bipartite(2, 5);
  Graph g3 = Graph::cycle(13);

  g = g1 + g2 + g3;
  assert(!g.is_bipartite());

  std::cout << "All tests passed." << std::endl;
}

void test_all() {
  for (void (*f)() : tests)
    f();
}

}