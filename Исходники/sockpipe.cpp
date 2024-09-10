void die(char * message,...)
{
    char    buf[1024];
    va_list args;

    va_start(args, message);
#if defined(SAFESTR)
    vsnprintf_s(buf, sizeof(buf), sizeof(buf) - 1, message, args);
#else
    _vsnprintf(buf, sizeof(buf), message, args);
#endif
    fprintf(stderr, "%s\n", buf);
    if (g_log)
    {
        g_log->Log(0, "die", buf);
    }
    my_exit(1);
}