ULONG _cdecl NFS41DbgPrint( __in LPTSTR Format, ... )
{
    ULONG rc = 0;
    TCHAR szbuffer[256];

    va_list marker;
    va_start( marker, Format );
    {

        //StringCchVPrintfW( szbuffer, 127, Format, marker );
        StringCchVPrintfW( szbuffer, 256, Format, marker );
        szbuffer[255] = (TCHAR)0;
        OutputDebugString( TRACE_TAG );
        OutputDebugString( szbuffer );
    }

    return rc;
}