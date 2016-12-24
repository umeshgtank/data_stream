//
//  ss.hpp
//  ss
//
//  Created by Umesh Tank on 12/18/16.
//  Copyright © 2016 Umesh Tank. All rights reserved.
//

#ifndef ss_hpp
#define ss_hpp

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>


// This is an implementation of space saving algorithm. Original paper can be
// found here -
// http://www.cse.ust.hk/~raywong/comp5331/References/EfficientComputationOfFrequentAndTop-kElementsInDataStreams.pdf
// http://www.mathcs.emory.edu/~cheung/papers/StreamDB/Frequency-count/2005-Metwally-Top-k-elements.pdf
//
// As per the paper Algorithm is defined as follows.
// Algorithm: Space-Saving(m counters, stream S)
// begin
//   for each element, e, in S{
//       If e is monitored,
//           increment the counter of e;
//       else
//       {
//           let em be the element with least hits, min
//           Replace em with e;
//           Increment countm;
//           Assign error-m the value min;
//       }
// }// end for
// end;
//
// TODO the data structure "stream summary" described in the paper is not yet implemented.
// TODO description of implementation details
//


struct ssElement{
    //Represents actual value
    std::string value;
    
    //Represents error
    long        count;
    
    //Represents if an element is monitored by the monitored list
    long        error;
    
    //Indicates if it is empty 
    bool        isFull;
};

//Need sorting algo to sort monitored element
class SpaceSaving{
public:
    //Constructors
    SpaceSaving(long noOfCounters);
    
    //Copy constructor
    SpaceSaving(const SpaceSaving&);
    
    //Assignment operators
    SpaceSaving& operator=(const SpaceSaving&);
    
    //Use following medthod to insert an element in ss
    void appendData(std::string &data);
    
    //Get top N from the list
    void printTopN();
    
    //Returns most freqent element (Top - N)
    std::vector<std::string> getFrequneElement();
    
    
private:
    //Number of counters for the frequent elements. Defines the size
    //of monitoring list
    long                        m_counters;
    
    //Moniotered list with max number of elements is equal to  m(noOfMonitoredElement_m)
    std::vector<ssElement>      m_monitoredList;
    
    //sets this flag to true if monitored list is full
    bool                        m_isMonitoredListFull;
    
};


//Writing a functor to sort monitored list
//template <typename dataType>
class monitoredListComparator{
public:
    bool operator()(const ssElement &rhs, const ssElement &lhs){
        if (rhs.count == lhs.count){
            return rhs.error > lhs.error;
        }
        return rhs.count > lhs.count;
    }
};

#endif /* ss_hpp */
