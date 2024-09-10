static BOOL is_local_machineA( const CHAR *server )
{
    static const CHAR dot[] = ".";
    CHAR buffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD len = sizeof(buffer) / sizeof(buffer[0]);

    if (!server || !strcmp( server, dot )) return TRUE;
    if (GetComputerNameA( buffer, &len ) && !lstrcmpiA( server, buffer )) return TRUE;
    return FALSE;
}