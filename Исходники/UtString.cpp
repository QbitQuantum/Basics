UtString::UtString(const char *format, va_list alist)
{
    mpBuffer = NULL;
    VPrintF(format, alist);
}