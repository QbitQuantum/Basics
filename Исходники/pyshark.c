static PyObject *
pyshark_iter(PyObject *self, PyObject *args)
{
    gsize i;
    char *filename;
    PyObject *keylistobj;
    const char *dfilter;
    char *decode_as = NULL;
    pyshark_Iter *p;

    gint ret;

    /* NB: Automatic sanity checks for 1st, 3rd, and optional 4th argument */
    if(!PyArg_ParseTuple(args, "sOs|s", &filename, &keylistobj, &dfilter, &decode_as)) {
        return NULL;
    }

    /* NB: Explicit sanity checks needed for the second argument */
    if(!PyList_Check(keylistobj)) {
        PyErr_SetString(PyExc_TypeError, "Second argument must be a list of wireshark fieldnames");
        return NULL;
    }

    for(i = 0; i < PyList_Size(keylistobj); i++) {
        PyObject *fieldnameobj = PyList_GetItem(keylistobj, i);

        if (!PyString_Check(fieldnameobj)) {
            PyErr_SetString(PyExc_TypeError, "All items in second argument list must be strings");
            return NULL;
        }
    }

    /* NB: See PyObject.ob_type in http://docs.python.org/c-api/typeobj.html
       for more info
     */
    pyshark_IterType.ob_type = &PyType_Type; //pyshark_Iter;

    /* NB: look at bottom of http://docs.python.org/c-api/type.html */
    ret = PyType_Ready(&pyshark_IterType);
    if(ret) {
        return NULL;
    }

    /* Create our iterator object */
    p = PyObject_New(pyshark_Iter, &pyshark_IterType);
    if(!p) {
        return NULL;
    }

    /* Initialize all our data structures in the iterator object to 0. This makes it easier
       to implement deallocation logic for both expected and unexpected cases.
     */
    p->clean = FALSE;
    p->decode_as = NULL;
    p->stdata = NULL;
    p->nwpykeylist = NULL;
    p->wpykeyhash = NULL;
    p->asel = FALSE;
    p->show_empty_fields = FALSE;

    if(!PyObject_Init((PyObject *)p, &pyshark_IterType)) {
        Py_DECREF(p);
        return NULL;
    }

    p->stdata = stdata_new();
    if(!p->stdata) {
        Py_DECREF(p);
        return NULL;
    }

    p->wpykeyhash = g_hash_table_new(g_str_hash, g_str_equal);

    p->nwpykeylist = g_ptr_array_new();

    /*
      Iterate through the Python List and add to either fieldnames OR wfieldnames
     depending on presence of a '*' in the string
    */
    for(i = 0; i < PyList_Size(keylistobj); i++) {
        /* NB: we know these are not NULL because of our sanity checks above */
        PyObject *keyobj = PyList_GetItem(keylistobj, i);

        /* Check for wildcard entries, e.g. "*", "ip.*", "eth.*", etc. */
        const gchar *key = PyString_AsString(keyobj);
        gchar *ptr = g_strstr_len(key, strnlen(key, 100), "*");

        if(ptr) {
            /* We have a fieldname with a wildcard in it
             *
             * Use pointer arithmetic to figure out the length
             * TODO: better way to do this, maybe?
             */
            gsize prefix_len = (gsize)ptr - (gsize)key;

            g_ptr_array_add(p->stdata->wfieldnames, g_strndup(key, prefix_len));
        }
        else {
            /*
             * Non-wildcard entry.
             */
            g_ptr_array_add(p->stdata->fieldnames, PyString_AsString(keyobj));

            /* On the python-module side of things, keep a list of python objects,
               one for each non-wildcard fieldname to be processed by sharktools.
               NB: the index between entries in p->{stdata->fieldnames,nwpykeylist}
               MUST be the same.
            */
            g_ptr_array_add(p->nwpykeylist, keyobj);

            /* The above array_add() call doesn't deep copy the fieldname,
               let's increment the refcount, and decrement it when we cleanup.
               NB: also used for our copy of the key in p->nwpykeylist
            */
            Py_INCREF(keyobj);
        }
    }

    /* If there is a decode_as string set, add it */
    if(decode_as) {
        dprintf("decode as string added: %s\n", decode_as);
        ret = sharktools_add_decode_as(decode_as);
        if(ret == FALSE) {
            dprintf("%s\n", sharktools_errmsg);
            PyErr_SetString(PySharkError, sharktools_errmsg);
            Py_DECREF(p);
            return NULL;
        }
        /* NB: Add to object state; we'll need to remove it later */
        p->decode_as = strndup(decode_as, strlen(decode_as));
    }

    /*
     * Create and initialize sharktools' state
     */
    ret = sharktools_iter_init(p->stdata, filename, strdup(dfilter));
    if(ret < 0) {
        dprintf("%s\n", sharktools_errmsg);
        PyErr_SetString(PySharkError, sharktools_errmsg);
        Py_DECREF(p);
        return NULL;
    }

    /* NB: We are dirty */
    p->clean = FALSE;

    return (PyObject *)p;
}