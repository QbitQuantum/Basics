tmErrorCode_t tmsysOM3912Print(UInt32 level, const char* format, ...)
{
    tmErrorCode_t   err = TM_OK;

#ifdef NXPFEV2_DBG_MSG
    va_list         args;
    int             len = 0;
    char            *buffer = Null;

    va_start( args, format );
    len = _vscprintf(format, args ) + 1;
    buffer = (char *)malloc(len * sizeof(char));

    (void)vsprintf_s(buffer, len, format, args);

    if(pDbgMsgCallBack != Null)
    {
        err = pDbgMsgCallBack(level, buffer);
    }

    free(buffer);
#else
    static char     buf[PRINT_BUFFER_SIZE] = "\0";
    va_list         ap;

    if(level<DEBUGLVL_VERBOSE)
    {
        va_start(ap, format);
        (void)vsnprintf(buf, PRINT_BUFFER_SIZE, format, ap);
        va_end(ap);

#ifdef CUSTOMER_IMPLEMENTATION
        /* Customer implementation */
        tmdlPrint(buf);
#endif
    }
#endif

    return err;
}