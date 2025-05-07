# Makefile for CPS 222 Project 5
# Folder: john-project5-222

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Source and object files
SRCS = main.cc Town.cc Road.cc HighWayNetwork.cc
OBJS = $(SRCS:.cc=.o)

# Executable name
TARGET = project5

# Default build rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test rule (update input/output files accordingly)
test: $(TARGET)
	./$(TARGET) < t01-input.in > t01-output.out
	@echo "Test complete. Output saved to t01-output.out"

# Clean rule
clean:
	rm -f $(TARGET) *.o *.out
