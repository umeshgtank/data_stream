# data stream algorithms - Heavy hitter

Implementation of heavy hitter (stream trend) algorithm in C++.


##Notes:
1. This is the first version and i just wanted to see heavy hitter algorithm in action. Code is not optimized and there are many improvements.
2. This is not extensively tested hence it can have bugs and i will be more than happy to fix all of them.


##Compiling the source.
1. You need to provide a location of directory where your data files are residing. You can set “DATA_FILE_DIR“ macro in main.cpp
2. By default main.cpp uses “\n” as delimiter. You can change this by setting DATA_DELIMITERS macro in main.cpp
3. Point your terminal to the directory where you have checkout the code and run 'make'
4. It will build a binary called 'StreamTrend'






