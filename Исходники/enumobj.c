short PASCAL _Cover_EnumObjects( HDC dc, short obj, FARPROC p, LPSTR data )
{
    return( EnumObjects( dc, obj, SetProc( p, GETPROC_ENUMOBJECTS ),
                (LPARAM)data ) );
}