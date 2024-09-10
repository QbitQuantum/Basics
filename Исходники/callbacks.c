/******************************************************************************
 *
 * Call the python object with all arguments
 *
 */
static void _CallPythonObject(void *mem,
                              ffi_type *restype,
                              SETFUNC setfunc,
                              PyObject *callable,
                              PyObject *converters,
                              int flags,
                              void **pArgs)
{
    Py_ssize_t i;
    PyObject *result;
    PyObject *arglist = NULL;
    Py_ssize_t nArgs;
    PyObject *error_object = NULL;
    int *space;
#ifdef WITH_THREAD
    PyGILState_STATE state = PyGILState_Ensure();
#endif

    nArgs = PySequence_Length(converters);
    /* Hm. What to return in case of error?
       For COM, 0xFFFFFFFF seems better than 0.
    */
    if (nArgs < 0) {
        PrintError("BUG: PySequence_Length");
        goto Done;
    }

    arglist = PyTuple_New(nArgs);
    if (!arglist) {
        PrintError("PyTuple_New()");
        goto Done;
    }
    for (i = 0; i < nArgs; ++i) {
        /* Note: new reference! */
        PyObject *cnv = PySequence_GetItem(converters, i);
        StgDictObject *dict;
        if (cnv)
            dict = PyType_stgdict(cnv);
        else {
            PrintError("Getting argument converter %d\n", i);
            goto Done;
        }

        if (dict && dict->getfunc && !_ctypes_simple_instance(cnv)) {
            PyObject *v = dict->getfunc(*pArgs, dict->size);
            if (!v) {
                PrintError("create argument %d:\n", i);
                Py_DECREF(cnv);
                goto Done;
            }
            PyTuple_SET_ITEM(arglist, i, v);
            /* XXX XXX XX
               We have the problem that c_byte or c_short have dict->size of
               1 resp. 4, but these parameters are pushed as sizeof(int) bytes.
               BTW, the same problem occurs when they are pushed as parameters
            */
        } else if (dict) {
            /* Hm, shouldn't we use PyCData_AtAddress() or something like that instead? */
            CDataObject *obj = (CDataObject *)PyObject_CallFunctionObjArgs(cnv, NULL);
            if (!obj) {
                PrintError("create argument %d:\n", i);
                Py_DECREF(cnv);
                goto Done;
            }
            if (!CDataObject_Check(obj)) {
                Py_DECREF(obj);
                Py_DECREF(cnv);
                PrintError("unexpected result of create argument %d:\n", i);
                goto Done;
            }
            memcpy(obj->b_ptr, *pArgs, dict->size);
            PyTuple_SET_ITEM(arglist, i, (PyObject *)obj);
#ifdef MS_WIN32
            TryAddRef(dict, obj);
#endif
        } else {
            PyErr_SetString(PyExc_TypeError,
                            "cannot build parameter");
            PrintError("Parsing argument %d\n", i);
            Py_DECREF(cnv);
            goto Done;
        }
        Py_DECREF(cnv);
        /* XXX error handling! */
        pArgs++;
    }

#define CHECK(what, x) \
if (x == NULL) _ctypes_add_traceback(what, "_ctypes/callbacks.c", __LINE__ - 1), PyErr_Print()

    if (flags & (FUNCFLAG_USE_ERRNO | FUNCFLAG_USE_LASTERROR)) {
        error_object = _ctypes_get_errobj(&space);
        if (error_object == NULL)
            goto Done;
        if (flags & FUNCFLAG_USE_ERRNO) {
            int temp = space[0];
            space[0] = errno;
            errno = temp;
        }
#ifdef MS_WIN32
        if (flags & FUNCFLAG_USE_LASTERROR) {
            int temp = space[1];
            space[1] = GetLastError();
            SetLastError(temp);
        }
#endif
    }

    result = PyObject_CallObject(callable, arglist);
    CHECK("'calling callback function'", result);

#ifdef MS_WIN32
    if (flags & FUNCFLAG_USE_LASTERROR) {
        int temp = space[1];
        space[1] = GetLastError();
        SetLastError(temp);
    }
#endif
    if (flags & FUNCFLAG_USE_ERRNO) {
        int temp = space[0];
        space[0] = errno;
        errno = temp;
    }
    Py_XDECREF(error_object);

    if ((restype != &ffi_type_void) && result) {
        PyObject *keep;
        assert(setfunc);
#ifdef WORDS_BIGENDIAN
        /* See the corresponding code in callproc.c, around line 961 */
        if (restype->type != FFI_TYPE_FLOAT && restype->size < sizeof(ffi_arg))
            mem = (char *)mem + sizeof(ffi_arg) - restype->size;
#endif
        keep = setfunc(mem, result, 0);
        CHECK("'converting callback result'", keep);
        /* keep is an object we have to keep alive so that the result
           stays valid.  If there is no such object, the setfunc will
           have returned Py_None.

           If there is such an object, we have no choice than to keep
           it alive forever - but a refcount and/or memory leak will
           be the result.  EXCEPT when restype is py_object - Python
           itself knows how to manage the refcount of these objects.
        */
        if (keep == NULL) /* Could not convert callback result. */
            PyErr_WriteUnraisable(callable);
        else if (keep == Py_None) /* Nothing to keep */
            Py_DECREF(keep);
        else if (setfunc != _ctypes_get_fielddesc("O")->setfunc) {
            if (-1 == PyErr_Warn(PyExc_RuntimeWarning,
                                 "memory leak in callback function."))
                PyErr_WriteUnraisable(callable);
        }
    }
    Py_XDECREF(result);
Done:
    Py_XDECREF(arglist);
#ifdef WITH_THREAD
    PyGILState_Release(state);
#endif
}