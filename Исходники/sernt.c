bool TestForBreak( void )
{
    DWORD       errors;
    COMSTAT     comStat;

    if( ClearCommError( hSerial, &errors, &comStat ) ) {
        if( errors & CE_BREAK ) {
            return TRUE;
        }
    }
    return( FALSE );
}