# Makefile for the project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
SRCDIR = src
BUILDDIR = build
BINDIR = bin
INCDIR = include

# Source files
SRCS = $(shell find $(SRCDIR) -name "*.cpp")

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Executable name
TARGET = $(BINDIR)/surit

# Default target
all: clean $(TARGET)

# Rule to create the build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Rule to create the bin directory
$(BINDIR):
	mkdir -p $(BINDIR)

# Rule to compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Rule to link object files into the executable
$(TARGET): $(OBJS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
