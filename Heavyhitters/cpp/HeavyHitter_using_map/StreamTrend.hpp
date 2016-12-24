//
//  StreamTrend.hpp
//  streamtrend
//
//  Created by Umesh Tank on 12/18/16.
//  Copyright © 2016 Umesh Tank. All rights reserved.
//

#ifndef StreamTrend_hpp
#define StreamTrend_hpp

#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <vector>


// This is an implementation of heavy hitter. The purpose of this algorithm
// is to find trends in the stream and get the most frequent elements.
// the challenge with this approach is that it expacts
//
// Below steps describes the implementation details.
//
// If item is in the topicList
//   Increment the count by one
// elseif length of topicList is not total number of topics to track
//   Add new item and set it's count to 1
// else
//   decrement all topic's count by 1
//   Remove elements with 0 count from the list
//
// Note:
//      In this implementation we are using std::map to maintain a list of
//      heavy hitters. There is another implementaion which is based on
//      std::vector where instead of removing an element we are replacing
//      which is faster as we just need to replace an element instead of
//      remove and insert another element
//


class StreamTrend{

public:
    //Constructors
    StreamTrend(long noOfCounters);
    
    //Copy constructor
    StreamTrend(const StreamTrend&);
    
    //Assignment operators
    StreamTrend& operator=(const StreamTrend&);
    
    //Use following medthod to insert an element in fss
    void updateItemHit(std::string &data);
    
    //Get top N from the list
    void printTopTrends();
    
    
    //Returns most freqent element (Top - N)
    std::vector<std::string> getTopTrends();
    
    
private:
    //Number of counters for the frequent elements. Defines the size
    //of monitoring list
    long                m_counterSize;
    
    //Moniotered list with max number of elements is equal to  m(noOfMonitoredElement_m)
    std::map<std::string, int>  m_counters;
    
    //sets this flag to true if monitored list is full
    bool                m_isMonitoredListFull;
};



//Writing a functor to sort monitored list
template <typename _first, typename _second>
class monitoredListComparator{
public:
    bool operator()(const std::pair<_first, _second> &rhs, const std::pair<_first, _second> &lhs){
        return rhs.second > lhs.second;
    }
};

#endif /* StreamTrend_hpp */
