int ifprintf(IFILE output, char * format, ...)
{
    String buffer;

    va_list  ap;
    va_start(ap, format);

    buffer.vprintf(format, ap);

    va_end(ap);

    return ::ifwrite(output, (const char *) buffer, buffer.Length());
}