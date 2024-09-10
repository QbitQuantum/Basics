void CCmdBase::RuntimeError(PCWSTR pszFormat, ...)
{
    _fError = TRUE;
    va_list args;
    va_start(args, pszFormat);

    wprintf(L"ERROR - ");
    vwprintf(pszFormat, args);

    va_end(args);
}