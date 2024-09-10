wchar_t *os_wcstok(wchar_t *_pwstData, const wchar_t *_pwstDelim, wchar_t** _pswtState)
{
#ifndef _MSC_VER
    return wcstok(_pwstData, _pwstDelim, _pswtState);
#else
    return wcstok(_pwstData, _pwstDelim);
#endif
}