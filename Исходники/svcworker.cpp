void SvcLogger::Printf(const CHAR *format, ...)
{
    StackSString s;

    va_list args;
    va_start(args, format);
    s.VPrintf(format, args);
    va_end(args);

    if (pCorSvcLogger)
    {
        LogHelper(s);
    }
    else
    {
        wprintf( W("%s"), s.GetUnicode() );
    }
}