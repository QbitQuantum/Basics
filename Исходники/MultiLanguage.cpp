LANGID CMultiLanguage::DetectLangID()
{
    LANGID langid = 0;
    int nPrimaryLang = 0;
    int nSubLang = 0;
    LCID lcid = 0;
    int nLocales = 0;

    langid = GetUserDefaultLangID();    // WinNT3.1/95 and later
    AddLangId( langid );
    TRACE(_T("CMultiLanguage::GetUserDefaultLangID() 1st/2nd = %0X\n"),
          langid );

    LANGID langSysid = GetSystemDefaultLangID();    // WinNT3.1/95 and later
    AddLangId( langSysid );
    TRACE(_T("CMultiLanguage::GetSystemDefaultLangID() 3rd/4th = %0X\n"),
          langid );

    return langid;
}