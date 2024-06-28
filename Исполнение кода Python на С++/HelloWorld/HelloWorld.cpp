#include "C:\Program Files\WindowsApps\PythonSoftwareFoundation.Python.3.11_3.11.2288.0_x64__qbz5n2kfra8p0\include\Python.h"
#define CALL(NAME_FUNCTION, OBJECT) PyFloat_AsDouble(PyObject_CallObject(PyObject_GetAttrString(PyImport_Import(PyUnicode_FromString((char*)"__main__")), NAME_FUNCTION), OBJECT))

//#include <Python.h>
#include <iostream>
#include <string>

class MyClass
{
public:
    const char* program = R"(
import time

def q(q,s):
    return time.time()

def s(q,s):
    return time.time()

def t(q,s):
    return time.time()

)";

	MyClass();
	~MyClass();
    auto Run();
private:

};

MyClass::MyClass()
{
    Py_Initialize();
}

MyClass::~MyClass()
{
    Py_Finalize();
}

auto MyClass::Run()
{
    
    PyRun_SimpleStringFlags(this->program, NULL);
    auto name = "q";
    PyObject* T = PyTuple_New(2);
    PyTuple_SetItem(PyTuple_New(2), 0, PyLong_FromLong(2));
    PyTuple_SetItem(PyTuple_New(2), 1, PyLong_FromLong(3));
    long result = CALL("s", PyTuple_New(2));

    std::cout << "Result: " << result << std::endl;
    Py_DECREF(T);
    
}

int main() {
    MyClass python;
    python.Run();
    return 0;

}