// ronavraham99@gmail.com

#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

namespace graph {
    
/**
 * @struct Node
 * @brief Represents a single node in the adjacency list.
 * 
 * Each node stores the destination vertex, the edge weight,
 * and a pointer to the next node in the list.
 */
struct Node {
    int dest; ///< Destination vertex.
    int weight;//< Weight of the edge.
    Node* next;//< Pointer to the next node.

  
    Node(int d, int w, Node* n = nullptr) 
        : dest(d), weight(w), next(n) {} 
};
class AdjacencyList {
private:
    Node* head;  ///< Pointer to the first node (start of the list).

public:
    AdjacencyList();  ///< Constructor
    ~AdjacencyList();  ///< Destructor
    
    void addEdge(int dest, int weight);   
    void removeEdge(int dest);            
    bool contains(int dest) const;       
    void print() const;
    int count() const;
    int* getAllNeighbors() const;
    int getWeight(int dest) const;
    Node* getHead() const {return head;}

                   
};

}

#endif
