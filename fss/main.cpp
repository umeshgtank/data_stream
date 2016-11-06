//
//  main.cpp
//  fss
//
//  Created by Umesh Tank on 10/31/16.
//  Copyright © 2016 Umesh Tank. All rights reserved.
//

#include <iostream>
#include "fss.hpp"
#include "dirent.h"
#include <fstream>
#include <time.h>
#include <ctime>
#include <sys/time.h>


#define DATA_FILE_DIR
#define DATA_DELIMITERS     "\n"

int main(int argc, const char * argv[]) {
    std::string stream("In this work one proposes a novel algorithm, Filtered Space-Saving (FSS), that uses a filtering approach to improve on\
                       Space-Saving [14]. It also gets some inspiration on previous work around probabilistic counting and sliding windows statistics\
                       [3,6,8–10,18]. FSS uses a bitmap counter to filter and minimize updates on the monitored elements list and also to better\
                       estimate the error associated with each element. Instead of using a single error estimate value, it uses an error estimate\
                       dependent on the hash counter. This allows for better estimates by using the maximum possible error for that particular\
                       hash value instead of a global value. Although an additional bitmap counter has to be kept, it reduces the number of extra\
                       elements in the list needed to ensure high quality top-k elements. It will also reduce the number of list updates. The conjunction\
                       of the bitmap counter with the list of elements, minimizes the collision problem of most sketch-based algorithms.\
                       The bitmap counter size can depend on the number of k elements to be retrieved and not on the number of distinct elements\
                       of the stream, which is usually much higher.\
                       FSS uses a bitmap counter with h cells, each containing two values, ai and ci, standing for the error and the number of\
                       monitored elements in cell i. The hash function needs to be able to transform the input values from stream S into a uniformly\
                       distributed integer range. The hashed value h(x) is then used to access the corresponding counter. Initially all values of ai and\
                       ci are set to 0. The second storage element is a list of monitored elements with size m. The list is initially empty. Each element\
                       consists of 3 parts: the element itself vj, the estimate count fj and the associated error ej. Fig. 4 presents a block diagram of the\
                       FSS algorithm.\
                       The value of ai gives an indication on ‘‘how many of the hits occurring in that cell were not considered for the monitored\
                       list”. In order for an element to be included in the monitored list, it has to have at least as many possible hits ai as the minimum\
                       of the estimates in the monitored list, l = min{fj}. While the list has free elements, ai and l are set to 0.\
                       The algorithm is quite simple. When a new value is received, the hash is calculated and the bitmap counter is checked; If\
                       there are already monitored elements with that same hash (ci > 0), the monitored list is searched to see if this particular element\
                       is already there; If the element is in the list then the estimate count fj is incremented");
    fss fss(43, 10);
    int count = 0;
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
    
    DIR *dir;
    struct dirent *ent;
    std::cout<<"STARTING......";
    if ((dir = opendir (DATA_FILE_DIR)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            count++;
            std::string fullpath(DATA_FILE_DIR);
            fullpath.append(ent->d_name);
            //std::cout<<"fullpath = " <<fullpath<<"\n";
            std::ifstream dataFile(fullpath, std::ios::in);
            std::string line;
            if (dataFile.is_open()){
                //while(getline(dataFile, line)){
                dataFile.seekg(0,dataFile.end);
                long length = dataFile.tellg();
                dataFile.seekg(0,dataFile.beg);
                char *buf = new char [length];
                dataFile.read(buf, length);
                if (dataFile){
                    char *token;
                    //token = strtok(const_cast<char*>(line.c_str()) , " ");
                    token = strtok(buf , DATA_DELIMITERS);
                    while (token){
                        std::string input(token);
                        //std::cout<<input<<"\n";
                        fss.appendToList(input);
                        token = strtok(NULL , DATA_DELIMITERS);
                    }
                }
                //}
                dataFile.close();
                delete[] buf;
            }
            if(103 == count){
                break;
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    
    std::cout<<"\n\n\nTime to get top values\n";
    fss.printTopN();
    std::cout<<"DONE......"<<"\n";
    
    {
        timeval curTime;
        gettimeofday(&curTime, NULL);
        int milli = curTime.tv_usec / 1000;
        
        char buffer [80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));
        
        char currentTime[84] = "";
        sprintf(currentTime, "%s:%d", buffer, milli);
        printf("END ... current time: %s \n", currentTime);
    }
    
    return 0;
}
