//
//  hll.hpp
//  hll
//
//  Created by Um3sh Tank on 1/21/17.
//  Copyright © 2017 Umesh Tank. All rights reserved.
//

//Note that Murmur3 hash is copied from below location
////https://github.com/avz/hll/tree/master/deps/MurmurHash3
// And credit goes to orignal Auther - Austin Appleby.

#ifndef hll_hpp
#define hll_hpp

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <cmath>

//Pre-calculated 2^32
#define pow_2_32 4294967296ull


// Implement of hyperloglog cardinality estimation algorithm.
// Below algorithm is implemented using following paper
// http://algo.inria.fr/flajolet/Publications/FlFuGaMe07.pdf
//
class hll {
public:
    //Constructor with default to 10 bits
    hll(uint8_t b = 10);
    
    //Adds string to the data set for cardinality calculation
    void addData(const std::string & str);
    
    //Returns the cardinality of the set
    double estimate();
        
    
private:
    //Number of bits. b in original paper
    uint8_t  bits;
    
    //Number of registers used for bucketization
    uint32_t m;
    
    //Actual buckets / registers
    std::vector<uint8_t> M;
    
    //Represents alpha * m^2
    double alpha_MSquar;
};

#endif /* hll_hpp */
