static void
debug(wchar_t* format, ...)
{
    if (debug_fp != NULL) {
        va_list ap;
        va_start(ap, format);
        vfwprintf(debug_fp, format, ap);
        va_end(ap);
    }
}