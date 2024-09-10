const char * GetBestMatchedLanguageString()
{
 //   LCID localeid = GetSystemDefaultLCID();
    LANGID langid = GetUserDefaultUILanguage ();
    switch (langid & 0xF) {
    case 0x04: // zh related
        return "cn";
    default :
        return "en";
    }

}