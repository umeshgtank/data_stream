//
//  ss.cpp
//  ss
//
//  Created by Umesh Tank on 12/18/16.
//  Copyright © 2016 Umesh Tank. All rights reserved.
//

#include "ss.hpp"
#include <iostream>

//Constructure initialize member variables
SpaceSaving::SpaceSaving(long noOfCounters):m_counters(noOfCounters){
    m_isMonitoredListFull = false;
    m_monitoredList.assign(m_counters, ssElement());
}


void SpaceSaving::appendData(std::string &data){
    std::vector<ssElement>::iterator it;
    //Find element in the list
    //This is important otherwise we keep adding duplicate elements if monitored
    //list is empty. Which is not desirable
    bool bIsMonitoredListUpdate = false;
    for (it = m_monitoredList.begin() ; it != m_monitoredList.end(); ++it){
        if ((*it).value == data){
            (*it).count++;
            bIsMonitoredListUpdate = true;
            break;
        }
    }
    
    if (!bIsMonitoredListUpdate){
        //If not found let's check if monitored list has an empty space
        if (!m_isMonitoredListFull){
            typename std::vector<ssElement >::iterator it;
            for (it = m_monitoredList.begin() ; it != m_monitoredList.end(); ++it){
                if(!(*it).isFull){
                    //prepare an element and set it to this iterator
                    (*it).value = data;
                    (*it).error = 0;
                    (*it).count = 1;
                    (*it).isFull = true;
                    bIsMonitoredListUpdate = true;
                    break;
                }
            }
            if (!bIsMonitoredListUpdate){
                m_isMonitoredListFull = true;
            }
        } else {
            //let's replace the last element.
            m_monitoredList[m_counters-1].error = m_monitoredList[m_counters-1].count;
            m_monitoredList[m_counters-1].count++;
            m_monitoredList[m_counters-1].value = data;
            bIsMonitoredListUpdate = true;
        }
        
        if (bIsMonitoredListUpdate){
            std::sort(m_monitoredList.begin(), m_monitoredList.end(), monitoredListComparator());
        }
    }
}

void SpaceSaving::printTopN(){
    std::cout<<"Top N from the stream are \n";
    std::cout<<"Value \t Frequency \t error \t counter_error\n";
    std::vector<ssElement>::iterator it;
    for (it = m_monitoredList.begin() ; it != m_monitoredList.end(); ++it){
        std::cout<<(*it).value<<"\t\t"<<(*it).count<<"\t\t"<<(*it).error<<"\t\t"<<"\n";
    }
}

std::vector<std::string> SpaceSaving::getFrequneElement(){
    std::vector<ssElement>::iterator it;
    std::vector<std::string> frequentElement;
    for (it = m_monitoredList.begin() ; it != m_monitoredList.end(); ++it){
        std::cout<<(*it).value<<"\t\t"<<(*it).count<<"\t\t"<<(*it).error<<"\t\t"<<"\n";
        frequentElement.push_back((*it).value);
    }
    return frequentElement;
}

