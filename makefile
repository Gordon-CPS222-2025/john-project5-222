# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Source and object files
SRCS = Main.cc Town.cc Road.cc HighWayNetwork.cc
OBJS = $(SRCS:.cc=.o)

# Executable name 
TARGET = project5

# Default build rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)  # <-- TAB at start of line

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@  # <-- TAB at start of line

# Clean rule
clean:
	rm -f $(TARGET) $(OBJS) *~ *.out  # <-- TAB at start of line