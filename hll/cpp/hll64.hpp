//
//  hll.hpp
//  hlltest
//
//  Created by Um3sh Tank on 1/21/17.
//  Copyright © 2017 Umesh Tank. All rights reserved.
//

//Note that city hash is copied from below location
//https://github.com/google/cityhash
// And credit goes to the orignal Auther(s).

#ifndef hll64_hpp
#define hll64_hpp

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <cmath>

//Pre-calculated 2^64
#define pow_2_64 18446744073709551615ull


// Implement of hyperloglog cardinality estimation algorithm.
// Below algorithm is implemented using following paper
// http://algo.inria.fr/flajolet/Publications/FlFuGaMe07.pdf
//

class hll64 {
public:
    //Constructor with default to 10 bits
    hll64(uint8_t b = 10);
    
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

#endif /* hll64_hpp */
