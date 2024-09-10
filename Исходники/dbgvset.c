static bool ScanRightBrace( void )
/********************************/
{
    if( CurrToken != T_RIGHT_BRACE ) return( FALSE );
    Scan();
    return( TRUE );
}