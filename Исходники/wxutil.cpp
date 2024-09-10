int WINAPIV wsprintfWInternal(
    LPWSTR wszOut, LPCWSTR pszFmt, ...) {
    va_list va;
    va_start(va, pszFmt);
    int i = wvsprintfW(wszOut, pszFmt, va);
    va_end(va);
    return i;
}