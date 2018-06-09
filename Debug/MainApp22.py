import sys

#sys.path.append(r'D:\\MyProjects\\PythonCDemo27\\Debug\\dlls')
#sys.path.append(r'D:\\MyProjects\\PythonCDemo27\\Debug\\dlls\\PyQt4')

import traceback
import socket
#import QtGui, QtCore
#import QtGui
from ctypes import *



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
