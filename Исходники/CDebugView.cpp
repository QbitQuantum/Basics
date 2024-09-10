void CDebugView::Outputf ( bool bColorCoded, char* szText, ... )
{
    char szBuffer [ 1024 ];
    va_list ap;
    va_start ( ap, szText );
    _VSNPRINTF ( szBuffer, 1024, szText, ap );
    va_end ( ap );

    CChat * pChat = g_pChat;
    g_pChat = this;
    CChat::Output ( szBuffer, bColorCoded );
    g_pChat = pChat;
}