# Detectează toate fișierele .cpp din directorul curent
SRCS = $(wildcard *.cpp)

# Generează lista executabilelor (fără extensie)
EXES = $(SRCS:.cpp=)

# Compilatorul
CXX = g++

# Opțiuni pentru compilator
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Regula implicită: compilează toate executabilele
all: $(EXES)

# Regula pentru crearea fiecărui executabil
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Curăță toate executabilele
clean:
	rm -f $(EXES)
	rm -r ../out/* || true
	rm -r ../input/* || true
	rm -r ../ref/* || true
