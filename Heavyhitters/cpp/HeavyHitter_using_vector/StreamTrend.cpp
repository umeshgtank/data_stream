//
//  StreamTrend.cpp
//  streamtrend
//
//  Created by Umesh Tank on 12/18/16.
//  Copyright © 2016 Umesh Tank. All rights reserved.
//


// If item is in the topicList
//   Increment the count by one
// elseif length of topicList is not total number of topics to track
//   Add new item and set it's count to 1
// else
//   decrement all topic's count by 1
//   Remove elements with 0 count from the list


#include "StreamTrend.hpp"
#include <iostream>

StreamTrend::StreamTrend(long noOfCounters):m_counterSize(noOfCounters){
    m_counters.assign(m_counterSize, element());
}

//Use following medthod to insert an element in fss
void StreamTrend::updateItemHit(std::string &data){
    //Search for the element. if it is found just udpate the count
    bool bFound = false;
    std::vector<element>::iterator itr;
    for (itr = m_counters.begin(); itr != m_counters.end(); ++itr){
        if ((*itr).value== data){
            (*itr).count++;
            bFound = true;
            break;
        }
    }
    if (!bFound){
        //If there is a space in the counter then let's add it
        if (!m_isMonitoredListFull){
        typename std::vector<element>::iterator it;
        for (it = m_counters.begin() ; it != m_counters.end(); ++it){
            if(!(*it).isFull){
                //prepare an element and set it to this iterator
                (*it).value = data;
                (*it).count = 1;
                (*it).isFull = true;
                bFound = true;
                break;
            }
        }
        if (!bFound){
            m_isMonitoredListFull = true;
        }
        
       } else {
            //If there is no space in the list then let's decrement
            //values of each element in the map and remove map entries
            //with 0 count
           typename std::vector<element>::iterator it;
           for (it = m_counters.begin() ; it != m_counters.end(); ++it ){
               if(!(*it).isFull){
                   //prepare an element and set it to this iterator
                   (*it).value = data;
                   (*it).count --;
                   if ((*it).count == 0){
                       (*it).isFull = false;
                       m_isMonitoredListFull = false;
                   }
                   break;
               }
           }
        }
    }
}

void StreamTrend::printTopTrends(){
    std::cout<<"Top N from the stream are \n";
    std::cout<<"Value \t Frequency \t error \t counter_error\n";
    std::vector<element>::iterator it;
    for (it = m_counters.begin() ; it != m_counters.end(); ++it){
        std::cout<<(*it).value<<"\t\t"<<(*it).count<<"\t\t"<<"\n";
    }
}

std::vector<std::string> StreamTrend::getTopTrends(){
    //sort the vector
    std::sort(m_counters.begin(), m_counters.end(), monitoredListComparator());

    //Iterate and get top trends
    std::vector<element>::iterator it;
    std::vector<std::string> frequentElement;
    for (it = m_counters.begin() ; it != m_counters.end(); ++it){
        std::cout<<(*it).value<<"\t\t"<<(*it).count<<"\t\t"<<"\n";
        frequentElement.push_back((*it).value);
    }
    return frequentElement;
}

