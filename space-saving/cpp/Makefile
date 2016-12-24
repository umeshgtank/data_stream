CXX = clang++
CXXFLAGS = -Wall -g -std=c++11

main: main.o ss.o
	$(CXX) $(CXXFLAGS) -o spacesaving main.o ss.o

main.o: main.cpp ss.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

ss.o: ss.cpp ss.hpp
	$(CXX) $(CXXFLAGS) -c ss.cpp
