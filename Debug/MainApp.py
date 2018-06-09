import sys
import traceback
#import socket
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
