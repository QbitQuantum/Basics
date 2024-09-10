void exception_catcher::set_process_exception_handlers()
{
    // Install top-level SEH handler
    SetUnhandledExceptionFilter(catched_seh_handler);

    // Catch pure virtual function calls.
    // Because there is one _purecall_handler for the whole process,
    // calling this function immediately impacts all threads. The last
    // caller on any thread sets the handler.
    // http://msdn.microsoft.com/en-us/library/t296ys27.aspx
    _set_purecall_handler(catched_pure_call_handler);

    // Catch new operator memory allocation exceptions
    _set_new_handler(catched_new_handler);

    // Catch invalid parameter exceptions.
    _set_invalid_parameter_handler(catched_invalid_parameter_handler);

    // Set up C++ signal handlers

    _set_abort_behavior(_CALL_REPORTFAULT, _CALL_REPORTFAULT);

    // Catch an abnormal program termination
    signal(SIGABRT, catched_sigabrt_handler);

    // Catch illegal instruction handler
    signal(SIGINT, catched_sigint_handler);

    // Catch a termination request
    signal(SIGTERM, catched_sigterm_handler);
}