#include "../graph.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

namespace matching_test {

void test_bipartite_complete();
void test_bipartite_1();
void test_bipartite_2();
void test_bipartite_folder();

std::vector<void(*)()> tests = {test_bipartite_complete, test_bipartite_1, test_bipartite_2, test_bipartite_folder};

/* 
* Given a matching represented as a mate map, returns its size.
*/
int matching_size(const std::vector<int>& mate) {
  int res = 0;
  for (int x: mate)
    if (x != -1)
      res++;
  
  assert(res % 2 == 0);
  return res / 2;
}

void print_matching(const std::vector<int>& mate) {
  int n = mate.size();
  std::cout << "Matching edges:\n";
  for (int i = 0; i < n; i++) {
    if (mate[i] > i) 
      std::cout << "{" << i << "," << mate[i] << "}\n"; 
  }
}

void test_bipartite_complete() {
  for (int i = 1; i < 15; i++)
    for (int j = 1; j < 15; j++) {
      Graph g = Graph::complete_bipartite(i, j);
      std::vector<int> mate(g.get_n(), -1);
      g.maximum_cardinality_matching(mate);

      assert(matching_size(mate) == std::min(i, j));
    }
}

void test_bipartite_1() {
  Graph g("graphs/1.txt");
  std::vector<int> mate(g.get_n(), -1);
  g.maximum_cardinality_matching(mate);

  assert(matching_size(mate) == 2);
  // print_matching(mate);
}

void test_bipartite_2() {
  Graph g("graphs/2.txt");
  std::vector<int> mate(g.get_n(), -1);
  g.maximum_cardinality_matching(mate);

  assert(matching_size(mate) == 2);
  // print_matching(mate);
}

void test_bipartite_folder() {
  std::ifstream keyfile("test/bipartite_matching_instances/key.txt");
  int n; keyfile >> n;
  for (int i = 0; i < n; i++) {
    int expected; keyfile >> expected;
    Graph g("test/bipartite_matching_instances/" + std::to_string(i) + ".txt");
    std::vector<int> mate(g.get_n(), -1);
    g.maximum_cardinality_matching(mate);

    assert(matching_size(mate) == expected);
  }
}

void test_all() {
  for (void (*f)() : tests)
    f();
  
  std::cout << "All tests passed." << std::endl;
}

}