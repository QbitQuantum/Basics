extern "C" int __cdecl _wcsicoll (
        const wchar_t *_string1,
        const wchar_t *_string2
        )
{
    if (!__acrt_locale_changed())
    {
        wchar_t f,l;

        /* validation section */
        _VALIDATE_RETURN(_string1 != nullptr, EINVAL, _NLSCMPERROR );
        _VALIDATE_RETURN(_string2 != nullptr, EINVAL, _NLSCMPERROR );

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
    else
    {
        return _wcsicoll_l(_string1, _string2, nullptr);
    }

}