##
##  fss_module_test.py
##
##  Created by Umesh Tank on 3-Dec-16.
##  Copyright (c) 2016 Umesh Tank. All rights reserved.
##
## This file demonstrates usage of fss as a module
## It imports fss and uses its function to get top-n values
## This same example is also available in fss.py

from fss import *

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
            with open (join(dirpath, item)) as f:
                for line in f:
                    _fss.appendToList(line)
            if count == 103:
                break

        print "No of files processed= ", count
        top = _fss.getTopN()
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S:%f')
        print "Done with counting top values..", st, "\treturned top =", top
    else:
        print "Usage fss <no-of-bitmap-counter> <TopN> <Path-to-data-directory>"
