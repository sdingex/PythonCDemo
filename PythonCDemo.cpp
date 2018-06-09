// PythonCDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "C:\Python27\include\Python.h"
#include <iostream>
using namespace std;

//#pragma comment(lib, "python27_d.lib") 
#pragma comment(lib, "python27.lib") 

//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

string log_python_exception()
{
    std::string strErrorMsg;
    if (!Py_IsInitialized())
    {
        strErrorMsg = "Python 运行环境没有初始化！";
        return strErrorMsg;
    }
	
    if (PyErr_Occurred() != NULL)
    {
        PyObject *type_obj, *value_obj, *traceback_obj;
        PyErr_Fetch(&type_obj, &value_obj, &traceback_obj);
        if (value_obj == NULL)
            return strErrorMsg;
		
        PyErr_NormalizeException(&type_obj, &value_obj, 0);
        if (PyString_Check(PyObject_Str(value_obj)))
        {
            strErrorMsg = PyString_AsString(PyObject_Str(value_obj));
        }
		
        if (traceback_obj != NULL)
        {
            strErrorMsg += "Traceback:";
			
            PyObject * pModuleName = PyString_FromString("traceback");
            PyObject * pTraceModule = PyImport_Import(pModuleName);
            Py_XDECREF(pModuleName);
            if (pTraceModule != NULL)
            {
                PyObject * pModuleDict = PyModule_GetDict(pTraceModule);
                if (pModuleDict != NULL)
                {
                    PyObject * pFunc = PyDict_GetItemString(pModuleDict,"format_exception");
                    if (pFunc != NULL)
                    {
                        PyObject * errList = PyObject_CallFunctionObjArgs(pFunc,type_obj,value_obj, traceback_obj,NULL);
                        if (errList != NULL)
                        {
                            int listSize = PyList_Size(errList);
                            for (int i=0;i < listSize;++i)
                            {
                                strErrorMsg += PyString_AsString(PyList_GetItem(errList,i));
                            }
                        }
                    }
                }
                Py_XDECREF(pTraceModule);
            }
        }
        Py_XDECREF(type_obj);
        Py_XDECREF(value_obj);
        Py_XDECREF(traceback_obj);
    }
    return strErrorMsg;
}


int main(int argc, char* argv[])
{
	string err_msg;
	PyObject *arg;

    Py_NoSiteFlag = 1;    //避免出现“'import site' failed”的错误
    Py_Initialize();
	if (!Py_IsInitialized())  
	{
		return 0; 
	}

	PyRun_SimpleString("import sys,os"); 
	PyRun_SimpleString("print sys.path"); 

    PyObject * pModule = NULL;
    PyObject * pFunc = NULL;
	PyObject * result = NULL;
    pModule = PyImport_ImportModule("MainApp");    //调用的文件名
	if (!pModule)
	{
		PyErr_Print();
		goto __exit;
		return 0;
	}
	
	pFunc= PyObject_GetAttrString(pModule, "main");    //调用的函数名
	if (!pFunc)
	{
		MessageBox(NULL, "PyObject_GetAttrString Error", "Error", 0);
		return 0;
	}

    arg = NULL;
    arg = Py_BuildValue("(s)", "123");   
	if (!arg)
	{
		MessageBox(NULL, "Py_BuildValue Error", "Error", 0);
		return 0;
	}

    result = PyEval_CallObject(pFunc, arg); 


	//int i;
	//PyArg_Parse(result, "i", &i);  

	//cout << i << endl;

	err_msg = log_python_exception();
	if(err_msg.length() > 0)
	{
		MessageBox(NULL, err_msg.c_str(), "error", 0);
	}

	PyErr_Clear();
    Py_Finalize();

__exit:
	system("pause");

	return 0;
}

