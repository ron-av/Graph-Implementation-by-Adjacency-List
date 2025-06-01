// ronavraham99@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace graph;

// ----------- BFS TESTS -----------


TEST_CASE("BFS traversal and tree structure") {
    SUBCASE("Connected graph") {
        Graph g(4);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);

        Graph tree = Algorithms::bfs(g, 0);

        CHECK(tree.getNumVertices() == 4);
        CHECK(tree.containsEdge(0, 1));
        CHECK(tree.containsEdge(0, 2));
        CHECK(tree.containsEdge(1, 3));
        CHECK_FALSE(tree.containsEdge(2, 3));
    }

    SUBCASE("Disconnected graph") {
        Graph g(4);
        g.addEdge(0, 1);
        g.addEdge(2, 3);

        Graph tree = Algorithms::bfs(g, 0);

        CHECK(tree.getNumVertices() == 4);
        CHECK(tree.containsEdge(0, 1));
        CHECK_FALSE(tree.containsEdge(2, 3));
        CHECK_FALSE(tree.containsEdge(1, 2));
    }

    SUBCASE("Empty graph") {
        Graph g(0);
        Graph tree = Algorithms::bfs(g, 0);
        CHECK(tree.getNumVertices() == 0);
    }

    SUBCASE("Single node") {
        Graph g(1);
        Graph tree = Algorithms::bfs(g, 0);
        CHECK(tree.getNumVertices() == 1);
        CHECK(tree.countEdges() == 0);
    }
}

// ----------- DFS TESTS -----------


TEST_CASE("DFS traversal and tree structure") {
    SUBCASE("Connected graph") {
        Graph g(4);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);

        Graph tree = Algorithms::dfs(g, 0);

        CHECK(tree.getNumVertices() == 4);
        CHECK(tree.containsEdge(0, 1));
        CHECK(tree.containsEdge(1, 0));
        CHECK(tree.containsEdge(0, 2));
        CHECK (tree.containsEdge(2, 0));
        CHECK(tree.containsEdge(1, 3));
        CHECK(tree.containsEdge(3, 1));
        CHECK_FALSE(tree.containsEdge(2, 3));
    }

    SUBCASE("Disconnected graph") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(2, 3);

        Graph tree = Algorithms::dfs(g, 0);

        CHECK(tree.getNumVertices() == 5);
        CHECK(tree.containsEdge(0, 1));
        CHECK_FALSE(tree.containsEdge(2, 3));
        CHECK_FALSE(tree.containsEdge(1, 2));
    }

    SUBCASE("Empty graph") {
        Graph g(0);
        Graph tree = Algorithms::dfs(g, 0);
        CHECK(tree.getNumVertices() == 0);
    }

    SUBCASE("Single node") {
        Graph g(1);
        Graph tree = Algorithms::dfs(g, 0);
        CHECK(tree.getNumVertices() == 1);
        CHECK(tree.countEdges() == 0);
    }
}

// ----------- DIJKSTRA TESTS -----------


TEST_CASE("Dijkstra's shortest paths") {
    SUBCASE("Weighted graph") {
        Graph g(5);
        g.addEdge(0, 1, 2);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 2);
        g.addEdge(2, 4, 1);
        g.addEdge(3, 4, 3);

        Graph tree = Algorithms::dijkstra(g, 0);

        CHECK(tree.getNumVertices() == 5);
        CHECK(tree.containsEdge(0, 1));
        CHECK(tree.containsEdge(1, 2));
        CHECK(tree.containsEdge(1, 3));
        CHECK(tree.containsEdge(2, 4));
        CHECK_FALSE(tree.containsEdge(0, 2));
    }

    SUBCASE("Single node") {
        Graph g(1);
        Graph tree = Algorithms::dijkstra(g, 0);
        CHECK(tree.getNumVertices() == 1);
        CHECK(tree.countEdges() == 0);
    }

    SUBCASE("Empty graph") {
        Graph g(0);
        Graph tree = Algorithms::dijkstra(g, 0);
        CHECK(tree.getNumVertices() == 0);
    }
}

// ----------- PRIM TESTS -----------

/**
 * Test Prim's MST algorithm on various graphs.
 */
TEST_CASE("Prim's Minimum Spanning Tree") {
    SUBCASE("Weighted graph") {
        Graph g(5);
        g.addEdge(0, 1, 3);
        g.addEdge(0, 3, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 3);
        g.addEdge(2, 4, 5);
        g.addEdge(3, 4, 6);

        Graph mst = Algorithms::prim(g);

        CHECK(mst.getNumVertices() == 5);
        CHECK(mst.countEdges() == 4);
    }

    SUBCASE("Single node") {
        Graph g(1);
        Graph mst = Algorithms::prim(g);
        CHECK(mst.getNumVertices() == 1);
        CHECK(mst.countEdges() == 0);
    }

    SUBCASE("Empty graph") {
        Graph g(0);
        Graph mst = Algorithms::prim(g);
        CHECK(mst.getNumVertices() == 0);
    }
}

// ----------- KRUSKAL TESTS -----------

/**
 * Test Kruskal's MST algorithm on various graphs.
 */
TEST_CASE("Kruskal's Minimum Spanning Tree") {
    SUBCASE("Weighted graph") {
        Graph g(5);
        g.addEdge(0, 1, 3);
        g.addEdge(0, 3, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 3);
        g.addEdge(2, 4, 5);
        g.addEdge(3, 4, 6);

        Graph mst = Algorithms::kruskal(g);

        CHECK(mst.getNumVertices() == 5);
        CHECK(mst.countEdges() == 4);
    }

    SUBCASE("Single node") {
        Graph g(1);
        Graph mst = Algorithms::kruskal(g);
        CHECK(mst.getNumVertices() == 1);
        CHECK(mst.countEdges() == 0);
    }

    SUBCASE("Empty graph") {
        Graph g(0);
        Graph mst = Algorithms::kruskal(g);
        CHECK(mst.getNumVertices() == 0);
    }
}
