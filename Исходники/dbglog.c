void ProcLog( void )
{
    if( ScanEOC() ) {
        LogEnd();
    } else if( CurrToken == T_GT ) {
        Scan();
        LogAppend();
    } else if( CurrToken == T_DIV ) {
        Scan();
        (*LogJmpTab[ ScanCmd( LogNameTab ) ])();
    } else {
        LogStart();
    }
}