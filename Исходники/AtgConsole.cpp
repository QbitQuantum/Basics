VOID Console::FormatV( LPCWSTR wstrFormat, va_list pArgList )
{
    // Count the required length of the string
    DWORD dwStrLen = _vscwprintf( wstrFormat, pArgList ) + 1;    // +1 = null terminator
    WCHAR* strMessage = ( WCHAR* )_malloca( dwStrLen * sizeof( WCHAR ) );
    vswprintf_s( strMessage, dwStrLen, wstrFormat, pArgList );

    // Output the string to the console
    for( DWORD i = 0; i < wcslen( strMessage ); i++ )
    {
        Add( strMessage[i] );
    }

    // Output the string to the debug channel, if requested
    if( m_bOutputToDebugChannel )
    {
        OutputDebugStringW( strMessage );
    }

    // Render the new output
    Render();

    _freea( strMessage );

}