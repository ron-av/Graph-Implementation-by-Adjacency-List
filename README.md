# Graph Implementation by Adjacency List

## Description
Implementation of an **undirected weighted graph** in C++ using an **adjacency list**, without STL containers.  
Includes classic algorithms (BFS, DFS, Dijkstra, Prim, Kruskal) and custom data structures (Queue, Priority Queue, Union-Find).  
All memory is managed manually with `new`/`delete`.

---

## Structure
- **AdjacencyList** – singly-linked neighbor list per vertex  
- **Graph** – fixed number of vertices, supports add/remove edges, printing  
- **DataStructures** – Queue, PriorityQueue, UnionFind  
- **Algorithms** – BFS, DFS, Dijkstra, Prim, Kruskal  
- **Main.cpp** – demo program  
- **Tests.cpp** – doctest unit tests  

---

## Requirements
- **g++** (C++11 or later)  
- **make**  
- **valgrind** (optional, for memory leak detection)  
- **doctest.h** (already included in the repo for unit tests)

---

## Build & Run

```bash
make          # build ./main
./main        # run demo

make test     # run doctest unit tests
make valgrind # run memory checks (requires valgrind)
make clean    # remove build files
```

## Author
- Ron Avraham
- ronavraham1999@gmail.com
