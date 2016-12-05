##
##  fss.py
##
##  Created by Umesh Tank on 3-Dec-16.
##  Copyright (c) 2016 Umesh Tank. All rights reserved.
##
## This is an implementation of Filtered spce saving algorithm. Below is
## link to the paper
## http://www.l2f.inesc-id.pt/~fmmb/wiki/uploads/Work/misnis.ref0a.pdf
##Below steps describes the implementaion details.
##TODO: Flow needs to be adjusted with implementation
##This is how it is implemented here - a fss algo.
##1. Apply hash function on the input data. Say hash is hData.
##2. Find the index for hashed value which is within the range of bitmap counter.
##      Use this technique hData % bitmapCounterCells_h;
##3. Check if counter's 'isMonitored' flag is true
##      a. If it is true search the element with same value as data within the monitored list
##      b. Pretty sure it is  there otherwise there is something wrong with the implementation
##      c. Update the frequency of the element by 1
##      d. Make sure monitored list is sorted
##4. If 'isMonitored' flag is false
##      a. which means element is not monitored and we got to add it to the list
##      b. If monitored list is not full just add the element to the end.
##          Make sure monitored list is sorted
##      c. If full we need to replace the last element (Ideally this should be the last element in) with new one only if
##         Check if counter's alpha +1 > monitored element's frequency.
##          I. Get bitmap counter's index from the monitored list element which will be removed
##          II. set bitmpap counter [index].ismonitored = false; & error = monitored list element's frequency
##          III. Update monitored list by setting value, frequency = bitmapcounter[index].alpha_error, counter_index = index
##          IV. Set bitmap_counter[index].ismonitored = true;
##          V. Make sure monitored list is sorted
##      d. If counter's alpha +1 > monitored element's frequency.
##          Just update counter's alpha by 1
##
## TODO:
##      1. Monitored list is sorted based on just frequency. We must use error if frequency is same
##      2. Use argparser. Check example here https://www.cyberciti.biz/faq/python-command-line-arguments-argv-example/
##      3. Use default for monitored list and bitmap counter if not passed as part of command line parameters
##

from os import listdir
from os.path import isfile, join
import time
import datetime
import sys


class bitmapCounter:
    def __init__(self, alphaError, isMonitored):
        self.alphaError = 0
        self.isMonitored = False


class fssElement:
    def __init__(self, value, frequency, error, counter, index):
        self.value = value
        self.frequency = frequency
        self.error = error
        self.counter = counter
        self.counter_index = index
        self.isEmpty = True;


class fss:
    def __init__(self, bitmap_counter_size, topN):
        # h - hash function for no of cells
        self.bitmapCounterSize_h = bitmap_counter_size

        # m - no of monitored elements in the list
        self.monitoredListSize_m = topN

        # Monitored list which holds elements that are monitored
        self.monitoredList = []
        for _i in range(self.monitoredListSize_m):
            self.monitoredList.append(fssElement('', 0, 0, 0, 0))

        # bitmap list which holds the counter
        self.bitmapList = []
        for _k in range(self.bitmapCounterSize_h):
            self.bitmapList.append(bitmapCounter(0, False))

        # is monitored list full
        self.isMonitoredListFull = False

    def getEmptyIndexFromMonitoredList(self):
        for _i in range(self.monitoredListSize_m):
            if self.monitoredList[_i].isEmpty is True:
                return _i
        return -1

    def appendToList(self, data):
        # calculate hash.
        # Note hash can return -ve value but we are using % which gives +ve
        # value. Hence we don't care.
        should_sort_list = False
        bitmap_index = hash(data) % self.bitmapCounterSize_h
        if self.bitmapList[bitmap_index].isMonitored is True:
            for element in self.monitoredList:
                if element.value == data:
                    element.frequency += 1
                    should_sort_list = True
            # Sort the list if needed
            if should_sort_list is True:
                self.monitoredList.sort(key=lambda x: x.frequency, reverse=True)
        else:
            if self.isMonitoredListFull is False:
                insert_index = self.getEmptyIndexFromMonitoredList();
                if insert_index is not -1:  # enter new entry into monitored list
                    self.monitoredList[insert_index].value = data
                    self.monitoredList[insert_index].frequency = self.bitmapList[bitmap_index].alphaError + 1
                    self.monitoredList[insert_index].error = self.bitmapList[bitmap_index].alphaError
                    self.monitoredList[insert_index].counter = self.bitmapList[bitmap_index]
                    self.monitoredList[insert_index].counter_index = bitmap_index
                    self.monitoredList[insert_index].isEmpty = False
                    self.bitmapList[bitmap_index].isMonitored = True;
                    should_sort_list = True
                    # Sort monitored list after this
                if should_sort_list is False:
                    self.isMonitoredListFull = True
            else:  # Replace last entry from the list
                if self.bitmapList[bitmap_index].alphaError + 1 > self.monitoredList[
                            self.monitoredListSize_m - 1].frequency:
                    monitored_counter_index = self.monitoredList[self.monitoredListSize_m - 1].counter_index
                    self.bitmapList[monitored_counter_index].isMonitored = False
                    self.bitmapList[monitored_counter_index].alpha_error = self.monitoredList[
                                                                               self.monitoredListSize_m - 1].frequency + 1

                    self.monitoredList[self.monitoredListSize_m - 1].value = data
                    self.monitoredList[self.monitoredListSize_m - 1].frequency = self.bitmapList[
                                                                                     bitmap_index].alphaError + 1
                    self.monitoredList[self.monitoredListSize_m - 1].error = self.bitmapList[bitmap_index].alphaError
                    self.monitoredList[self.monitoredListSize_m - 1].counter = self.bitmapList[bitmap_index]
                    self.monitoredList[self.monitoredListSize_m - 1].counter_index = bitmap_index
                    self.bitmapList[bitmap_index].isMonitored = True;
                    should_sort_list = True
                else:
                    self.bitmapList[bitmap_index].alphaError += 1
            if should_sort_list is True:
                self.monitoredList.sort(key=lambda x: x.frequency, reverse=True)

    def getTopN(self):
        # prints and returns top-n values
        topn = []
        for element in self.monitoredList:
            # print "value=", element.value, "frequency=", element.frequency, "error=", element.error
            topn.append(element.value)
        return topn

    def getTopNWithFrequency(self):
        # prints and returns top-n values
        topn = {}
        for element in self.monitoredList:
            print "value=", element.value, "frequency=", element.frequency, "error=", element.error
            topn[element.value] = element.frequency
        return topn


if __name__ == '__main__':
    no_of_args = len(sys.argv)
    if no_of_args == 4:
        args = str(sys.argv)
        # Example _fss = fss(43, 10);
        _fss = fss(int(sys.argv[1]), int(sys.argv[2]));
        dirpath = sys.argv[3];
        count = 0
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S:%f')
        print "Started counting top values..", st
        datafiles = [f for f in listdir(dirpath) if isfile(join(dirpath, f))]
        for item in datafiles:
            count += 1
            with open(join(dirpath, item)) as f:
                for line in f:
                    _fss.appendToList(line)
            if count == 103:
                break

        print "No of files processed= ", count
        top = _fss.getTopNWithFrequency()
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S:%f')
        print "Done with counting top values..", st, "\treturned top =", top
    else:
        print "Usage fss <no-of-bitmap-counter> <TopN> <Path-to-data-directory>"
