extern "C" int __cdecl _wcsicoll_l (
        const wchar_t *_string1,
        const wchar_t *_string2,
        _locale_t plocinfo
        )
{
    int ret;
    wchar_t f, l;
    _LocaleUpdate _loc_update(plocinfo);

    /* validation section */
    _VALIDATE_RETURN(_string1 != NULL, EINVAL, _NLSCMPERROR );
    _VALIDATE_RETURN(_string2 != NULL, EINVAL, _NLSCMPERROR );

    if ( _loc_update.GetLocaleT()->locinfo->lc_handle[LC_COLLATE] == _CLOCALEHANDLE )
    {
        do
        {
            f = __ascii_towlower(*_string1);
            l = __ascii_towlower(*_string2);
            _string1++;
            _string2++;
        }
        while ( (f) && (f == l) );

        return (int)(f - l);
    }

    if ( 0 == (ret = __crtCompareStringW(
                    _loc_update.GetLocaleT(),
                    _loc_update.GetLocaleT()->locinfo->lc_handle[LC_COLLATE],
                    SORT_STRINGSORT | NORM_IGNORECASE,
                    _string1,
                    -1,
                    _string2,
                    -1,
                    _loc_update.GetLocaleT()->locinfo->lc_codepage)) )
    {
        errno = EINVAL;
        return _NLSCMPERROR;
    }

    return (ret - 2);
}