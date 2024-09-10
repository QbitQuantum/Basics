static void SplashLayout() {
    unichar_t *start, *pt, *lastspace;
    extern const char *source_modtime_str;
    extern const char *source_version_str;

    uc_strcpy(msg, "When my father finished his book on Renaissance printing (The Craft of Printing and the Publication of Shakespeare's Works) he told me that I would have to write the chapter on computer typography. This is my attempt to do so.");

    GDrawSetFont(splashw,splash_font);
    linecnt = 0;
    lines[linecnt++] = msg-1;
    for ( start = msg; *start!='\0'; start = pt ) {
	lastspace = NULL;
	for ( pt=start; ; ++pt ) {
	    if ( *pt==' ' || *pt=='\0' ) {
		if ( GDrawGetTextWidth(splashw,start,pt-start)<splashimage.u.image->width-10 )
		    lastspace = pt;
		else
	break;
		if ( *pt=='\0' )
	break;
	    }
	}
	if ( lastspace!=NULL )
	    pt = lastspace;
	lines[linecnt++] = pt;
	if ( *pt ) ++pt;
    }
    uc_strcpy(pt, " FontForge used to be named PfaEdit.");

    pt += u_strlen(pt);
    lines[linecnt++] = pt;
    uc_strcpy(pt,"  git hash: ");;
    pt += u_strlen(pt);
    lines[linecnt++] = pt;
    uc_strcat(pt, FONTFORGE_GIT_VERSION);

    pt += u_strlen(pt);
    lines[linecnt++] = pt;
    uc_strcpy(pt,"  Version: ");;
    uc_strcat(pt,FONTFORGE_MODTIME_STR);

    pt += u_strlen(pt);
    lines[linecnt++] = pt;
    uc_strcat(pt,"           (");
    uc_strcat(pt,FONTFORGE_MODTIME_STR);
    uc_strcat(pt,"-ML");
#ifdef FREETYPE_HAS_DEBUGGER
    uc_strcat(pt,"-TtfDb");
#endif
    uc_strcat(pt,")");
    pt += u_strlen(pt);
    lines[linecnt++] = pt;
    uc_strcpy(pt,"  Lib Version: ");
    uc_strcat(pt,FONTFORGE_MODTIME_STR);
    lines[linecnt++] = pt+u_strlen(pt);
    lines[linecnt] = NULL;
    is = u_strchr(msg,'(');
    ie = u_strchr(msg,')');
}