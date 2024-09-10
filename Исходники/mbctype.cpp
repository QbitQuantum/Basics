static int getSystemCP (int codepage)
{
    _locale_t plocinfo = nullptr;
    _LocaleUpdate _loc_update(plocinfo);
    fSystemSet = 0;

    /* get system code page values if requested */

    if (codepage == _MB_CP_OEM)
    {
        fSystemSet = 1;
        return GetOEMCP();
    }
    else if (codepage == _MB_CP_ANSI)
    {
        fSystemSet = 1;
        return GetACP();
    }
    else if (codepage == _MB_CP_LOCALE)
    {
        fSystemSet = 1;
        return _loc_update.GetLocaleT()->locinfo->_public._locale_lc_codepage;
    }

    return codepage;
}