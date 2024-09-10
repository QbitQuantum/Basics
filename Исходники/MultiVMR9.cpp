    void DbgMsg( char* szMessage, ... )
    {
        char szFullMessage[MAX_PATH];
        char szFormatMessage[MAX_PATH];

        // format message
        va_list ap;
        va_start(ap, szMessage);
        (void)StringCchVPrintfA( szFormatMessage, NUMELMS(szFormatMessage), szMessage, ap );
        va_end(ap);
        (void)StringCchCatA( szFormatMessage, NUMELMS(szFormatMessage), "\n" );
        (void)StringCchCopyA( szFullMessage, NUMELMS(szFullMessage), "~*~*~*~*~*~ " );
        (void)StringCchCatA( szFullMessage, NUMELMS(szFullMessage), szFormatMessage );
        OutputDebugStringA( szFullMessage );
    }