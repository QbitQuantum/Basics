bool ScanQuote( char **start, unsigned *len )
{
    int   cnt;

    if( CurrToken != T_LEFT_BRACE ) {
        *start = NULL;
        *len   = 0;
        return( FALSE );
    }
    *start = ScanPtr;
    cnt = 1;
    while( cnt > 0 ) {
        Scan();
        if( CurrToken == T_LEFT_BRACE ) {
            cnt += 1;
        } else if( CurrToken == T_RIGHT_BRACE ) {
            cnt -= 1;
        } else if( CurrToken == T_LINE_SEPARATOR ) {
            Recog( T_RIGHT_BRACE ); /* cause error */
        }
    }
    *len = TokenStart - *start;
    Scan();
    return( TRUE );
}