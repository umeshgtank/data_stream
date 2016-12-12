//
//  fss.hpp
//  fss
//
//  Created by Umesh Tank on 10/31/16.
//  Copyright © 2016 Umesh Tank. All rights reserved.
//  Version - 0.1
//

#ifndef fss_hpp
#define fss_hpp

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

//This is an implementation of Flitered space saving below is a link to the paper
//http://www.l2f.inesc-id.pt/~fmmb/wiki/uploads/Work/misnis.ref0a.pdf


struct bitmapCounter{
    //Represents error
    long    alpha_error;
    
    //Represents if an element is monitored by the monitored list
    bool    isMonitored;
};


struct fssElement{
    std::string     value;              //store value of element
    long            frequency;          //frequency of the element. Estimate count
    long            error;              //errors in count
    bitmapCounter   counter;            //reference to counter from the bitmap
    bool            isEmpty;            //Check if this is an empty element
    long            counter_index;      //To store index of the counter for easy retrival
    
};

//Need sorting algo to sort monitored element
//Need hash functons to hash the value
class fss{
public:
    //Constructors
    fss(long bitmapCell, long monitoredElement);
    
    //Copy constructor
    fss(const fss&);
    
    //Assignment operators
    fss& operator=(const fss&);
    
    //Use following medthod to insert an element in fss
    void appendToList(std::string &data);
    
    //Get top N from the list
    void printTopN();
    
private:
    //h - hash function for number of cells
    long                                bitmapCounterCells_h;
    
    //m - Number of monitored elements in list
    long                                noOfMonitoredElement_m;
    
    //Moniotered list with max number of elements is equal to  m(noOfMonitoredElement_m)
    std::vector<fssElement> monitoredList;
    
    //Bitmap counter to count hits with number of elements is equal to h(bitmapCounterCells_h)
    std::shared_ptr<bitmapCounter>      counter;
    
    //Bitmap counter which holds cells = 'bitmapCounterCells_h'
    std::vector<bitmapCounter>          bitmap;
    
    //sets this flag to true if monitored list is full
    bool                                isMonitoredListFull;
    
};

////Implementing a dummy class for input. This will be an input format and
////fss can just call getStream to get the data in key-value pair.
//template <typename Type = std::string>
//class streamFormat{
//private:
//    Type formatter;
//};


//Writing a functor to sort monitored list
//template <typename dataType>
class monitoredListComparator{
public:
    bool operator()(const fssElement &rhs, const fssElement &lhs){
        if (rhs.frequency == lhs.frequency){
            return rhs.error > lhs.error;
        }
        return rhs.frequency > lhs.frequency;
    }
};


#endif /* fss_hpp */
