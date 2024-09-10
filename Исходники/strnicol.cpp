extern "C" int __cdecl _strnicoll (
        const char *_string1,
        const char *_string2,
        size_t count
        )
{
    if (!__acrt_locale_changed())
    {
        return _strnicmp(_string1, _string2, count);
    }
    else
    {
        return _strnicoll_l(_string1, _string2, count, nullptr);
    }
}