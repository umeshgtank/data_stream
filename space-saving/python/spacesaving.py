#
#  spacesaving.py
#
#  Created by Umesh Tank on 18-Dec-16.
#  Copyright (c) 2016 Umesh Tank. All rights reserved.
#
# This is an implementation of space saving algorithm. Original paper can be
# found here -
# http://www.cse.ust.hk/~raywong/comp5331/References/EfficientComputationOfFrequentAndTop-kElementsInDataStreams.pdf
# http://www.mathcs.emory.edu/~cheung/papers/StreamDB/Frequency-count/2005-Metwally-Top-k-elements.pdf
#
# As per the paper Algorithm is defined as follows.
# Algorithm: Space-Saving(m counters, stream S)
# begin
#   for each element, e, in S{
#       If e is monitored,
#           increment the counter of e;
#       else
#       {
#           let em be the element with least hits, min
#           Replace em with e;
#           Increment countm;
#           Assign error-m the value min;
#       }
# }// end for
# end;
#
# TODO the data structure "stream summary" described in the paper is not yet implemented.
# TODO description of implementation details
#

import collections
from os import listdir
from os.path import isfile, join
import time
import datetime
import sys

# class counterElement:
#     def __init__(self, cnt=0, err=0):
#         self.count = cnt
#         self.error = err

class spaceSaving:
    def __init__(self, noOfCnt= 33):
        # number of counters to get the frequent elements
        self.noOfCounters = noOfCnt
        self.ssCounter = collections.Counter()

    def appendData(self, data):
        if data in self.ssCounter:
            self.ssCounter[data]['count'] += 1
        elif len(self.ssCounter) < self.noOfCounters:
            self.ssCounter[data] = {'count': 1, 'error': 0}
        else:
            k, element = self.ssCounter.most_common()[-1]
            del self.ssCounter[k]
            self.ssCounter[data] = {'count': element['count']+1, 'error': element['count']} #counterElement(element.count+1, element.count)
            # for item in self.ssCounter:
            #     self.ssCounter[item]["count"] -= 1
            # # remove 0 or -ve counts
            # self.topicsList += collections.Counter()

    def getFrequentElements(self):
        return self.ssCounter.most_common()

if __name__ == '__main__':
    no_of_args = len(sys.argv)
    if no_of_args == 2:
        args = str(sys.argv)
        # Example mostTrending = streamTrend(33);
        ss = spaceSaving(int(sys.argv[1]));
        dirpath = sys.argv[2];
        count = 0
        entryCount = 0;
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S:%f')
        print "Space saving in action & searching for most frequent elements  ..", st
        datafiles = [f for f in listdir(dirpath) if isfile(join(dirpath, f))]
        for item in datafiles:
            count += 1
            with open(join(dirpath, item)) as f:
                for line in f:
                    ss.appendData(line)
                    entryCount += 1
            if count == 103:
                break

        print "No of files processed= ", count
        print "Total number of entries processed = ", entryCount
        trends = ss.getFrequentElements()
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S:%f')
        print "Done with search...", st, "\nreturned frequent elements are =", trends
    else:
        print "Usage spacesaving <no-of-counters> <Path-to-data-directory>"

