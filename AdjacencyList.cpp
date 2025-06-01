// ronavraham99@gmail.com

#include "AdjacencyList.hpp"
#include <iostream> 

namespace graph {

/**
 * @class AdjacencyList
 * @brief Represents a singly linked adjacency list for graph edges.
 * 
 * Each node in the list stores the destination vertex and the edge weight.
 * Provides methods to add, remove, and query edges.
 */
AdjacencyList::AdjacencyList() {
    head = nullptr; ///< Initialize head pointer to null (empty list).
}

AdjacencyList::~AdjacencyList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;       ///< Save pointer before moving to next node.
        current = current->next;    ///< Advance iterator.
        delete temp;                ///< Free memory to avoid leaks.
    }
}

/**
 * @brief Add a new edge to the adjacency list.
 * @param dest Destination vertex.
 * @param weight Weight of the edge.
 */
void AdjacencyList::addEdge(int dest, int weight) {
    Node* newNode = new Node(dest, weight, head); ///< Insert at the beginning.
    head = newNode;
}

/**
 * @brief Remove an edge with the given destination.
 * @param dest Destination vertex to remove.
 * @throws const char* if the edge is not found.
 */
void AdjacencyList::removeEdge(int dest) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->dest == dest) {
            if (prev == nullptr) {
                head = current->next;   ///< Edge is the first node.
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }

    throw "Edge not found"; ///< No matching edge in list.
}

/**
 * @brief Check if an edge to the given destination exists.
 * @param dest Destination vertex to search for.
 * @return True if found, false otherwise.
 */
bool AdjacencyList::contains(int dest) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->dest == dest) {
            return true;
        }
        current = current->next;
    }
    return false;
}

/**
 * @brief Print all edges in the adjacency list.
 * 
 * Format: (destination, weight)
 */
void AdjacencyList::print() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "(" << current->dest << ", weight " << current->weight << ") ";
        current = current->next;
    }
}

/**
 * @brief Count the number of edges in the adjacency list.
 * @return Number of nodes in the list.
 */
int AdjacencyList::count() const {
    int c = 0;
    Node* current = head;
    while (current != nullptr) {
        ++c;                  ///< Increment for each node.
        current = current->next;
    }
    return c;
}

/**
 * @brief Get all neighbor vertices from the adjacency list.
 * @return Dynamically allocated array of neighbor IDs.
 * @note Caller is responsible for freeing the returned array.
 */
int* AdjacencyList::getAllNeighbors() const {
    int c = count();
    int* neighbors = new int[c];
    Node* current = head;
    int i = 0;
    while (current != nullptr) {
        neighbors[i++] = current->dest;
        current = current->next;
    }
    return neighbors;
}

/**
 * @brief Retrieve the weight of an edge to a given destination.
 * @param dest Destination vertex.
 * @return Edge weight if found, otherwise -1.
 */
int AdjacencyList::getWeight(int dest) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->dest == dest)
            return current->weight;
        current = current->next;
    }
    return -1; ///< Indicates no such edge exists.
}

} // namespace graph
