# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iincludes

# Directories
INCLUDES_DIR = includes
SRC_DIR = src
BUILD_DIR = build

# Programs to build
PROGRAMS = dijkstra dial radixheap

# Common source files
COMMON_SRC = RadixHeap.cpp Graph.cpp Parse.cpp Timer.cpp
COMMON_OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(COMMON_SRC))

# Source files for each program
dijkstra_SRC = Dijkstra.cpp $(COMMON_SRC)
dial_SRC = Dial.cpp $(COMMON_SRC)
radix_SRC = Radix.cpp $(COMMON_SRC)

# Object files for each program
dijkstra_OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(dijkstra_SRC))
dial_OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(dial_SRC))
radix_OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(radix_SRC))

# Default target to build all programs
all: $(PROGRAMS)

# Rules for each program
dijkstra: $(dijkstra_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

dial: $(dial_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

radixheap: $(radix_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generic rule to compile .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up all build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony targets to avoid conflicts with file names
.PHONY: all clean