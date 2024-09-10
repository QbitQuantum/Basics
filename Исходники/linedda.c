void PASCAL _Cover_LineDDA( short x1, short y1, short x2, short y2, LINEDDAPROC p,
                        LPARAM data )
{
    LineDDA( x1, y1, x2, y2, SetProc( (FARPROC)p, GETPROC_LINEDDA ), (LPARAM) data );
}