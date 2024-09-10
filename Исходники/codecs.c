PyObject *_PyCodec_Lookup(const char *encoding)
{
    PyInterpreterState *interp;
    PyObject *result, *args = NULL, *v;
    Py_ssize_t i, len;

    if (encoding == NULL) {
        PyErr_BadArgument();
        goto onError;
    }

    interp = PyThreadState_GET()->interp;
    if (interp->codec_search_path == NULL && _PyCodecRegistry_Init())
        goto onError;

    /* Convert the encoding to a normalized Python string: all
       characters are converted to lower case, spaces and hyphens are
       replaced with underscores. */
    v = normalizestring(encoding);
    if (v == NULL)
        goto onError;
    PyString_InternInPlace(&v);

    /* First, try to lookup the name in the registry dictionary */
    result = PyDict_GetItem(interp->codec_search_cache, v);
    if (result != NULL) {
        Py_INCREF(result);
        Py_DECREF(v);
        return result;
    }

    /* Next, scan the search functions in order of registration */
    args = PyTuple_New(1);
    if (args == NULL)
        goto onError;
    PyTuple_SET_ITEM(args,0,v);

    len = PyList_Size(interp->codec_search_path);
    if (len < 0)
        goto onError;
    if (len == 0) {
        PyErr_SetString(PyExc_LookupError,
                        "no codec search functions registered: "
                        "can't find encoding");
        goto onError;
    }

    for (i = 0; i < len; i++) {
        PyObject *func;

        func = PyList_GetItem(interp->codec_search_path, i);
        if (func == NULL)
            goto onError;
        result = PyEval_CallObject(func, args);
        if (result == NULL)
            goto onError;
        if (result == Py_None) {
            Py_DECREF(result);
            continue;
        }
        if (!PyTuple_Check(result) || PyTuple_GET_SIZE(result) != 4) {
            PyErr_SetString(PyExc_TypeError,
                            "codec search functions must return 4-tuples");
            Py_DECREF(result);
            goto onError;
        }
        break;
    }
    if (i == len) {
        /* XXX Perhaps we should cache misses too ? */
        PyErr_Format(PyExc_LookupError,
                     "unknown encoding: %s", encoding);
        goto onError;
    }

    /* Cache and return the result */
    PyDict_SetItem(interp->codec_search_cache, v, result);
    Py_DECREF(args);
    return result;

 onError:
    Py_XDECREF(args);
    return NULL;
}