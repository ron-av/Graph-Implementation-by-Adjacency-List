// ronavraham99@gmail.com

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>

using namespace graph;

/**
 * @brief Entry point of the program.
 * 
 * Demonstrates the usage of the Graph class and Algorithms:
 *  - Builds a sample undirected weighted graph.
 *  - Prints the original graph.
 *  - Runs BFS, DFS, Dijkstra, Prim, and Kruskal.
 *  - Prints the resulting spanning/shortest-path trees.
 */
int main() {
    Graph g(6);

    // Build sample graph
    g.addEdge(0, 1, 7);
    g.addEdge(0, 2);
    g.addEdge(0, 5, 14);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 11);
    g.addEdge(2, 5, 2);
    g.addEdge(3, 4, 6);
    g.addEdge(4, 5, 9);

    std::cout << "--- Original Graph ---\n";
    g.print_graph();

    // BFS
    std::cout << "\n--- BFS Tree (from vertex 0) ---\n";
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();

    // DFS
    std::cout << "\n--- DFS Tree (from vertex 0) ---\n";
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();

    // Dijkstra
    std::cout << "\n--- Dijkstra Tree (from vertex 0) ---\n";
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    dijkstraTree.print_graph();

    // Prim
    std::cout << "\n--- Prim MST ---\n";
    Graph primTree = Algorithms::prim(g);
    primTree.print_graph();

    // Kruskal
    std::cout << "\n--- Kruskal MST ---\n";
    Graph kruskalTree = Algorithms::kruskal(g);
    kruskalTree.print_graph();

    return 0;
}
