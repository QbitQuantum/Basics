extern "C" int __cdecl _stricoll (
        const char *_string1,
        const char *_string2
        )
{
    if (!__acrt_locale_changed())
    {
        return _stricmp(_string1, _string2);
    }
    else
    {
        return _stricoll_l(_string1, _string2, nullptr);
    }

}