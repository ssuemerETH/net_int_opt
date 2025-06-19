#include "graph.hpp"

#include <fstream>
#include <iostream>
#include <cassert>

Graph::Graph(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file " << filename << "." << std::endl;
    std::abort();
  }

  int M;
  file >> n >> M;
  adj = std::vector<std::vector<int>>(n, std::vector<int>());
  
  for (int i = 0; i < M; i++) {
    int u, v; file >> u >> v;
    add_edge(u, v);
  }
}

Graph::Graph(int n) : n(n), m(0) {
  adj = std::vector<std::vector<int>>(n, std::vector<int>());
};

Graph Graph::complete(int n) {
  Graph res(n);
  for (int i = 0; i < n; i++) 
    for (int j = i + 1; j < n; j++)
      res.add_edge_unchecked(i, j);

  return res;
}

Graph Graph::complete_bipartite(int n, int m) {
  Graph res(n + m);
  for (int i = 0; i < n; i++) 
    for (int j = n; j < n + m; j++)
      res.add_edge_unchecked(i, j);
  
  return res;
}

Graph Graph::cycle(int n) {
  Graph res = Graph::path(n);
  res.add_edge_unchecked(0, n - 1);
  return res;
}

Graph Graph::path(int n) {
  Graph res(n);
  for (int i = 0; i < n - 1; i++)
    res.add_edge_unchecked(i, i + 1);
  return res;
}

void Graph::add_edge_unchecked(int u, int v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
  m++;
}

void Graph::add_edge(int u, int v) {
  assert(u >= 0 && u < n);
  assert(v >= 0 && v < n);
  assert(u != v);
  add_edge_unchecked(u, v);
}

std::ostream& operator<<(std::ostream& out, const Graph& p) {
  out << p.n << " vertices and " << p.m << " edges." << std::endl;
  for (int i = 0; i < p.n; i++) {
    out << "Neighborhood of vertex " << i << ": ";
    for (const int& x: p.adj[i])
      out << x << " ";
    out << std::endl;
  }

  return out;
}

Graph Graph::operator+(const Graph& other) const {
  Graph res(n + other.n);
  for (int u = 0; u < n; u++) 
    for (int v: adj[u])
      res.add_edge_unchecked(u, v);
  
  for (int u = 0; u < other.n; u++)
    for (int v: other.adj[u])
      res.add_edge_unchecked(u + n, v + n);
  
  return res;
}