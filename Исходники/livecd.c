static VOID
CreateLanguagesList(HWND hwnd)
{
    WCHAR langSel[255];

    hList = hwnd;
    bSpain = FALSE;
    EnumSystemLocalesW(LocalesEnumProc, LCID_SUPPORTED);

    /* Select current locale */
    /* or should it be System and not user? */
    GetLocaleInfoW(GetUserDefaultLCID(), LOCALE_SLANGUAGE, langSel, sizeof(langSel)/sizeof(WCHAR));

    SendMessageW(hList,
                 CB_SELECTSTRING,
                 -1,
                 (LPARAM)langSel);
}