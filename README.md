# data stream

Implementation of various data stream algorithms in different (but relevant) programming languages.


##Notes:
1. This is the first version and i just wanted to see FSS (Filtered space saving) algorithm in action. Code is not optimized and there are many improvements.
2. This is not extensively tested hence it can have bugs and i will be more than happy to fix all of them.


##Pending items
1. Initially i thought of implementing classes as template but I couldn’t think of any use case. I am still in dilemma if template implementation makes sense?
2. ~~Including Makefile for easy compilation.~~
3. Code cleanup. 
4. All the data member of bitmapCounter & fssElement are public and that needs to be fixed. They must be private


##Compiling the source.
1. You need to provide a location of directory where your data files are residing. You can set “DATA_FILE_DIR“ macro in main.cpp
2. By default main.cpp uses “\n” as delimiter. You can change this by setting DATA_DELIMITERS macro in main.cpp
3. Point your terminal to the directory where you have checkout the code and run 'make'
4. It will build a binary called 'fss'






