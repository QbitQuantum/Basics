extern "C" wchar_t * __cdecl _wcsupr_l (
        wchar_t * wsrc,
        _locale_t plocinfo
        )
{
    _wcsupr_s_l(wsrc, (size_t)(-1), plocinfo);
    return wsrc;
}