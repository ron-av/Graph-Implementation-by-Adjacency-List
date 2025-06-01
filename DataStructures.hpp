// ronavraham99@gmail.com

#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

namespace graph {

/**
 * @struct Queue
 * @brief A simple circular queue implementation for integers.
 */
struct Queue {
    int* data;        ///< Array to hold elements.
    int capacity;     ///< Maximum number of elements.
    int front;        ///< Index of the front element.
    int rear;         ///< Index of the next insertion.
    int size;         ///< Current number of elements.

    /**
     * @brief Construct a new Queue with given capacity.
     * @param cap Maximum number of elements.
     */
    Queue(int cap) : capacity(cap), front(0), rear(0), size(0) {
        data = new int[capacity];
    }

    /// Destructor – releases allocated memory.
    ~Queue() {
        delete[] data;
    }

    /**
     * @brief Insert a value at the rear of the queue.
     * @param val Value to insert.
     * @note Does nothing if the queue is full.
     */
    void enqueue(int val) {
        if (size == capacity) return;
        data[rear] = val;
        rear = (rear + 1) % capacity;
        ++size;
    }

    /**
     * @brief Remove and return the front element.
     * @return The front value, or -1 if the queue is empty.
     */
    int dequeue() {
        if (isEmpty()) return -1;
        int val = data[front];
        front = (front + 1) % capacity;
        --size;
        return val;
    }

    /**
     * @brief Check if the queue is empty.
     * @return True if empty, false otherwise.
     */
    bool isEmpty() const {
        return size == 0;
    }
};

/**
 * @struct PriorityQueue
 * @brief A simple array-based priority queue (min-priority).
 */
struct PriorityQueue {
    int* values;       ///< Stored values.
    int* priorities;   ///< Corresponding priorities.
    int size;          ///< Current number of elements.
    int capacity;      ///< Maximum capacity.

    /**
     * @brief Construct a new PriorityQueue with given capacity.
     * @param cap Maximum number of elements.
     */
    PriorityQueue(int cap) : size(0), capacity(cap) {
        values = new int[capacity];
        priorities = new int[capacity];
        for (int i = 0; i < capacity; ++i)
            priorities[i] = 1e9; ///< Initialize with "infinity".
    }

    /// Destructor – releases allocated memory.
    ~PriorityQueue() {
        delete[] values;
        delete[] priorities;
    }

    /**
     * @brief Insert a value with its priority.
     * @param value The value to store.
     * @param priority The associated priority.
     * @note Does nothing if the queue is full.
     */
    void insert(int value, int priority) {
        if (size == capacity) return;
        values[size] = value;
        priorities[size] = priority;
        ++size;
    }

    /**
     * @brief Extract the value with the smallest priority.
     * @return The value with minimum priority, or -1 if empty.
     */
    int extractMin() {
        if (size == 0) return -1;
        int minIndex = 0;
        for (int i = 1; i < size; ++i) {
            if (priorities[i] < priorities[minIndex])
                minIndex = i;
        }
        int val = values[minIndex];
        values[minIndex] = values[size - 1];
        priorities[minIndex] = priorities[size - 1];
        --size;
        return val;
    }

    /**
     * @brief Decrease the priority of a given value.
     * @param value The value to update.
     * @param newPriority The new priority.
     */
    void decreaseKey(int value, int newPriority) {
        for (int i = 0; i < size; ++i) {
            if (values[i] == value && priorities[i] > newPriority) {
                priorities[i] = newPriority;
                break;
            }
        }
    }

    /**
     * @brief Check if the priority queue is empty.
     * @return True if empty, false otherwise.
     */
    bool isEmpty() const {
        return size == 0;
    }
};

/**
 * @struct unionFind
 * @brief Disjoint-set (Union-Find) data structure with path compression and union by rank.
 */
struct unionFind {
    int* parent;   ///< Parent array for disjoint sets.
    int* rank;     ///< Rank array for balancing unions.
    int size;      ///< Number of elements.

    /**
     * @brief Construct a new unionFind with n elements.
     * @param n Number of elements.
     */
    unionFind(int n) : size(n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    /// Destructor – releases allocated memory.
    ~unionFind() {
        delete[] parent;
        delete[] rank;
    }

    /**
     * @brief Find the representative of a set containing x.
     * @param x Element to search.
     * @return Root of the set.
     * @note Uses path compression for efficiency.
     */
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    /**
     * @brief Union two sets containing x and y.
     * @param x First element.
     * @param y Second element.
     * @note Uses union by rank heuristic.
     */
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return;
        if (rank[rx] < rank[ry])
            parent[rx] = ry;
        else if (rank[rx] > rank[ry])
            parent[ry] = rx;
        else {
            parent[ry] = rx;
            rank[rx]++;
        }
    }
};

} // namespace graph

#endif // DATA_STRUCTURES_HPP
