// ronavraham99@gmail.com

#include "Graph.hpp"
#include <iostream>
#include <stdexcept> 

namespace graph {

/**
 * @brief Construct a new Graph with a given number of vertices.
 * 
 * Initializes an array of adjacency lists.
 * @param vertices Number of vertices in the graph.
 */
Graph::Graph(int vertices) {
    num_of_vertices = vertices;
    adjacency_vertices = new AdjacencyList[num_of_vertices]; ///< Create adjacency lists.
}

/// Destructor – releases adjacency list array.
Graph::~Graph() {
    delete[] adjacency_vertices; 
}

/**
 * @brief Add an undirected weighted edge between two vertices.
 * @param src Source vertex.
 * @param dest Destination vertex.
 * @param weight Weight of the edge.
 * @note Does nothing if vertices are invalid.
 */
void Graph::addEdge(int src, int dest, int weight) {
    if (src < 0 || dest < 0 || src >= num_of_vertices || dest >= num_of_vertices) {
        std::cout << "Invalid edge!" << std::endl;
        return;
    }

    adjacency_vertices[src].addEdge(dest, weight);
    adjacency_vertices[dest].addEdge(src, weight); ///< Because the graph is undirected.
}

/**
 * @brief Remove an undirected edge between two vertices.
 * @param src Source vertex.
 * @param dest Destination vertex.
 * @throws std::runtime_error If the edge does not exist.
 */
void Graph::removeEdge(int src, int dest) { 
    if (src < 0 || dest < 0 || src >= num_of_vertices || dest >= num_of_vertices) {
        std::cout << "Invalid edge!" << std::endl;
        return;
    }

    if (!adjacency_vertices[src].contains(dest)) {
        throw std::runtime_error("The edge does not exist and cannot be removed");
    }

    adjacency_vertices[src].removeEdge(dest);
    adjacency_vertices[dest].removeEdge(src); ///< Remove both directions.
}

/**
 * @brief Print the entire graph.
 * 
 * Displays each vertex followed by its adjacency list.
 */
void Graph::print_graph() const {
    for (int i = 0; i < num_of_vertices; ++i) {
        std::cout << "vertex " << i << ": ";
        adjacency_vertices[i].print();  
        std::cout << std::endl;
    }
}

/// @return Number of vertices in the graph.
int Graph::getNumVertices() const {
    return num_of_vertices;
}

/**
 * @brief Get the number of neighbors for a given vertex.
 * @param vertex Vertex index.
 * @return Number of neighbors, or 0 if invalid vertex.
 */
int Graph::getNeighborCount(int vertex) const {
    if (vertex < 0 || vertex >= num_of_vertices) return 0;
    return adjacency_vertices[vertex].count();
}

/**
 * @brief Get all neighbors of a vertex.
 * @param vertex Vertex index.
 * @return Dynamically allocated array of neighbors, or nullptr if invalid.
 * @note Caller is responsible for freeing the array.
 */
int* Graph::getNeighbors(int vertex) const {
    if (vertex < 0 || vertex >= num_of_vertices) return nullptr;
    return adjacency_vertices[vertex].getAllNeighbors();
}

/**
 * @brief Get the weight of an edge between two vertices.
 * @param src Source vertex.
 * @param dest Destination vertex.
 * @return Edge weight, or -1 if invalid or edge not found.
 */
int Graph::getEdgeWeight(int src, int dest) const {
    if (src < 0 || dest < 0 || src >= num_of_vertices || dest >= num_of_vertices)
        return -1;
    return adjacency_vertices[src].getWeight(dest);
}

/**
 * @brief Check if an edge exists between two vertices.
 * @param src Source vertex.
 * @param dest Destination vertex.
 * @return True if the edge exists, false otherwise.
 */
bool Graph::containsEdge(int src, int dest) const {
    if (src < 0 || dest < 0 || src >= num_of_vertices || dest >= num_of_vertices) {
        return false;
    }
    return adjacency_vertices[src].contains(dest);
}

/**
 * @brief Count the total number of edges in the graph.
 * @return Number of undirected edges.
 */
int Graph::countEdges() const {
    int total = 0;
    for (int i = 0; i < num_of_vertices; ++i) {
        Node* current = adjacency_vertices[i].getHead();
        while (current != nullptr) {
            total++;
            current = current->next;
        }
    }
    return total / 2; ///< Divide by 2 since the graph is undirected.
}

} // namespace graph
