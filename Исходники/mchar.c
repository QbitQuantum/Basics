const char*
default_codeset (void)
{
    const char* fromcode = 0;

#if defined HAVE_LOCALE_CHARSET
    debug_printf ("Using locale_charset() to get system codeset.\n");
    fromcode = locale_charset ();
#elif defined HAVE_LANGINFO_CODESET
    debug_printf ("Using nl_langinfo() to get system codeset.\n");
    fromcode = nl_langinfo (CODESET);
#else
    debug_printf ("No way to get system codeset.\n");
#endif
    if (!fromcode || !fromcode[0]) {
	debug_printf ("No default codeset, using ISO-8859-1.\n");
	fromcode = "ISO-8859-1";
    } else {
	debug_printf ("Found default codeset %s\n", fromcode);
    }

#if defined (WIN32)
    {
	/* This is just for debugging */
	LCID lcid;
	lcid = GetSystemDefaultLCID ();
	debug_printf ("SystemDefaultLCID: %04x\n", lcid);
	lcid = GetUserDefaultLCID ();
	debug_printf ("UserDefaultLCID: %04x\n", lcid);
    }
#endif

#if defined HAVE_ICONV
    debug_printf ("Have iconv.\n");
#else
    debug_printf ("No iconv.\n");
#endif

    return fromcode;
}