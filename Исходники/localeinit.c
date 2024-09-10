static VALUE
locale_charmap(VALUE (*conv)(const char *))
{
#if defined NO_LOCALE_CHARMAP
# error NO_LOCALE_CHARMAP defined
#elif defined _WIN32 || defined __CYGWIN__
    const char *codeset = 0;
    char cp[SIZEOF_CP_NAME];
# ifdef __CYGWIN__
    const char *nl_langinfo_codeset(void);
    codeset = nl_langinfo_codeset();
# endif
    if (!codeset) {
	UINT codepage = GetConsoleCP();
	if (!codepage) codepage = GetACP();
	CP_FORMAT(cp, codepage);
	codeset = cp;
    }
    return (*conv)(codeset);
#elif defined HAVE_LANGINFO_H
    char *codeset;
    codeset = nl_langinfo(CODESET);
    return (*conv)(codeset);
#else
    return ENCINDEX_US_ASCII;
#endif
}