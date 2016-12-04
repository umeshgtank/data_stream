# FSS implementation

This is an implementation of Filtered spce saving algorithm in python. The algorithm is based on the below paper.
http://www.l2f.inesc-id.pt/~fmmb/wiki/uploads/Work/misnis.ref0a.pdf

##Directory structure
There are three files in the package.
  1. fss.py: An actual implementation of algorithm
  2. fss_module_test.py: Which loads fss as a module and retrieves top-n from the data set
  3. README.md: this file :-)

##Usage
This module can be used in two different ways.
  1. Use fss.py directly
  2. Load fss as moduel and import it in your script

###Run fss.py
This module requires three parameters.
  1. Number of bitmap counter that you would like to allocate
  2. Number of top values. That is define 'n' in top-n.
  3. Path to a directory where your data is residing

Note that first two parameters are required for an algorithm whereas third one is for data sets. It is not required by algorithm.
Launch your terminal and navigate to the directory where you have placed fss scripts and run following
<code>
python fss.py 43 10 DATA_SET_DIRECTORY
</code>


###Run fss_module_test.py
This module requires three parameters, same as fss.py.
  1. Number of bitmap counter that you would like to allocate
  2. Number of top values. That is define 'n' in top-n.
  3. Path to a directory where your data is residing

Note that first two parameters are required for an algorithm whereas third one is for data sets. It is not required by algorithm.
Launch your terminal and navigate to the directory where you have placed fss scripts and run following
<code>
python fss_module_test.py 43 10 DATA_SET_DIRECTORY
</code>


##Pending items
  1. Monitored list is sorted based on just frequency. We must use error if frequency is same
  2. Use argparser. Check example here https://www.cyberciti.biz/faq/python-command-line-arguments-argv-example/
  3. Use default for monitored list and bitmap counter if not passed as part of command line parameters

##Notes
    1. I am not python expert. Code may not be optimized. I am listening please feel free to suggest any optimization that you may find.
    2. Code is not extensively tested hence it can have bugs and i will be more than happy to fix all of them. Please feel free to report any bugs that you may found in the code