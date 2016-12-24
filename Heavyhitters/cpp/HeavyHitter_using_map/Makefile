CXX = clang++
CXXFLAGS = -Wall -g -std=c++11

main: main.o StreamTrend.o
	$(CXX) $(CXXFLAGS) -o StreamTrend main.o StreamTrend.o

main.o: main.cpp StreamTrend.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

StreamTrend.o: StreamTrend.cpp StreamTrend.hpp
	$(CXX) $(CXXFLAGS) -c StreamTrend.cpp
