#
#  streamtrend_module_test.py
#
#  Created by Umesh Tank on 18-Dec-16.
#  Copyright (c) 2016 Umesh Tank. All rights reserved.
#
# This file demonstrates usage of streamtrend as a module
# It imports all the classes from streamtrend and uses its function to get
#  most trending items.
# This same example is also available in streamtrend.py
#

from streamtrend import *

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
        print "Usage streamtrend_module_test <no-of-topics-to-track> <Path-to-data-directory>"

