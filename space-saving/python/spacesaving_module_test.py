from spacesaving import *

if __name__ == '__main__':
    no_of_args = len(sys.argv)
    if no_of_args == 3:
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

