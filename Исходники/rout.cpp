//********************************************************************
static Bool LoadAlphabet(
        long language,
        char *rec6xxxFilename)
{
    // Загрузка файла REC6.DAT
    FILE *f = NULL;
    int fd;
    char buf[256] = "";
#if defined(WIN32) || defined(__CYGWIN__)
    const char line_end = '\n';
#else
    const char line_end = '\r';
#endif

    ASSERT (language >= 0 && language < PUMA_LANG_TOTAL);

    long sizeAlphabet = 0;

    fd = open_data_file(rec6xxxFilename, O_RDONLY);
    if(fd == -1)
        return FALSE;
    f = fdopen(fd, "rt");
    if (!f)
        return FALSE;

    fgets(buf,sizeof(buf)-1,f);

    sscanf(buf,"%ld",&sizeAlphabet);

    if( sizeAlphabet < 1 ||
        sizeAlphabet > kMaxSizeAlphabet
        )
    {
        fclose(f);
        ERR_LOAD_ALPHABET;
        return FALSE;
    }

    gAT_sizeAlphabet[language] = sizeAlphabet;

    char *upper = gAT_upper[language];
    char *lower = gAT_lower[language];
    char *vowels = gAT_vowels[language];

    fgets(upper,kMaxSizeAlphabet,f);
    fgets(lower,kMaxSizeAlphabet,f);
    fgets(vowels,kMaxSizeAlphabet,f);

    fclose(f);
    f = NULL;

    char *p1 = strchr(upper, line_end);
    char *p2 = strchr(lower, line_end);
    char *p3 = strchr(vowels, line_end);

    if ( p1 ) *p1 = 0;
    if ( p2 ) *p2 = 0;
    if ( p3 ) *p3 = 0;

    if ( (long)strlen(upper) != sizeAlphabet ||
         (long)strlen(lower) != sizeAlphabet ||
         (long)strlen(vowels)> sizeAlphabet
         )
    {
        ERR_LOAD_ALPHABET;
        return FALSE;
    }

    return TRUE;
}