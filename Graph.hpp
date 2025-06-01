// ronavraham99@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "AdjacencyList.hpp"

namespace graph {

/**
 * @class Graph
 * @brief Undirected weighted graph implemented using adjacency lists.
 * 
 * Each vertex has an adjacency list storing its neighbors
 * and the weights of the connecting edges.
 */
class Graph {
private:
    int num_of_vertices;             ///< Number of vertices in the graph.
    AdjacencyList* adjacency_vertices; ///< Array of adjacency lists.

public:
  
    Graph(int vertices);
    ~Graph();

    void addEdge(int src, int dest, int weight = 1);
    void removeEdge(int src, int dest);
    void print_graph() const;
    int getNumVertices() const;
    int getNeighborCount(int vertex) const;
    int* getNeighbors(int vertex) const;
    int getEdgeWeight(int src, int dest) const;
    bool containsEdge(int src, int dest) const;
    int countEdges() const;
};

} // namespace graph

#endif // GRAPH_HPP
