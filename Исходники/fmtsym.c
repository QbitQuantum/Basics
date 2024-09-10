char *FormatName( NAME name, VBUF *pvbuf )
/****************************************/
{
    VBUF    prefix;
    bool    ctordtor;

    VbufInit( pvbuf );
    VbufInit( &prefix );
    ctordtor = fmtSymName( NULL, name, &prefix, pvbuf, FF_NULL );
    if( !ctordtor ) {
        VbufConcVbuf( pvbuf, &prefix );
    }
    VbufFree( &prefix );
    return( strrev( VbufString( pvbuf ) ) );
}