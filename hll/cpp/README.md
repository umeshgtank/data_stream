# data stream - HyperLogLog

Implementation of Hyperloglog algorithm in C++.

1. This algorithm is implemented with 32-bit and 64-bit hash word. hll is 32-bit hash word implementation whereas hll64 is 64-bit hash word implementation. 
2. To test the algorithm, program generates predefined set of cardinal values and adds them to both 32-bit & 64-bit implementations. After adding predefined set of data it calculates the cardinality. I just use a very basic and simple technique where i am using a text "hyperloglog_" and appending 1..n to the string based on the predefined value of n.
3. I tried various hashing algorithms with sample data and found cityhash better than other hashing algorithms. Hence, using cityhash. What i observed is hashing has an influence on the results. 


##Notes:
1. The implementation is not extensively tested hence it can have bugs and i will be more than happy to fix all of them. 


##Compiling the source.
1. Point your terminal to the directory where you have checkout the code and run 'make'
2. It will build a binary called 'hll'
3. Run hll and you will see the results on your terminal. 
