char	*
_XkbGetCharset(void)
{
    /*
     * PAGE USAGE TUNING: explicitly initialize to move these to data
     * instead of bss
     */
    static char buf[100] = { 0 };
    char lang[256];
    char *start,*tmp,*end,*next,*set;
    char *country,*charset;
    char *locale;

    tmp = getenv( "_XKB_CHARSET" );
    if ( tmp )
	return tmp;
    locale = setlocale(LC_CTYPE,NULL);

    if ( locale == NULL )
	return NULL;

    if (strlen(locale) >= sizeof(lang))
	return NULL;

    for (tmp = lang; *tmp = *locale++; tmp++) {
	if (isupper(*tmp))
	    *tmp = tolower(*tmp);
    }
    country = strchr( lang, '_');
    if ( country ) {
	*country++ = '\0';
	charset = strchr( country, '.' );
	if ( charset )	*charset++ = '\0';
	if ( charset ) {
	    strncpy(buf,charset,99);
	    buf[99] = '\0';
	    return buf;
	}
    }
    else {
	charset = NULL;
    }

    if ((tmp = getenv("_XKB_LOCALE_CHARSETS"))!=NULL) {
	start = _XkbAlloc(strlen(tmp) + 1);
	strcpy(start, tmp);
	tmp = start;
    } else {
	struct stat sbuf;
	FILE *file;
#ifndef __UNIXOS2__
	char *cf = CHARSET_FILE;
#else
        char *cf = __XOS2RedirRoot(CHARSET_FILE);
#endif

#ifndef S_ISREG
# define S_ISREG(mode)   (((mode) & S_IFMT) == S_IFREG)
#endif

	if ( (stat(cf,&sbuf)==0) && S_ISREG(sbuf.st_mode) &&
	    (file = fopen(cf,"r")) ) {
	    tmp = _XkbAlloc(sbuf.st_size+1);
	    if (tmp!=NULL) {
		sbuf.st_size = (long)fread(tmp,1,sbuf.st_size,file);
		tmp[sbuf.st_size] = '\0';
	    }
	    fclose(file);
	}
    }

    if ( tmp == NULL ) {
	tmp = _XkbAlloc(strlen(_XkbKnownLanguages) + 1);
	if (!tmp)
	    return NULL;
	strcpy(tmp, _XkbKnownLanguages);
    }
    start = tmp;
    do {
	if ( (set=strchr(tmp,'=')) == NULL )
	    break;
	*set++ = '\0';
	if ( (next=strchr(set,':')) != NULL )
	    *next++ = '\0';
	while ( tmp && *tmp ) {
	    if ( (end=strchr(tmp,',')) != NULL )
		*end++ = '\0';
	    if ( Strcmp( tmp, lang ) == 0 ) {
		strncpy(buf,set,100);
		buf[99] = '\0';
		Xfree(start);
		return buf;
	    }
	    tmp = end;
	}
	tmp = next;
    } while ( tmp && *tmp );
    Xfree(start);
    return NULL;
}