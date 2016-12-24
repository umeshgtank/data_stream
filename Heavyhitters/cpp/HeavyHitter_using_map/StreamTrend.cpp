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
}

//Use following medthod to insert an element in fss
void StreamTrend::updateItemHit(std::string &data){
    //Search for the element. if it is found just udpate the count
    bool bFound = false;
    std::map<std::string, int>::iterator itr;
    for (itr = m_counters.begin(); itr != m_counters.end(); ++itr){
        if ((*itr).first== data){
            (*itr).second++;
            bFound = true;
            break;
        }
    }
    if (!bFound){
        //If there is a space in the counter then let's add it
        if(m_counters.size() < m_counterSize){
            m_counters.insert(std::pair<std::string, int>(data, 1));
        } else {
            //If there is no space in the list then let's decrement
            //values of each element in the map and remove map entries
            //with 0 count
            std::map<std::string, int>::iterator it;
            for (it = m_counters.begin(); it != m_counters.end();){
                (*it).second--;
                if ((*it).second == 0){
                    m_counters.erase(it++);
                }else {
                    ++it;
                }
            }
        }
    }
}

//Get top N from the list
void StreamTrend::printTopTrends(){
    std::cout<<"Top N from the stream are \n";
    std::cout<<"Value \t Frequency \t error \t counter_error\n";
    std::map<std::string, int>::iterator it;
    for (it = m_counters.begin(); it != m_counters.end(); ++it){
        std::cout<<(*it).first<<"\t\t"<<(*it).second<<"\n";
    }
}

//Returns most freqent element (Top - N)
std::vector<std::string> StreamTrend::getTopTrends(){
    //Sort the map
    std::vector<std::pair<std::string, int> > counter(m_counters.begin(), m_counters.end());
    std::sort(counter.begin(), counter.end(), monitoredListComparator<std::string, int>());
    
    std::vector<std::string> topTrends;
    std::vector<std::pair<std::string, int> >::iterator itr;
    for (itr = counter.begin(); itr != counter.end(); ++itr){
        topTrends.push_back((*itr).first);
    }
    
    return topTrends;
}
