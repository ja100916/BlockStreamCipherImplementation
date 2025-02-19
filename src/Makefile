# Compiler and flags
CXX = g++                                            # C++ compiler
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror         # Compiler flags
INCLUDES = -Iinclude                                 # Include directory

# Directories
SRC_DIR = src
INC_DIR = include
TEST_DIR = test
BUILD_DIR = build
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/cipher

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)                 # All source files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)   # Object files

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/test_%.o)
TEST_TARGET = $(BIN_DIR)/test_cipher

# Create necessary directories
$(shell mkdir -p $(BUILD_DIR) $(BIN_DIR))

# Main target
all: $(TARGET)

$(TARGET): $(OBJS)                                  # Link object files
	$(CXX) $(OBJS) -o $@

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Test target
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(filter-out $(BUILD_DIR)/main.o, $(OBJS))
	$(CXX) $^ -o $@

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Documentation
docs:
	doxygen Doxyfile

# Clean build files
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

# Install
install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin

.PHONY: all test clean docs install