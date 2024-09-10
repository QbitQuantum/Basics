void WdeChangeDialogInfo( WdeInfoStruct *is )
{
    WdeInfoStruct       c_is;
    char                *str;
    char                *cp;
    bool                quoted_str;
    bool                str_is_ordinal;
    uint_16             ord;
    bool                found;
    WdeHashValue        value;

    c_is = *is;

    str = NULL;
    cp = WdeGetStrFromEdit( WdeInfoWindow, IDB_INFO_CAPTION, NULL );
    if( cp != NULL ) {
        str = WRConvertStringTo( cp, "\t\n", "tn" );
        WRMemFree( cp );
    }
    c_is.d.caption = str;

    str = WdeGetStrFromCombo( WdeInfoWindow, IDB_INFO_IDSTR );
    if( str == NULL ) {
        WRMemFree( c_is.d.caption );
        c_is.d.caption = NULL;
        return;
    }

    WRStripSymbol( str );

    quoted_str = FALSE;
    if( _mbclen( (unsigned char *)str ) == 1 && str[0] == '"' ) {
        unsigned char   *s;

        str[0] = ' ';
        cp = NULL;
        for( s = (unsigned char *)str; *s != '\0'; s = _mbsinc( s ) ) {
            if( _mbclen( s ) == 1 && *s == '"' ) {
                cp = (char *)s;
            }
        }
        if( cp != NULL ) {
            *cp = '\0';
        }
        WRStripSymbol( str );
        quoted_str = TRUE;
    }

    if( str[0] == '\0' ) {
        WRMemFree( str );
        WRMemFree( c_is.d.caption );
        c_is.d.caption = NULL;
        return;
    }

    ord = (uint_16)strtoul( str, &cp, 0 );
    str_is_ordinal = (*cp == '\0');

    c_is.symbol = NULL;

    if( quoted_str ) {
        c_is.d.name = WResIDFromStr( str );
        WRMemFree( str );
    } else if( str_is_ordinal ) {
        c_is.d.name = WResIDFromNum( ord );
        WRMemFree( str );
    } else {
        if( !WdeIsValidSymbol( str ) ) {
            WRMemFree( str );
            WRMemFree( c_is.d.caption );
            c_is.d.caption = NULL;
            return;
        }
        strupr( str );
        c_is.symbol = str;
        c_is.d.name = NULL;
    }

    Forward( is->obj, MODIFY_INFO, &c_is, NULL );

    if( c_is.symbol ) {
        WdeAddUniqueStringToCombo( WdeInfoWindow, IDB_INFO_IDSTR, c_is.symbol );
        value = WdeLookupName( c_is.res_info->hash_table, c_is.symbol, &found );
        if( found ) {
            WdeSetEditWithSINT32( (int_32)value, 10, WdeInfoWindow, IDB_INFO_IDNUM );
        }
    } else if( str_is_ordinal ) {
        WdeSetEditWithSINT32( (int_32)ord, 10, WdeInfoWindow, IDB_INFO_IDNUM );
    } else {
        WdeSetEditWithStr( "", WdeInfoWindow, IDB_INFO_IDNUM );
    }

    *is = c_is;
}