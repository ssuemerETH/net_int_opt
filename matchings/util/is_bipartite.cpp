#include "../graph.hpp"
#include <deque>

/*
* Given a graph, returns true if and only if it is bipartite.
* In this case, also populates the part vector with booleans that
* denote the bipartition. (true and false denoting the two classes)
*/
bool Graph::is_bipartite() {
  // vertices discovered during BFS
  part = std::vector<bool>(n, false);
  std::vector<bool> discovered(n, false);
  
  for (int r = 0; r < n; r++) {
    if (!discovered[r]) {
      std::deque<int> q = {r};
      part[r] = true;
      discovered[r] = true;

      while (!q.empty()) {
        int v = q.front();
        q.pop_front();
        for (int w: adj[v]) {
          if (!discovered[w]) {
            q.push_back(w);
            part[w] = !part[v];
            discovered[w] = true;
          }
        }
      }
    }
  }

  for (int u = 0; u < n; u++) 
    for (int v: adj[u]) 
      if (part[u] == part[v])
        return false;
  return true;
}