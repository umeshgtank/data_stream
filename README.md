# data stream

Implementation of various data stream algorithms in different (but relevant) programming languages.


##Notes:
1. This is the first version and i just wanted to see FSS (Filtered space saving) algorithm in action. Code is not optimized and there are many improvements.
2. This is not extensively tested hence it can have bugs and i will be more than happy to fix all of them.


##Pending items
1. Initially i thought of implementing classes as template but I couldn’t think of any use case. I am still in dilemma if template implementation makes sense?
2. Including Makefile for easy compilation.
3. Code cleanup. 


##Compiling the source.
1. Ideally any linux based system should work. Soon i will include Makefile for easy compilation. But in the meantime you can use any tool. 
2. You need to provide a location of directory where your data files are residing. You can set “DATA_FILE_DIR“ macro in main.cpp
3. By default main.cpp uses “\n” as delimiter. You can change this by setting DATA_DELIMITERS macro in main.cpp




