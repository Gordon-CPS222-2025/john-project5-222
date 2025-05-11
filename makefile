# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Source and object files
SRCS = Main.cc Town.cc Road.cc HighWayNetwork.cc DisjointSet.cc
OBJS = $(SRCS:.cc=.o)

# Executable name 
TARGET = project5

# Default build rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)  

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@  

# Clean rule
clean:
	rm -f $(TARGET) $(OBJS) 