static void
init_locale(int argc, char *argv[])
{
    char *lang = NULL, *p = NULL;
	char buffer[64];


	strcpy(language,"i18n/");
	if (argc == 2) {
		strcat(language, argv[1]);
        if (is_valid_locale(language))
            return;
	}
	PDL_GetLanguage(buffer, 64);
	//Error("the pdl language is:%s\n",buffer);
    //lang = getenv("LANG");
    lang = buffer;
	lang = strtok(buffer,"_");
	if (lang != NULL) {
        strcpy(language,"i18n/");
        strcat(language, lang);
		//Error("lang defined language is:%s\n",language);
        if (is_valid_locale(language))
            return;
        while ((p = strrchr(language, '.')) != NULL) {
            *p = 0;
            if (is_valid_locale(language))
                return;
        }
        if ((p = strrchr(language, '_')) != NULL) {
            *p = 0;
            if (is_valid_locale(language))
                return;
        }
    }

#ifdef WIN32
    {
        LCID lcid = GetThreadLocale();
        strcpy(language,"i18n/");
        GetLocaleInfoA(lcid, LOCALE_SISO639LANGNAME, 
                       language + strlen(language), sizeof(language));
        p = language + strlen(language);
        strcat(language, "_");
        GetLocaleInfo(lcid, LOCALE_SISO3166CTRYNAME, 
                      language + strlen(language), sizeof(language));
        Debug("locale %s", language);
        if (is_valid_locale(language))
            return;
        *p = 0;
        if (is_valid_locale(language))
            return;
    }
#endif /* WIN32 */

    /* last resort - use the english locale */
	//Error("default locale path:%s\n",DEFAULT_LOCALE_PATH);
    strcpy(language, DEFAULT_LOCALE_PATH);
	//Error("default language is:%s\n",language);
}