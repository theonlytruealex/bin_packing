# Detect all .cpp files in the current directory
SRCS = $(wildcard *.cpp)

# Generate the list of executables (removes the .cpp extension)
EXES = $(SRCS:.cpp=)

# Compiler to use
CXX = g++

# Compiler options
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Default rule: build all executables
all: $(EXES)

# Rule to create each executable from its corresponding .cpp file
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean rule: remove all executables and object files
clean:
<<<<<<< HEAD
	rm -f $(EXES)
	rm -r ../out/* || true
	rm -r ../input/* || true
	rm -r ../ref/* || true
=======
	rm -f $(EXES) *.o
>>>>>>> 4ebe08c (Updates on generate_tests with mtp as greedy gen)
