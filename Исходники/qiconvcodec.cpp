iconv_t QIconvCodec::createIconv_t(const char *to, const char *from)
{
    Q_ASSERT((to == 0 && from != 0) || (to != 0 && from == 0));

    iconv_t cd = (iconv_t) -1;
#if defined(__GLIBC__) || defined(GNU_LIBICONV)
    // both GLIBC and libgnuiconv will use the locale's encoding if from or to is an empty string
    static const char empty_codeset[] = "";
    const char *codeset = empty_codeset;
    cd = iconv_open(to ? to : codeset, from ? from : codeset);
#else
    char *codeset = 0;
#endif

#if defined(_XOPEN_UNIX) && !defined(Q_OS_QNX6) && !defined(Q_OS_OSF)
    if (cd == (iconv_t) -1) {
        codeset = nl_langinfo(CODESET);
        if (codeset)
            cd = iconv_open(to ? to : codeset, from ? from : codeset);
    }
#endif

    if (cd == (iconv_t) -1) {
        // Very poorly defined and followed standards causes lots of
        // code to try to get all the cases... This logic is
        // duplicated in QTextCodec, so if you change it here, change
        // it there too.

        // Try to determine locale codeset from locale name assigned to
        // LC_CTYPE category.

        // First part is getting that locale name.  First try setlocale() which
        // definitely knows it, but since we cannot fully trust it, get ready
        // to fall back to environment variables.
        char * ctype = qstrdup(setlocale(LC_CTYPE, 0));

        // Get the first nonempty value from $LC_ALL, $LC_CTYPE, and $LANG
        // environment variables.
        char * lang = qstrdup(qgetenv("LC_ALL").constData());
        if (!lang || lang[0] == 0 || strcmp(lang, "C") == 0) {
            if (lang) delete [] lang;
            lang = qstrdup(qgetenv("LC_CTYPE").constData());
        }
        if (!lang || lang[0] == 0 || strcmp(lang, "C") == 0) {
            if (lang) delete [] lang;
            lang = qstrdup(qgetenv("LANG").constData());
        }

        // Now try these in order:
        // 1. CODESET from ctype if it contains a .CODESET part (e.g. en_US.ISO8859-15)
        // 2. CODESET from lang if it contains a .CODESET part
        // 3. ctype (maybe the locale is named "ISO-8859-1" or something)
        // 4. locale (ditto)
        // 5. check for "@euro"

        // 1. CODESET from ctype if it contains a .CODESET part (e.g. en_US.ISO8859-15)
        codeset = ctype ? strchr(ctype, '.') : 0;
        if (codeset && *codeset == '.') {
            ++codeset;
            cd = iconv_open(to ? to : codeset, from ? from : codeset);
        }

        // 2. CODESET from lang if it contains a .CODESET part
        codeset = lang ? strchr(lang, '.') : 0;
        if (cd == (iconv_t) -1 && codeset && *codeset == '.') {
            ++codeset;
            cd = iconv_open(to ? to : codeset, from ? from : codeset);
        }

        // 3. ctype (maybe the locale is named "ISO-8859-1" or something)
        if (cd == (iconv_t) -1 && ctype && *ctype != 0 && strcmp (ctype, "C") != 0)
            cd = iconv_open(to ? to : ctype, from ? from : ctype);


        // 4. locale (ditto)
        if (cd == (iconv_t) -1 && lang && *lang != 0)
            cd = iconv_open(to ? to : lang, from ? from : lang);

        // 5. "@euro"
        if ((cd == (iconv_t) -1 && ctype && strstr(ctype, "@euro")) || (lang && strstr(lang, "@euro")))
            cd = iconv_open(to ? to : "ISO8859-15", from ? from : "ISO8859-15");

        delete [] ctype;
        delete [] lang;
    }

    return cd;
}