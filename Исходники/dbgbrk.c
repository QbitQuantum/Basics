OVL_EXTERN brkp *ImageBreak( memory_expr def_seg )
{
    const char  *start;
    size_t      len;
    bool        clear = false;
    int         cmd;

    def_seg=def_seg;
    while( CurrToken == T_DIV ) {
        Scan();
        cmd = ScanCmd( PointNameTab );
        if( cmd < 0 )
            break;
        switch( cmd ) {
        case B_CLEAR:
            clear = true;
            break;
        default:
            Error( ERR_LOC, LIT_ENG( ERR_BAD_OPTION ), GetCmdName( CMD_BREAK ) );
            break;
        }
    }
    if( !ScanItem( true, &start, &len ) ) {
        BadPoint( def_seg );
    }
    BreakOnImageLoad( start, len, clear );
    Scan();
    ReqEOC();
    return( NULL );
}