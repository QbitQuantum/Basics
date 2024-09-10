extern "C" char * __cdecl _strlwr_l (
        char * string,
        _locale_t plocinfo
        )
{
    _strlwr_s_l(string, (size_t)(-1), plocinfo);
    return string;
}