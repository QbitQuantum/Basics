static PyObject* pyvicon_connect(PyObject* self, PyObject* args) {
    //inputs
    PyObject* capsule;
    char* address;
    
    //parse
    if (!PyArg_ParseTuple(args, "Os", &capsule, &address)) return NULL;
    Client* client = (Client*)PyCapsule_GetPointer(capsule, NULL);
    
    //thread waits here
    Output_Connect out;
    Py_BEGIN_ALLOW_THREADS
    out = client->Connect(address);
    Py_END_ALLOW_THREADS
    
    //true if connected, false if failed
    switch (out.Result) {
        case Result::Success:
            Py_RETURN_TRUE;
        case Result::ClientAlreadyConnected:
            Py_RETURN_TRUE;
        case Result::ClientConnectionFailed:
            Py_RETURN_FALSE;
        default:
            break;
    }
    
    //raise errors for everything else
    if (handleError(out.Result)) return NULL;
    
    //catch the rest
    Py_RETURN_FALSE;
}