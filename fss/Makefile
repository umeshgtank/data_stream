CXX = clang++
CXXFLAGS = -Wall -g -std=c++11

main: main.o fss.o
	$(CXX) $(CXXFLAGS) -o fss main.o fss.o

main.o: main.cpp fss.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

fss.o: fss.cpp fss.hpp
	$(CXX) $(CXXFLAGS) -c fss.cpp
