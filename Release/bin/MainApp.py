import sys
import traceback
import socket
from ctypes import *

oldStdout = None  
logfile = None  

def InitPy():
    logfile = open('1.log','w+')  
    oldStdout = sys.stdout  
    sys.stdout = logfile  

def UninitPy():
    if logfile:  
        logfile.close()  
    if oldStdout:  
        sys.stdout = oldStdout  




def main(a):
    try:
        raise Exception("abbdddddddd")
    except Exception, e:
        err = str(traceback.format_exc())
        user32 = windll.LoadLibrary('user32.dll')         
        user32.MessageBoxA(0, err, "error", 0)   
    return 888

if __name__ == "__main__":
    main(0);
