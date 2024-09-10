extern "C" int __cdecl _wctomb_l (
        char *s,
        wchar_t wchar,
        _locale_t plocinfo
        )
{
    int retval = -1;
    errno_t e;
    _LocaleUpdate _loc_update(plocinfo);

    e = _wctomb_s_l(&retval, s, _loc_update.GetLocaleT()->locinfo->mb_cur_max, wchar, _loc_update.GetLocaleT());
    return (e == 0 ? retval : -1);
}