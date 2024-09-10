static LONG WINAPI
faulthandler_exc_handler(struct _EXCEPTION_POINTERS *exc_info)
{
    const int fd = fatal_error.fd;
    DWORD code = exc_info->ExceptionRecord->ExceptionCode;
    DWORD flags = exc_info->ExceptionRecord->ExceptionFlags;

    /* only log fatal exceptions */
    if (flags & EXCEPTION_NONCONTINUABLE) {
        /* call the next exception handler */
        return EXCEPTION_CONTINUE_SEARCH;
    }

    PUTS(fd, "Windows fatal exception: ");
    switch (code)
    {
    /* only format most common errors */
    case EXCEPTION_ACCESS_VIOLATION: PUTS(fd, "access violation"); break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO: PUTS(fd, "float divide by zero"); break;
    case EXCEPTION_FLT_OVERFLOW: PUTS(fd, "float overflow"); break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO: PUTS(fd, "int divide by zero"); break;
    case EXCEPTION_INT_OVERFLOW: PUTS(fd, "integer overflow"); break;
    case EXCEPTION_IN_PAGE_ERROR: PUTS(fd, "page error"); break;
    case EXCEPTION_STACK_OVERFLOW: PUTS(fd, "stack overflow"); break;
    default:
        PUTS(fd, "code ");
        _Py_DumpDecimal(fd, code);
    }
    PUTS(fd, "\n\n");

    if (code == EXCEPTION_ACCESS_VIOLATION) {
        /* disable signal handler for SIGSEGV */
        size_t i;
        for (i=0; i < faulthandler_nsignals; i++) {
            fault_handler_t *handler = &faulthandler_handlers[i];
            if (handler->signum == SIGSEGV) {
                faulthandler_disable_fatal_handler(handler);
                break;
            }
        }
    }

    faulthandler_dump_traceback(fd, fatal_error.all_threads,
                                fatal_error.interp);

    /* call the next exception handler */
    return EXCEPTION_CONTINUE_SEARCH;
}