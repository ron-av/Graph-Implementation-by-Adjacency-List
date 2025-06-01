// ronavraham99@gmail.com

#include "Algorithms.hpp"
#include "Graph.hpp"
#include "DataStructures.hpp"

namespace graph {

/**
 * @brief Breadth-First Search (BFS).
 * 
 * Constructs a BFS tree starting from a given vertex.
 * @param g Input graph.
 * @param start Starting vertex.
 * @return Graph representing the BFS tree.
 */
Graph Algorithms::bfs(const Graph& g, int start) {
    int n = g.getNumVertices();
    Graph tree(n);

    bool* visited = new bool[n];     ///< Track visited vertices.
    for (int i = 0; i < n; ++i) visited[i] = false;

    Queue q(n);
    visited[start] = true;
    q.enqueue(start);

    while (!q.isEmpty()) {
        int u = q.dequeue();

        int neighborCount = g.getNeighborCount(u);
        int* neighbors = g.getNeighbors(u);

        for (int i = 0; i < neighborCount; ++i) {
            int v = neighbors[i];
            if (!visited[v]) {
                visited[v] = true;
                tree.addEdge(u, v, g.getEdgeWeight(u, v)); ///< Record BFS tree edge.
                q.enqueue(v);
            }
        }
        delete[] neighbors;
    }

    delete[] visited;
    return tree;
}

/**
 * @brief Depth-First Search (DFS) recursive helper.
 * @param g Input graph.
 * @param u Current vertex.
 * @param visited Boolean array tracking visited vertices.
 * @param tree Graph representing the DFS tree being built.
 */
void dfsHelper(const Graph& g, int u, bool* visited, Graph& tree) {
    visited[u] = true;
    int count = g.getNeighborCount(u);
    int* neighbors = g.getNeighbors(u);

    for (int i = 0; i < count; ++i) {
        int v = neighbors[i];
        if (!visited[v]) {
            tree.addEdge(u, v, g.getEdgeWeight(u, v)); ///< Record DFS tree edge.
            dfsHelper(g, v, visited, tree);
        }
    }
    delete[] neighbors;
}

/**
 * @brief Depth-First Search (DFS).
 * 
 * Constructs a DFS tree starting from a given vertex.
 * @param g Input graph.
 * @param start Starting vertex.
 * @return Graph representing the DFS tree.
 */
Graph Algorithms::dfs(const Graph& g, int start) {
    int n = g.getNumVertices();
    Graph tree(n);
    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) visited[i] = false;

    dfsHelper(g, start, visited, tree);

    delete[] visited;
    return tree;
}

/**
 * @brief Dijkstra's algorithm.
 * 
 * Computes shortest paths from a start vertex to all others.
 * Returns a shortest-path tree.
 * @param g Input weighted graph.
 * @param start Source vertex.
 * @return Graph representing the shortest-path tree.
 */
Graph Algorithms::dijkstra(const Graph& g, int start) {
    int n = g.getNumVertices();
    Graph tree(n);

    bool* visited = new bool[n];
    int* dist = new int[n];   ///< Distance estimates.
    int* prev = new int[n];   ///< Predecessor array.

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        dist[i] = 1e9;        ///< Initialize with "infinity".
        prev[i] = -1;
    }
    dist[start] = 0;

    PriorityQueue pq(n);
    pq.insert(start, 0);

    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        if (visited[u]) continue;
        visited[u] = true;

        int count = g.getNeighborCount(u);
        int* neighbors = g.getNeighbors(u);

        for (int i = 0; i < count; ++i) {
            int v = neighbors[i];
            int w = g.getEdgeWeight(u, v);
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.insert(v, dist[v]);
            }
        }
        delete[] neighbors;
    }

    // Build shortest-path tree
    for (int v = 0; v < n; ++v) {
        if (prev[v] != -1)
            tree.addEdge(v, prev[v], g.getEdgeWeight(v, prev[v]));
    }

    delete[] visited;
    delete[] dist;
    delete[] prev;
    return tree;
}

/**
 * @brief Prim's algorithm.
 * 
 * Computes a Minimum Spanning Tree (MST).
 * @param g Input weighted graph.
 * @return Graph representing the MST.
 */
Graph Algorithms::prim(const Graph& g) {
    int n = g.getNumVertices();
    Graph tree(n);

    bool* inMST = new bool[n];
    int* key = new int[n];     ///< Minimum edge weight to connect a vertex.
    int* parent = new int[n];  ///< Store MST parent.

    for (int i = 0; i < n; ++i) {
        inMST[i] = false;
        key[i] = 1e9;
        parent[i] = -1;
    }

    key[0] = 0;
    PriorityQueue pq(n);
    pq.insert(0, 0);

    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        inMST[u] = true;

        int count = g.getNeighborCount(u);
        int* neighbors = g.getNeighbors(u);

        for (int i = 0; i < count; ++i) {
            int v = neighbors[i];
            int w = g.getEdgeWeight(u, v);
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.insert(v, key[v]);
            }
        }
        delete[] neighbors;
    }

    // Build MST edges
    for (int i = 1; i < n; ++i) {
        if (parent[i] != -1)
            tree.addEdge(i, parent[i], g.getEdgeWeight(i, parent[i]));
    }

    delete[] inMST;
    delete[] key;
    delete[] parent;
    return tree;
}

/**
 * @brief Kruskal's algorithm.
 * 
 * Computes a Minimum Spanning Tree (MST) using Union-Find.
 * @param g Input weighted graph.
 * @return Graph representing the MST.
 */
Graph Algorithms::kruskal(const Graph& g) {
    int n = g.getNumVertices();
    Graph tree(n);
    unionFind uf(n);

    struct Edge {
        int u, v, w;
    };

    Edge* edges = new Edge[n * n]; ///< Collect edges.
    int edgeCount = 0;

    // Collect all edges without duplicates
    for (int u = 0; u < n; ++u) {
        int count = g.getNeighborCount(u);
        int* neighbors = g.getNeighbors(u);

        for (int i = 0; i < count; ++i) {
            int v = neighbors[i];
            if (u < v) { // avoid duplicates
                edges[edgeCount++] = {u, v, g.getEdgeWeight(u, v)};
            }
        }
        delete[] neighbors;
    }

    // Sort edges by weight (bubble sort for simplicity)
    for (int i = 0; i < edgeCount - 1; ++i) {
        for (int j = 0; j < edgeCount - i - 1; ++j) {
            if (edges[j].w > edges[j + 1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Build MST
    for (int i = 0; i < edgeCount; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        if (uf.find(u) != uf.find(v)) {
            tree.addEdge(u, v, edges[i].w);
            uf.unite(u, v);
        }
    }

    delete[] edges;
    return tree;
}

} // namespace graph
