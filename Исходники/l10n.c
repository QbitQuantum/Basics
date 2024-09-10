void locale_init(char* code)
{
    int locale_id = get_locale_id(code);

#ifdef _WIN_
    CP_OLD = GetConsoleCP();
    if (CP_OLD == 866)
        SetConsoleCP(1251);

    LC_ALL_OLD = getenv(LC_ALL_VAR);

    char var[20];
    sprintf(var, LC_ALL_VAR "=%s\0", locales[locale_id]);
    putenv(var);
#else
    setlocale(LC_ALL, locales[locale_id]);
#endif

	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
}