extern "C" unsigned long long _CRTIMP __cdecl _wcstoull_l (
        const wchar_t *nptr,
        wchar_t **endptr,
        int ibase,
        _locale_t plocinfo
        )
{
    return _wcstoui64_l(nptr, endptr, ibase, plocinfo);
}