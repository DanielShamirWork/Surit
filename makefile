# Makefile for the project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -g -I$(SRCDIR)

# Directories
SRCDIR = src
BUILDDIR = build
BINDIR = bin
INCDIR = include

# Source files
SRCS = $(shell find $(SRCDIR) -name "*.cpp")

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
OBJS_NO_MAIN = $(filter-out $(BUILDDIR)/main.o, $(OBJS))

# Test files
TESTDIR = tests
TEST_BUILDDIR = $(BUILDDIR)/tests
TEST_SRCS = $(shell find $(TESTDIR) -name "*.cpp")
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp,$(TEST_BUILDDIR)/%.o,$(TEST_SRCS))

# Test executable name
TEST_TARGET = $(BINDIR)/surit_test

# Executable name
TARGET = $(BINDIR)/surit

# Default target
all: $(TARGET)

# Rule to create the build directory
$(BUILDDIR) $(TEST_BUILDDIR):
	mkdir -p $@

# Rule to create the bin directory
$(BINDIR):
	mkdir -p $(BINDIR)

# Rule to compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile test files
$(TEST_BUILDDIR)/%.o: $(TESTDIR)/%.cpp | $(TEST_BUILDDIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(TESTDIR) -c $< -o $@

# Rule to link object files into the executable
$(TARGET): $(OBJS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Rule to link test files into the test executable
$(TEST_TARGET): $(TEST_OBJS) $(OBJS_NO_MAIN) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Phony targets
.PHONY: all clean test

# Test target
test: $(TEST_TARGET)
	./$(TEST_TARGET)
