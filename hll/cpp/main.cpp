//
//  main.cpp
//  hll
//
//  Created by Um3sh Tank on 1/20/17.
//  Copyright © 2017 Umesh Tank. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include "hll.hpp"
#include "hll64.hpp"

int main(int argc, const char * argv[]) {
    //long dataPointRange[] = {150, 199, 550, 999, 1300, 9999, 13131, 99999, 131131, 999999, 1515151, 9999999, 17171717, 99999999, 151515151, 999999999, 1426789305, 9999999999};
    
    long dataPointRange[] = {150, 199, 550, 999, 1300, 5000, 9999, 13131, 25000, 49999, 74900, 89000,99999, 131131, 149900, 999999, 1515151, 9999999, 17171717};
    
    {
        timeval curTime;
        gettimeofday(&curTime, NULL);
        int milli = curTime.tv_usec / 1000;
        
        char buffer [80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));
        
        char currentTime[84] = "";
        sprintf(currentTime, "%s:%d", buffer, milli);
        printf("STARTING ... current time: %s \n", currentTime);
    }
    
    double dataPointRangeLength = (sizeof(dataPointRange)/sizeof(*dataPointRange));
    std::cout<<"Size of data point range is = "<<dataPointRangeLength<<"\n";
    for (int index = 0; index<dataPointRangeLength; index++){
        hll _hll = hll(10);
        hll64 _hll64 = hll64(20);
        std::string sampleStr("hyperloglog_");
        std::cout<<"\n\n################################## \nActual cardinality = "<<dataPointRange[index]<<"\n";
        for(int i = 0; i < dataPointRange[index]; i++) {
            std::string sample = sampleStr+std::to_string(i);
            _hll.addData(sample);
            _hll64.addData(sample);
        }
        double cardinality = _hll.estimate();
        double estimation_64 = _hll64.estimate();
        std::cout<<"Estimated cardinality with different implementation is as follows"<<"\n";
        std::cout<<"Cardinality estimated by actual implementation is = "<<cardinality<<"\n";
        std::cout<<"Cardinality estimated with 64bit acutal implementation is = "<<estimation_64<<"\n";
        std::cout<<"===========================";
    }
    
    {
        timeval curTime;
        gettimeofday(&curTime, NULL);
        int milli = curTime.tv_usec / 1000;
        
        char buffer [80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));
        
        char currentTime[84] = "";
        sprintf(currentTime, "%s:%d", buffer, milli);
        printf("\n\nEND ... current time: %s \n", currentTime);
    }
    
    return 0;
}
