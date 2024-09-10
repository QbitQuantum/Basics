static PyThreadState *
new_threadstate(PyInterpreterState *interp, int init)
{
    PyThreadState *tstate = (PyThreadState *)PyMem_RawMalloc(sizeof(PyThreadState));

    if (_PyThreadState_GetFrame == NULL)
        _PyThreadState_GetFrame = threadstate_getframe;

    if (tstate != NULL) {
        tstate->interp = interp;

        tstate->frame = NULL;
        tstate->recursion_depth = 0;
        tstate->overflowed = 0;
        tstate->recursion_critical = 0;
        tstate->tracing = 0;
        tstate->use_tracing = 0;
        tstate->gilstate_counter = 0;
        tstate->async_exc = NULL;
#ifdef WITH_THREAD
        tstate->thread_id = PyThread_get_thread_ident();
#else
        tstate->thread_id = 0;
#endif

        tstate->dict = NULL;

        tstate->curexc_type = NULL;
        tstate->curexc_value = NULL;
        tstate->curexc_traceback = NULL;

        tstate->exc_type = NULL;
        tstate->exc_value = NULL;
        tstate->exc_traceback = NULL;

        tstate->c_profilefunc = NULL;
        tstate->c_tracefunc = NULL;
        tstate->c_profileobj = NULL;
        tstate->c_traceobj = NULL;

        tstate->trash_delete_nesting = 0;
        tstate->trash_delete_later = NULL;
        tstate->on_delete = NULL;
        tstate->on_delete_data = NULL;

        if (init)
            _PyThreadState_Init(tstate);

        HEAD_LOCK();
        tstate->prev = NULL;
        tstate->next = interp->tstate_head;
        if (tstate->next)
            tstate->next->prev = tstate;
        interp->tstate_head = tstate;
        HEAD_UNLOCK();

#if defined _MSC_VER && _MSC_VER >= 1900
        /* Issue #23524: Temporary fix to disable termination due to invalid parameters */
        _set_thread_local_invalid_parameter_handler((_invalid_parameter_handler)_Py_silent_invalid_parameter_handler);
#endif
    }

    return tstate;
}