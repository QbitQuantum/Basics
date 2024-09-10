/*-------------------------------------------------------------------------*/
VOID ViewHeader( CHAR *file )
{
    INT          i, m;
    CHAR         buf[64];
    static CHAR  str[140], tmp[140];

    _splitpath( file, NULL, NULL, fname, ext );

    if( pktcount )
        sprintf( str, "%u - %u  (%s%s)", pktNumber + 1, pktcount, fname, ext );
    else
        sprintf( str,  "1 - 1  (%s%s)", fname, ext );

    i = strlen( str );
    WSetCurColor( wmain, C_TEXT );
    WSetXY      ( wmain,  6, 0 );
    WPuts       ( wmain, str );
    memset      ( str, ' ', 30 - i ); str[ 30 - i ] = 0;
    WSetXY      ( wmain,  6 + i, 0 );
    WPuts       ( wmain, str );
    
    if(( m = maxXmain - 32 ) > 64 )
        m = 64;

    strncpy( tmp, Current -> from, m - 7 ); WSetXY( wmain, 6, 1 );
    sprintf( str,  "%-*.*s", m - 7, m - 7, tmp ); WPutstr( wmain, str );
    
    strncpy( tmp, Current -> to, m - 7 ); WSetXY( wmain, 6, 2 );
    sprintf( str,  "%-*.*s", m - 7, m - 7, tmp ); WPutstr( wmain, str );

    strncpy( tmp, Current -> subj, maxXsubj - 6 ); WSetXY( wmain, 6, 3 );
    sprintf( str,  "%-*.*s", maxXsubj - 6, maxXsubj - 6, tmp ); WPutstr( wmain, str );

    if( Current -> area )
    {
        strcpy ( str, " " );
        strncat( str, Current -> area, 60 );
        strcat ( str, " " );
    }
    else
        strcpy( str, " Netmail " );

    i = strlen( str );
    WPutbs ( wmain, 0,  6, WGetSchColor( wmain, C_MORE ), str );
    memset ( str, 'Ä', 60 - i ); str[ 60 - i ] = 0;
    WPutbs ( wmain, 0, 6 + i, WGetSchColor( wmain, C_BORDER ), str );

    if( BadPkt )
    {
        WPutbs( wmain, 0, 2, WGetSchColor( wmain, C_BORDER ), "´ Ã" );
        WPutbs( wmain, 0, 3, WGetSchColor( wmain, C_MORE   ),  "b"  );
    }
    else
        WPutbs( wmain, 0, 2, WGetSchColor( wmain, C_BORDER ), "ÄÄÄ" );
    
    if( ReadOnly )
    {
        WPutbs( wmain, 0, maxXmain - 4, WGetSchColor( wmain, C_BORDER ),  "´  Ã" );
        WPutbs( wmain, 0, maxXmain - 3, WGetSchColor( wmain, C_MORE   ),   "ro" );
    }
    else
        WPutbs( wmain, 0, maxXmain - 4, WGetSchColor( wmain, C_BORDER ), "ÄÄÄÄ" );

    WPrints ( wmain, m + 11, 0, Current -> date );

    strncpy( str, FidoAddr2Str( &Current -> AddrFrom, buf ), maxXmain - m );
    WSetXY ( wmain, m, 1 );
    WPrintf( wmain, "%-*.*s", maxXmain - m, maxXmain - m, str );

    if( Current -> area )
        WSetCurColor( wmain, C_HIDE );

    strncpy( str, FidoAddr2Str( &Current -> AddrTo, buf ), maxXmain - m );
    WSetXY( wmain, m, 2 );
    WPrintf( wmain, "%-*.*s", maxXmain - m, maxXmain - m, str );

#ifndef _LITE_
    ViewSelected();
#endif
    ViewSize();
    ViewAttr();
}