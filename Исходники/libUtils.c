void
say(const char *fmt, ...)
{
    va_list ap;

    escape_curses();
    va_start(ap, fmt);
#ifdef HAVE_BCI
    vprintf_s(fmt, ap);
#else
    vprintf(fmt, ap);
#endif
    va_end(ap);
    fflush(stdout);
}