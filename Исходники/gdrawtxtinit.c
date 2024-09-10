enum charset _GDraw_ParseMapping(unichar_t *setname) {
    unichar_t *pt;
    int val;

    if ( uc_strstrmatch(setname,"iso")!=NULL && uc_strstrmatch(setname,"10646")!=NULL )
return( em_unicode );
    else if ( uc_strstrmatch(setname,"UnicodePlane")!=NULL ) {
	pt = u_strchr(setname,'-');
	if ( pt==NULL )
return( em_uplane0+1 );
return( em_uplane0+u_strtol(pt+1,NULL,10) );
    } else if ( uc_strstrmatch(setname,"unicode")!=NULL )
return( em_unicode );

#if 0
    if ( uc_strstrmatch(setname,"ascii")!=NULL ||
	    ( uc_strstrmatch(setname,"iso")!=NULL && uc_strstrmatch(setname,"646")!=NULL )) {
	char *lang = getenv( "LANG" );
	if ( lang==NULL || *lang=='\0' || (*lang=='e' && *lang=='n' ))
return( em_iso8859_1 );		/* ascii can masquarade as iso8859-1 for english speakers (no accents needed) */
    }
#endif

    if ( uc_strstrmatch(setname,"iso")!=NULL && uc_strstrmatch(setname,"8859")!=NULL ) {
	pt = uc_strstrmatch(setname,"8859");
	pt += 4;
	if ( *pt=='-' ) ++pt;
	if ( !isdigit(*pt) )
	    /* Bad */;
	else if ( !isdigit(pt[1]) )
return( em_iso8859_1+*pt-'1' );
	else {
	    val = (pt[0]-'0')*10 + pt[1]-'0';
	    switch ( val ) {
	      case 10: case 11:
return( em_iso8859_10+val-10 );
	      case 13: case 14: case 15:
return( em_iso8859_13+val-13 );
	    }
	}
    }

    if ( uc_strstrmatch(setname,"latin1")!=NULL )
return( em_iso8859_1 );
    else if ( uc_strstrmatch(setname,"latin2")!=NULL )
return( em_iso8859_2 );
    else if ( uc_strstrmatch(setname,"latin3")!=NULL )
return( em_iso8859_3 );
    else if ( uc_strstrmatch(setname,"latin4")!=NULL )
return( em_iso8859_4 );
    else if ( uc_strstrmatch(setname,"latin5")!=NULL )
return( em_iso8859_9 );
    else if ( uc_strstrmatch(setname,"latin6")!=NULL )
return( em_iso8859_10 );
    else if ( uc_strstrmatch(setname,"latin7")!=NULL )
return( em_iso8859_13 );
    else if ( uc_strstrmatch(setname,"latin8")!=NULL )
return( em_iso8859_14 );
    else if ( uc_strstrmatch(setname,"latin0")!=NULL || uc_strstrmatch(setname,"latin9")!=NULL )
return( em_iso8859_15 );

    if ( uc_strstrmatch(setname,"koi8")!=NULL )
return( em_koi8_r );

    if ( uc_strstrmatch(setname,"cyrillic")!=NULL )
return( em_iso8859_5 );		/* This is grasping at straws */
    else if ( uc_strstrmatch(setname,"greek")!=NULL )
return( em_iso8859_7 );		/* This is grasping at straws */
    else if ( uc_strstrmatch(setname,"arabic")!=NULL )
return( em_iso8859_6 );		/* This is grasping at straws */
    else if ( uc_strstrmatch(setname,"hebrew")!=NULL )
return( em_iso8859_8 );		/* This is grasping at straws */
    else if ( uc_strstrmatch(setname,"thai")!=NULL || uc_strstrmatch(setname,"tis")!=NULL )
return( em_iso8859_11 );

    if ( uc_strstrmatch(setname,"jis")!=NULL ) {
	if ( uc_strstrmatch(setname,"201")!=NULL )
return( em_jis201 );
	if ( uc_strstrmatch(setname,"208")!=NULL )
return( em_jis208 );
	if ( uc_strstrmatch(setname,"212")!=NULL )
return( em_jis212 );
	if ( uc_strstrmatch(setname,"213")!=NULL )	/* I don't support 213 */
return( em_none );

return( em_jis208 );
    }

    if ( uc_strstrmatch(setname,"ksc")!=NULL && uc_strstrmatch(setname,"5601")!=NULL )
return( em_ksc5601 );	/* Seem to be several versions of 5601, we want 94x94 */

    if ( uc_strstrmatch(setname,"gb")!=NULL && uc_strstrmatch(setname,"2312")!=NULL )
return( em_gb2312 );
    if ( uc_strstrmatch(setname,"big5")!=NULL )
return( em_big5 );

    if ( uc_strstrmatch(setname,"mac")!=NULL )
return( em_mac );
    if ( uc_strstrmatch(setname,"win")!=NULL )
return( em_win );

    if ( IsUserMap(setname))
return( em_user );

/* !!! Encodings used for postscript japanese fonts, which I don't understand */
#if 0
    if ( uc_strstrmatch(setname,"RJSJ")!=NULL )
return( em_sjis );
    if ( uc_strstrmatch(setname,"EUC")!=NULL )
return( em_euc );
#endif

return( em_none );
}