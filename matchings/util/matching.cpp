#include "../graph.hpp"
#include <cassert>
#include <deque>
#include <algorithm>

bool augmenting_bipartite(const Graph&, const std::vector<int>&, std::vector<int>&);
bool augmenting_non_bipartite(const Graph&, const std::vector<int>&, std::vector<int>&);
void augment(const std::vector<int>&, std::vector<int>&);

/*
* Given a graph, returns a maximum cardinality matching in it.
*/
void Graph::maximum_cardinality_matching(std::vector<int>& mate) {
  bool (*aug)(const Graph&, const std::vector<int>&, std::vector<int>&) = is_bipartite() ? augmenting_bipartite : augmenting_non_bipartite;

  std::vector<int> a_path;
  while(aug(*this, mate, a_path)) {
    augment(a_path, mate);
    a_path.clear();
  }
}

/*
* Finds an augmenting path in a given bipartite graph.
*/
bool augmenting_bipartite(const Graph& g, const std::vector<int>& mate, std::vector<int>& res) {
  std::deque<int> q;
  int n = g.get_n();
  for (int i = 0; i < n; i++) 
    if (g.part[i] && mate[i] == -1)
      q.push_back(i);   

  // q contains all exposed vertices in X
  // -1: root, -2: undiscovered
  std::vector<int> pred(n, -2);
  for (int x: q)
    pred[x] = -1;
  
  while (!q.empty()) {
    int v = q.front();
    q.pop_front();
    if (g.part[v]) {
      for (int w: g.adj[v]) 
        if (mate[v] != w && pred[w] == -2) {
          pred[w] = v;
          q.push_back(w);
        }
    } else if (mate[v] != -1) {
      int w = mate[v];
      if (pred[w] == -2) {
        pred[w] = v;
        q.push_back(w);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (pred[i] > -2 && !g.part[i] && mate[i] == -1) {
      int cur = i;
      while (cur != -1) {
        res.push_back(cur);
        cur = pred[cur];
      }

      std::reverse(res.begin(), res.end());
      return true;
    }
  }

  return false;
}

/*
* Finds an augmenting path in a given graph.
*/
bool augmenting_non_bipartite(const Graph& g, const std::vector<int>& mate, std::vector<int>& res) {
  return false;
}

/*
* Given a matching and a path augmenting this matching, augments the matching.
*/
void augment(const std::vector<int>& path, std::vector<int>& mate) {
  int k = path.size();
  assert(k % 2 == 0);
  for (int i = 0; i < k; i += 2) {
    int u = path[i];
    int v = path[i + 1];
    mate[u] = v;
    mate[v] = u;
  } 
}