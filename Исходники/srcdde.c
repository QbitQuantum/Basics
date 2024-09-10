/*
 * RunDDECommand - try to run a Windows specific command
 */
bool RunDDECommand( int token, const char *str, char *tmp1, vi_rc *result, vlist *vl )
{
    vi_rc       rc;
    char        *tmp2;
    char        *tmp3;
    HSZ         hdl;
    HSZ         serverhdl, topichdl;
    DWORD       dword;
    HCONV       hconv;
    HDDEDATA    data;
    char        *ptr;
    int         len;
    jmp_buf     jmpaddr;
    int         jmprc;

    tmp2 = alloca( MAX_INPUT_LINE );
    if( tmp2 == NULL ) {
        return( false );
    }
    tmp3 = alloca( MAX_INPUT_LINE );
    if( tmp3 == NULL ) {
        return( false );
    }

    if( token == T_DDEINIT ) {
        if( !DDEInit() ) {
            *result = ERR_DDE_FAIL;
        } else {
            *result = ERR_NO_ERR;
        }
        return( true );
    }

    if( !UseDDE ) {
        *result = ERR_INVALID_DDE;
        return( true );
    }

    rc = ERR_NO_ERR;
    switch( token ) {
    case T_DDEQUERYSTRING:
        /*
         * syntax: ddequerystring <resvar> handle
         */
        if( !getVarName( &str, tmp1, vl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        str = Expand( tmp3, str, vl );
        if( !GetHSZ( &str, &hdl  ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        len = DdeQueryString( DDEInstId, hdl, NULL, 0, CP_WINANSI ) + 1;
        ptr = MemAlloc( len  );
        DdeQueryString( DDEInstId, hdl, ptr, len, CP_WINANSI );
        VarAddStr( tmp1, ptr, vl );
        MemFree( ptr );
        break;

    case T_DDERET:
        /*
         * syntax: dderet retval
         */
        str = Expand( tmp3, str, vl );
        jmprc = setjmp( jmpaddr );
        if( jmprc == 0 ) {
            StartExprParse( str, jmpaddr );
            DDERet = (HDDEDATA)GetConstExpr();
        } else {
            rc = ERR_INVALID_DDE;
        }
        break;

    case T_DDESERVER:
        /*
         * syntax: ddeserver <serverhandle>
         */
        str = Expand( tmp3, str, vl );
        if( !GetHSZ( &str, &hdl  ) ) {
            rc = ERR_INVALID_DDE;
        } else {
            if( !DdeNameService( DDEInstId, hdl, (HSZ)NULL, DNS_REGISTER ) ) {
                rc = ERR_DDE_FAIL;
            } else {
                ServerCount++;
            }
        }
        break;

    case T_CREATEDDESTRING:
        /*
         * syntax: createddestring <handlevar> "<string>"
         */
        if( !getVarName( &str, tmp1, vl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        if( GetStringWithPossibleQuote( &str, tmp2 ) != ERR_NO_ERR ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        str = Expand( tmp3, tmp2, vl );
        if( !CreateStringHandle( str, &hdl ) ) {
            rc = ERR_DDE_FAIL;
        } else {
            sprintf( tmp2, "%ld", (long)hdl );
            VarAddStr( tmp1, tmp2, vl );
        }
        break;

    case T_DELETEDDESTRING:
        /*
         * syntax: deleteddestring <handle>
         */
        str = Expand( tmp3, str, vl );
        if( !GetHSZ( &str, &hdl ) ) {
            rc = ERR_INVALID_DDE;
        } else {
            DeleteStringHandle( hdl );
        }
        break;

    case T_DDEGETDATA:
        /*
         * syntax: ddegetdata <strvar> <datahandle>
         */
        if( !getVarName( &str, tmp1, vl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        str = Expand( tmp3, str, vl );
        if( !GetHDDEDATA( &str, &data ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        len = DdeGetData( data, NULL, 0, 0 );
        ptr = MemAlloc( len );
        DdeGetData( data, (LPBYTE)ptr, len, 0 );
        VarAddStr( tmp1, ptr,  vl );
        MemFree( ptr );
//      DdeFreeDataHandle( data );
        break;


    case T_DDECREATEDATAHANDLE:
        /*
         * syntax: ddecreatedatahandle <handlevar> <itemhandle> "<string>"
         */
        if( !getVarName( &str, tmp1, vl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        str = Expand( tmp3, str, vl );
        if( !GetHSZ( &str, &hdl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        if( GetStringWithPossibleQuote( &str, tmp2 ) != ERR_NO_ERR ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        data = DdeCreateDataHandle( DDEInstId, (LPBYTE)tmp2, strlen( tmp2 ) + 1,
                                    0, hdl, ClipboardFormat, 0 );
        if( data == (HDDEDATA)NULL ) {
            rc = ERR_DDE_FAIL;
        } else {
            sprintf( tmp2, "%ld", (long)data );
            VarAddStr( tmp1, tmp2, vl );
        }
        break;

    case T_DDECONNECT:
        /*
         * syntax: ddeconnect <convvar> <serverhandle> <topichandle>
         */
        if( !getVarName( &str, tmp1, vl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        str = Expand( tmp3, str, vl );
        if( !GetHSZ( &str, &serverhdl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        if( !GetHSZ( &str, &topichdl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        hconv = DdeConnect( DDEInstId, serverhdl, topichdl, NULL );
        if( hconv == (HCONV)NULL ) {
            rc = ERR_DDE_FAIL;
        } else {
            sprintf( tmp2, "%ld", (long)hconv );
            VarAddStr( tmp1, tmp2, vl );
        }
        break;
    case T_DDEDISCONNECT:
        /*
         * syntax: ddedisconnect <hconv>
         */
        str = Expand( tmp3, str, vl );
        if( !GetHCONV( &str, &hconv ) ) {
            rc = ERR_INVALID_DDE;
        } else {
            DdeDisconnect( hconv );
        }
        break;

    case T_DDEREQUEST:
        /*
         * syntax: dderequest <datavar> <conv> <strhandle>
         */
        if( !getVarName( &str, tmp1, vl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        str = Expand( tmp3, str, vl );
        if( !GetHCONV( &str, &hconv ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        if( !GetHSZ( &str, &hdl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        data = DdeClientTransaction( NULL, 0, hconv, hdl, ClipboardFormat,
                                     XTYP_REQUEST, TIME_OUT, &dword );
        if( data == (HDDEDATA)NULL ) {
            rc = ERR_DDE_FAIL;
        } else {
            len = DdeGetData( data, NULL, 0, 0 ) + 1;
            ptr = MemAlloc( len );
            DdeGetData( data, (LPBYTE)ptr, len, 0 );
            VarAddStr( tmp1, ptr,  vl );
            MemFree( ptr );
            DdeFreeDataHandle( data );
        }
        break;

    case T_DDEPOKE:
        /*
         * syntax: ddepoke "<data>" <conv> <strhandle>
         */
        str = Expand( tmp3, str, vl );
        if( GetStringWithPossibleQuote( &str, tmp1 ) != ERR_NO_ERR ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        if( !GetHCONV( &str, &hconv ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        if( !GetHSZ( &str, &hdl ) ) {
            rc = ERR_INVALID_DDE;
            break;
        }
        data = DdeCreateDataHandle( DDEInstId, (LPBYTE)tmp1, strlen( tmp1 ) + 1,
                                    0L, hdl, ClipboardFormat, 0 );
        if( data == (HDDEDATA)NULL ) {
            rc = ERR_DDE_FAIL;
        } else {
            DdeClientTransaction( (LPBYTE)data, -1, hconv, hdl,
                                  ClipboardFormat, XTYP_POKE, TIME_OUT, NULL );
        }
        break;
    }

    *result = rc;
    return( true );

} /* RunDDECommand */