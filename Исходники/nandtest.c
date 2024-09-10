void RetailPrint(wchar_t *pszFormat, ...)
{
    va_list al;
    va_start(al, pszFormat);
    vwprintf(pszFormat, al);
    va_end(al);
}