// Emulate snprintf() on Windows, _snprintf() doesn't zero-terminate the buffer on overflow...
int snprintf(char* buf, size_t len, const char* fmt, ...)
{
    va_list ap;
    int n;

    va_start(ap, fmt);
    n = _vsprintf_p(buf, len, fmt, ap);
    va_end(ap);

    /* It's a sad fact of life that no one ever checks the return value of
    * snprintf(). Zero-terminating the buffer hopefully reduces the risk
    * of gaping security holes.
    */
    if (n < 0)
    {
        if (len > 0)
        {
            buf[0] = '\0';
        }
    }
    return n;
}