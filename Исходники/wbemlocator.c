static BOOL is_local_machine( const WCHAR *server )
{
    static const WCHAR dotW[] = {'.',0};
    WCHAR buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD len = sizeof(buffer) / sizeof(buffer[0]);

    if (!server || !strcmpW( server, dotW )) return TRUE;
    if (GetComputerNameW( buffer, &len ) && !strcmpiW( server, buffer )) return TRUE;
    return FALSE;
}