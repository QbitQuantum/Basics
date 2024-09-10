PyMODINIT_FUNC
PyInit__multiprocess(void)
{
    PyObject *module, *temp, *value;

    /* Initialize module */
    module = PyModule_Create(&multiprocessing_module);
    if (!module)
        return NULL;

    /* Get copy of objects from pickle */
    temp = PyImport_ImportModule("dill");
    if (!temp)
        temp = PyImport_ImportModule(PICKLE_MODULE);
    if (!temp)
        return NULL;
    pickle_dumps = PyObject_GetAttrString(temp, "dumps");
    pickle_loads = PyObject_GetAttrString(temp, "loads");
    pickle_protocol = PyObject_GetAttrString(temp, "DEFAULT_PROTOCOL");
    if (!pickle_protocol)
        pickle_protocol = PyObject_GetAttrString(temp, "HIGHEST_PROTOCOL");
    Py_XDECREF(temp);

    /* Get copy of BufferTooShort */
    temp = PyImport_ImportModule("multiprocess");
    if (!temp)
        return NULL;
    BufferTooShort = PyObject_GetAttrString(temp, "BufferTooShort");
    Py_XDECREF(temp);

    /* Add connection type to module */
    if (PyType_Ready(&ConnectionType) < 0)
        return NULL;
    Py_INCREF(&ConnectionType);
    PyModule_AddObject(module, "Connection", (PyObject*)&ConnectionType);

#if defined(MS_WINDOWS) ||                                              \
  (defined(HAVE_SEM_OPEN) && !defined(POSIX_SEMAPHORES_NOT_ENABLED))
    /* Add SemLock type to module */
    if (PyType_Ready(&SemLockType) < 0)
        return NULL;
    Py_INCREF(&SemLockType);
    {
        PyObject *py_sem_value_max;
        /* Some systems define SEM_VALUE_MAX as an unsigned value that
         * causes it to be negative when used as an int (NetBSD). */
        if ((int)(SEM_VALUE_MAX) < 0)
            py_sem_value_max = PyLong_FromLong(INT_MAX);
        else
            py_sem_value_max = PyLong_FromLong(SEM_VALUE_MAX);
        if (py_sem_value_max == NULL)
            return NULL;
        PyDict_SetItemString(SemLockType.tp_dict, "SEM_VALUE_MAX",
                             py_sem_value_max);
    }
    PyModule_AddObject(module, "SemLock", (PyObject*)&SemLockType);
#endif

#ifdef MS_WINDOWS
    /* Add PipeConnection to module */
    if (PyType_Ready(&PipeConnectionType) < 0)
        return NULL;
    Py_INCREF(&PipeConnectionType);
    PyModule_AddObject(module, "PipeConnection",
                       (PyObject*)&PipeConnectionType);

    /* Initialize win32 class and add to multiprocessing */
    temp = create_win32_namespace();
    if (!temp)
        return NULL;
    PyModule_AddObject(module, "win32", temp);

    /* Initialize the event handle used to signal Ctrl-C */
    sigint_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!sigint_event) {
        PyErr_SetFromWindowsErr(0);
        return NULL;
    }
    if (!SetConsoleCtrlHandler(ProcessingCtrlHandler, TRUE)) {
        PyErr_SetFromWindowsErr(0);
        return NULL;
    }
#endif

    /* Add configuration macros */
    temp = PyDict_New();
    if (!temp)
        return NULL;

#define ADD_FLAG(name)                                            \
    value = Py_BuildValue("i", name);                             \
    if (value == NULL) { Py_DECREF(temp); return NULL; }          \
    if (PyDict_SetItemString(temp, #name, value) < 0) {           \
        Py_DECREF(temp); Py_DECREF(value); return NULL; }                 \
    Py_DECREF(value)

#if defined(HAVE_SEM_OPEN) && !defined(POSIX_SEMAPHORES_NOT_ENABLED)
    ADD_FLAG(HAVE_SEM_OPEN);
#endif
#ifdef HAVE_SEM_TIMEDWAIT
    ADD_FLAG(HAVE_SEM_TIMEDWAIT);
#endif
#ifdef HAVE_FD_TRANSFER
    ADD_FLAG(HAVE_FD_TRANSFER);
#endif
#ifdef HAVE_BROKEN_SEM_GETVALUE
    ADD_FLAG(HAVE_BROKEN_SEM_GETVALUE);
#endif
#ifdef HAVE_BROKEN_SEM_UNLINK
    ADD_FLAG(HAVE_BROKEN_SEM_UNLINK);
#endif

    if (PyModule_AddObject(module, "flags", temp) < 0)
        return NULL;

    return module;
}