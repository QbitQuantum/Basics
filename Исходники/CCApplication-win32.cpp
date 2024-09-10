const char * Application::getCurrentLanguageCode()
{
    LANGID lid = GetUserDefaultUILanguage();
    const LCID locale_id = MAKELCID(lid, SORT_DEFAULT);
    static char code[3] = { 0 };
    GetLocaleInfoA(locale_id, LOCALE_SISO639LANGNAME, code, sizeof(code));
    code[2] = '\0';
    return code;
}