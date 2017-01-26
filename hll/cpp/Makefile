CC=gcc
CXX = clang++
CXXFLAGS = -Wall -g -std=c++11 -v

main: main.o hll.o hll64.o MurmurHash3.o city.o
	$(CXX) $(CXXFLAGS) -o hll main.o hll.o MurmurHash3.o hll64.o city.o

main.o: main.cpp hll.hpp hll64.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

hll.o: hll.cpp hll.hpp
	$(CXX) $(CXXFLAGS) -c hll.cpp 

MurmurHash3.o: MurmurHash3.c MurmurHash3.h
	$(CC) -v -c MurmurHash3.c

hll64.o: hll64.cpp hll64.hpp
	$(CXX) $(CXXFLAGS) -c hll64.cpp

city.o: city.cc city.h
	$(CXX) $(CXXFLAGS) -c city.cc

clean:
	-$(RM) -f ./hll
	find . -name "*.o" -type f -print | xargs rm -f
