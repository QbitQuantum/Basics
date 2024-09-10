void print_buf_internal(voidpf opaque, voidpf stream, char *format, ...)
{
    ourstream_t *streamio = (ourstream_t *)stream;
    va_list arglist;
    PRINTF("Buf stream %p - ", streamio);
    va_start(arglist, format);
    VPRINTF(format, arglist);
    va_end(arglist);
}