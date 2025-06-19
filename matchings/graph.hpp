/*
* A class representing undirected graphs.
* The vertex set of such graphs is always of the form
* {0, ..., n - 1} where n is the number of vertices.
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>

class Graph {
  int n, m;
  
  public:
    std::vector<bool> part;
    std::vector<std::vector<int>> adj;

    /*
    * Initializes an empty graph on n vertices.
    */
    Graph(int);

    /*
    * Construct a graph from a file. The file must contain
    * the following information in the given order:abs
    * Number of vertices, number of edges, edges of the graph.
    * Example representation for the complete graph on 3 vertices:
    * 3
    * 3
    * 0 1
    * 0 2
    * 1 2
    */
    Graph(std::string);
    
    /*
    * Initializes a complete graph on n vertices.
    */
    int get_n() const {return n;}

    /*
    * Adds an edge to this, while checking whether the given vertices are valid.
    */
    void add_edge(int, int);

    /*
    * Adds an edge to this, not checking whether the given vertices are valid.
    */
    void add_edge_unchecked(int, int);
    bool is_bipartite();

    /*
    * Prints the given graph.
    */
    friend std::ostream& operator<<(std::ostream&, const Graph&);

    /*
    * Given two graphs, creates their disjoint union.
    */
    Graph operator+(const Graph&) const;

    void maximum_cardinality_matching(std::vector<int>&);

    static Graph complete(int);

    /*
    * Initializes a complete bipartite graph, where the bipartition sets
    * have sizes n and m respectively.
    */
    static Graph complete_bipartite(int, int);

    /*
    * Initializes a cycle on n vertices.
    */
    static Graph cycle(int);

    /*
    * Initializes a path on n vertices.
    */
    static Graph path(int);
};

#endif