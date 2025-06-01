# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Targets
TARGET = main
TEST_TARGET = tests

# Source files
SRCS = Main.cpp Graph.cpp AdjacencyList.cpp Algorithms.cpp
OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = Tests.cpp Graph.cpp AdjacencyList.cpp Algorithms.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default build
all: $(TARGET)

# Build main program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Build and run tests (doctest)
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Run valgrind on main program
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Clean build files
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
