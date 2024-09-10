/**
 * Yet another assertion handler.
 */
void DEBUG_AssertFormat(const char * file, long line, Str format, ...)
{
    char msg[512];
#ifdef UNICODE
    Char msg2[COUNT(msg)];
#else /* !UNICODE */
#  define msg2 msg
#endif /* UNICODE */

#if defined(_WIN32) && !defined(_NT_KERNEL)
    ULONG lastError = GetLastError();
#  ifdef _USE_EXCEPTION_HANDLING
    __try {
#  endif /* _USE_EXCEPTION_HANDLING */
#endif /* _WIN32) && !_NT_KERNEL */
        int n;
        va_list va;
        va_start(va, format);

        /* format the message */
        n = Vsnprintf(msg2,COUNT(msg2),format,va);
#ifdef UNICODE
        msg[0] = 0;
        msg2[COUNT(msg2)-1] = 0;
        wcstombs(msg, msg2, COUNT(msg));
        msg[COUNT(msg)-1] = 0;
#endif /* UNICODE */

        /* if the output string is REALLY long, terminate it with ... */
        if (n >= COUNT(msg)-1 || n < 0) {
            n = COUNT(msg)-1;
            msg[n--] = 0;
            msg[n--] = '.'; 
            msg[n--] = '.'; 
            msg[n--] = '.';
            msg[n--] = ' ';
        } else {
            msg[COUNT(msg)-1] = 0;
        }

        va_end(va);
#if defined(_WIN32) && !defined(_NT_KERNEL)
#  ifdef _USE_EXCEPTION_HANDLING
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        /* NOTE: ASSMSG1 macro would recursively invoke this function */
        TRACE1("EXCEPTION %08lX in DEBUG_AssertFormat\n",GetExceptionCode());
        ASSMSG("EXCEPTION in DEBUG_AssertFormat");
    }
#  endif /* _USE_EXCEPTION_HANDLING */
    DEBUG_Assert(msg, file, line);
    SetLastError(lastError);
#else
    DEBUG_Assert(msg, file, line);
#endif /* _WIN32) && !_NT_KERNEL */
}