//
//  fss.cpp
//  fss
//
//  Created by Umesh Tank on 10/31/16.
//  Copyright © 2016 Umesh Tank. All rights reserved.
//

#include "fss.hpp"
#include <iostream>


//This is an implementation of Flitered space saving below is a link to the paper
//http://www.l2f.inesc-id.pt/~fmmb/wiki/uploads/Work/misnis.ref0a.pdf
//
//Below steps describes the implementaion details.
//TODO: Flow needs to be adjusted with implementation
//This is how it is implemented here - a fss algo.
//1. Apply hash function on the input data. Say hash is hData.
//2. Find the index for hashed value which is within the range of bitmap counter.
//      Use this technique hData % bitmapCounterCells_h;
//3. Check if counter's 'isMonitored' flag is true
//      a. If it is true search the element with same value as data within the monitored list
//      b. Pretty sure it is  there otherwise there is something wrong with the implementation
//      c. Update the frequency of the element by 1
//      d. Make sure monitored list is sorted
//4. If 'isMonitored' flag is flase
//      a. which means element is not monitored and we got to add it to the list
//      b. If monitored list is not full just add the element to the end.
//          Make sure monitored list is sorted
//      c. If full we need to replace the last element (Ideally this should be the last element in) with new one only if
//         Check if counter's alpha +1 > monitored element's frequency.
//          I. Get bitmap counter's index from the monitored list element which will be removed
//          II. set bitmpap counter [index].ismonitored = false; & error = monitored list element's frequency
//          III. Update monitored list by setting value, frequency = bitmapcounter[index].alpha_error, counter_index = index
//          IV. Set bitmap_counter[index].ismonitored = true;
//          V. Make sure monitored list is sorted
//      d. If counter's alpha +1 > monitored element's frequency.
//          Just update counter's alpha by 1
//

fssElement::fssElement(std::string &val,
                                 long freq,
                                 long err,
                                 bitmapCounter &ctr):   value(val),
                                                        frequency(freq),
                                                        error(err),
                                                        counter(ctr){}


//Constructure initialize member variables
//TODO: Need designated initializers
//template <typename dataType>
fss::fss(){
    bitmap.assign(bitmapCounterCells_h, bitmapCounter());
    isMonitoredListFull = false;
    //TODO: in my opinion initializing with empty object should be fine as well
    //because we can always check frequency and replace the element. This will
    //make sure that we will have a common implementation.
    monitoredList.assign(noOfMonitoredElement_m, fssElement());
}

fss::fss(long bitmapCell, long monitoredElement)
:bitmapCounterCells_h(bitmapCell), noOfMonitoredElement_m(monitoredElement){
    bitmap.assign(bitmapCounterCells_h, bitmapCounter());
    isMonitoredListFull = false;
    //TODO: in my opinion initializing with empty object should be fine as well
    //because we can always check frequency and replace the element. This will
    //make sure that we will have a common implementation.
    monitoredList.assign(noOfMonitoredElement_m, fssElement());
}

//template <typename dataType>
void fss::appendToList(std::string &data){
    std::size_t hData = std::hash<std::string>{}(data);
    //Even this works!
//    std::hash<std::string> hs;
//    std::size_t hData = hs(data);
    
    //std::cout<<"calculated hash= "<< hData <<" \tfor the data = "<<data <<" possible cell index = "<<hData % bitmapCounterCells_h<<"\n";
    long bitmapCellIndex = hData % bitmapCounterCells_h;
    //if (bitmap[bitmapCellIndex]){
        if (bitmap[bitmapCellIndex].isMonitored){
            //exist in monitored list
            std::vector<fssElement>::iterator it;
            for (it = monitoredList.begin() ; it != monitoredList.end(); ++it){
                //std::cout << ' ' <<(*it).frequency<<(*it).error<<(*it).frequency<<(*it).value<<"\n";
                if ((*it).value == data){
                    //Found the element. Now let's update the frequency by 1
                    (*it).frequency++;
                    
                    //Do we need a function to sort the element something like ?
                    //sortMonitoredList();
                    std::sort(monitoredList.begin(), monitoredList.end(), monitoredListComparator());
                    //printTopN();
                    break;
                }
            }
        } else {
            //Not monitored. Either need to add or replace the existing one
            //let's check if list is full
            bool isMonitoredListUpdate = false;
            if (!isMonitoredListFull){
                typename std::vector<fssElement >::iterator it;
                for (it = monitoredList.begin() ; it != monitoredList.end(); ++it){
                    if((*it).isEmpty){
                        //prepare an element and set it to this iterator
                        (*it).value = data;
                        (*it).frequency = bitmap[bitmapCellIndex].alpha_error+1;
                        (*it).error = bitmap[bitmapCellIndex].alpha_error;
                        (*it).counter = bitmap[bitmapCellIndex];
                        (*it).isEmpty = false;
                        (*it).counter_index = bitmapCellIndex;
                        bitmap[bitmapCellIndex].isMonitored = true;
                        isMonitoredListUpdate = true;
                        break;
                    }
                }
                if (!isMonitoredListUpdate){
                    isMonitoredListFull = true;
                }
            } else {
                //let's replace the last element.
                //Note that we need to updat the existing element's counter
                if (bitmap[bitmapCellIndex].alpha_error+1 > monitoredList[noOfMonitoredElement_m-1].frequency){
                    long monitoredListCounterIndex = monitoredList[noOfMonitoredElement_m-1].counter_index;
                    bitmap[monitoredListCounterIndex].isMonitored = false;
                    bitmap[monitoredListCounterIndex].alpha_error = monitoredList[noOfMonitoredElement_m-1].frequency + 1;
                    
                    monitoredList[noOfMonitoredElement_m-1].value = data;
                    monitoredList[noOfMonitoredElement_m-1].frequency = bitmap[bitmapCellIndex].alpha_error+1;
                    monitoredList[noOfMonitoredElement_m-1].error = bitmap[bitmapCellIndex].alpha_error;
                    monitoredList[noOfMonitoredElement_m-1].counter = bitmap[bitmapCellIndex]; //This needs a pointer assignment
                    monitoredList[noOfMonitoredElement_m-1].counter_index = bitmapCellIndex;
                    bitmap[bitmapCellIndex].isMonitored = true;
                    
                    isMonitoredListUpdate = true;
                } else {
                    //Update coutner's alpha_error
                    bitmap[bitmapCellIndex].alpha_error++;
                }
            }
            
            if (isMonitoredListUpdate){
                std::sort(monitoredList.begin(), monitoredList.end(), monitoredListComparator());
                //printTopN();
            }
        }
}

void fss::printTopN(){
    std::cout<<"Top N from the stream are \n";
    std::cout<<"Value \t Frequency \t error \t counter_error\n";
    std::vector<fssElement>::iterator it;
    for (it = monitoredList.begin() ; it != monitoredList.end(); ++it){
        std::cout<<(*it).value<<"\t\t"<<(*it).frequency<<"\t\t"<<(*it).error<<"\t\t"<<(*it).counter.alpha_error<< "\n";
    }
}
//template <typename dataType>
//void fss<dataType>::sortMonitoredList(){
//    //Sort the list.
//    std::sort(monitoredList.begin(), monitoredList.end());
//}

