#
#  streamtrend.py
#
#  Created by Umesh Tank on 18-Dec-16.
#  Copyright (c) 2016 Umesh Tank. All rights reserved.
#
# This is an implementation of heavy hitter. The purpose of this algorithm
# is to find trends in the stream and get the most frequent elements.
# the challenge with this approach is that it expacts
#
# Below steps describes the implementation details.
#
# If item is in the topicList
#   Increment the count by one
# elseif length of topicList is not total number of topics to track
#   Add new item and set it's count to 1
# else
#   decrement all topic's count by 1
#   Remove elements with 0 count from the list

import collections
from os import listdir
from os.path import isfile, join
import time
import datetime
import sys

class streamTrend:
    def __init__(self, noOfTopicsToTrack = 33):
        # number of items to track for heavy hitting
        self.noOfTopics = noOfTopicsToTrack
        self.topicsList = collections.Counter()

    def updateItemHit(self, data):
        if data in self.topicsList:
            self.topicsList[data] += 1
        elif len(self.topicsList) < self.noOfTopics:
            self.topicsList[data] = 1
        else:
            for topic in self.topicsList:
                self.topicsList[topic] -= 1
            # remove 0 or -ve counts
            self.topicsList += collections.Counter()

    def getTrends(self):
        return self.topicsList.most_common()

if __name__ == '__main__':
    no_of_args = len(sys.argv)
    if no_of_args == 3:
        args = str(sys.argv)
        # Example mostTrending = streamTrend(33);
        mostTrending = streamTrend(int(sys.argv[1]));
        dirpath = sys.argv[2];
        count = 0
        entryCount = 0;
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S:%f')
        print "Stream trend in action & searching for most trending ..", st
        datafiles = [f for f in listdir(dirpath) if isfile(join(dirpath, f))]
        for item in datafiles:
            count += 1
            with open(join(dirpath, item)) as f:
                for line in f:
                    mostTrending.updateItemHit(line)
                    entryCount += 1
            if count == 103:
                break

        print "No of files processed= ", count
        print "Total number of entries processed = ", entryCount
        trends = mostTrending.getTrends()
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S:%f')
        print "Done with trend search ...", st, "\nreceived trend =", trends
    else:
        print "Usage streamtrend <no-of-topics-to-track> <Path-to-data-directory>"

