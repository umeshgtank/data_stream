 //
//  hll.cpp
//  hll
//
//  Created by Um3sh Tank on 1/21/17.
//  Copyright © 2017 Umesh Tank. All rights reserved.
//

#include "hll.hpp"
#include <string>
#include <iostream>
#include "city.h"

//Note that Murmur3 hash is copied from below location
////https://github.com/avz/hll/tree/master/deps/MurmurHash3
// And credit goes to orignal Auther - Austin Appleby.
extern "C" {
#include "MurmurHash3.h"
}

//Constructor
//initializing predefined values for alpha.
//Available in the original paper
hll::hll(uint8_t b) : bits(b){
    m = pow(2, (double)bits);
    M = std::vector<uint8_t>(m,0);
    double alpha;
    switch(m)
    {
        case 16:
            alpha = 0.673;
            break;
        case 32:
            alpha = 0.697;
            break;
        case 64:
            alpha = 0.709;
            break;
        default:
            alpha = 0.7213/(1.0 + 1.079/m); //This is a default alpha
    }
    alpha_MSquar = alpha * m * m;
}

// Add a new string to estimate cardinatliy
// Below function adds string for cardinality estimation.
// 1. It creates a has of the provided string
// 2. subtracts number of bits allocated for registers. That is For example
//       in our case by default 10 bits (b in the original paper) are allocated
//       for registers and hence 32-10 = 22 (w_bits) bits will be used for
//       actual hash value
// 3. Find the register index by shifting hash by w_bits times
// 4. get the position of the left most 1-bit from hash after shifting by number
//      of bits. function p(w) in the original paper
// 5. Compare if position is greater than the exisiting value in register
// 6.  if true replace the value with the new one
void hll::addData(const std::string & str){
    //Creating murmur3 hash.
    //Check out Duff's device in murmur3 implementation
    //uint32_t hash = MurmurHash3_x86_32(str.c_str(), (uint32_t)str.length(), 0x5f61767a);
    uint32_t hash = CityHash32(str.c_str(), (uint32_t)str.length());
    //Get the index by shifting 32-bits
    //the binary address determined by the first b bits
    uint32_t w_bits = 32 - bits;
    uint32_t index = hash >> w_bits;
    if(index >= m)
    {
        index = m - 1;
    }
    
    //Get the position of the left most 1-bit. p(s) in the paper
    uint32_t position = 1;
    uint32_t one = ((uint32_t)1 << 31);
    uint32_t w = hash << bits;
    while ((w & one) != one && position <= w_bits)
    {
        ++position;
        w <<= 1;
    }
    
    if( position > M[index] )
    {
        M[index] = position;
    }
}

//This is an estimation function which calculates the cardinality
//based on the register filled up by addData function.
//Below steps are already defined in the original paper
//1. Sum of 2^(-M[i]) where i is from 0 to 2^bits
//2. estimation = alpha * m^2 / Sum.
//3. Correction based on the original paper
//4. if  estimation is < 2.5*m
//      then if any of the register contians 0 then we will use linear counting
//5. if estimation is greater than 1/30 * 2^32 then adjust with the following
//6. estimation = -2^32 * log(1 - (estimate/2^32))
//7. Return the estimate.
double hll::estimate(){
    double estimate;
    double sum = 0.0;
    for (uint32_t i = 0; i < m; i++)
    {
        sum += 1.0/pow(2.0, M[i]);
    }
    estimate = alpha_MSquar/sum;
    if( estimate <= 2.5 * m )
    {
        uint32_t zeros = 0;
        for (uint32_t i = 0; i < m; i++)
        {
            if (M[i] == 0)
            {
                zeros++;
            }
        }
        if( zeros != 0 )
        {
            estimate = m * log((double)m/zeros);   //Linear counting
        }
    }
    else if (estimate > (1.0/30.0) * pow_2_32)
    {
        estimate = -(pow_2_32 * log(1.0 - ( estimate/pow_2_32 ) ));
    }
    return estimate;
}
