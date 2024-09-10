//--------------------------------------------------------------------------------------
// Outputs to the debug stream a formatted Unicode string with a variable-argument list.
//--------------------------------------------------------------------------------------
VOID DebugSpewV( LPCWSTR strMsg, ... )
{
    WCHAR strBuffer[512];

    va_list args;
    va_start( args, strMsg );
    StringCchVPrintfW( strBuffer, 512, strMsg, args );
    strBuffer[511] = L'\0';
    va_end( args );

    OutputDebugString( strBuffer );
}