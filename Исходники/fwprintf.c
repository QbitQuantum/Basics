int __cdecl _fwprintf_p_l (
        FILE *str,
        const wchar_t *format,
        _locale_t plocinfo,
        ...
        )
{
    va_list arglist;

    va_start(arglist, plocinfo);

    return _vfwprintf_p_l(str, format, plocinfo, arglist);
}