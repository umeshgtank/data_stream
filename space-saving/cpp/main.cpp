//
//  main.cpp
//  ss
//
//  Created by Umesh Tank on 12/18/16.
//  Copyright © 2016 Umesh Tank. All rights reserved.
//

#include <iostream>
#include "ss.hpp"
#include "dirent.h"
#include <fstream>
#include <time.h>
#include <ctime>
#include <sys/time.h>

#define DATA_FILE_DIR       
#define DATA_DELIMITERS     "\n"


int main(int argc, const char * argv[]) {
    SpaceSaving ss(63);
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
                        ss.appendData(input);
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
    //std::cout<<"\n\nTime to get top values\n";
    std::vector<std::string> fe = ss.getFrequneElement();
    std::vector<std::string>::iterator it;
    std::cout<<"Frequent element returened by Space saving is = "<<"\n";
    for (it = fe.begin(); it != fe.end(); ++it){
        std::cout<<(*it)<<"\n";
    }
    ss.printTopN();
    
    return 0;
}
