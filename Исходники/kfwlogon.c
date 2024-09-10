static BOOL
GetSecurityLogonSessionData(HANDLE hToken, PSECURITY_LOGON_SESSION_DATA * ppSessionData)
{
    NTSTATUS Status = 0;
#if 0
    HANDLE  TokenHandle;
#endif
    TOKEN_STATISTICS Stats;
    DWORD   ReqLen;
    BOOL    Success;

    if (!ppSessionData)
        return FALSE;
    *ppSessionData = NULL;

#if 0
    Success = OpenProcessToken( HANDLE GetCurrentProcess(), TOKEN_QUERY, &TokenHandle );
    if ( !Success )
        return FALSE;
#endif

    Success = GetTokenInformation( hToken, TokenStatistics, &Stats, sizeof(TOKEN_STATISTICS), &ReqLen );
#if 0
    CloseHandle( TokenHandle );
#endif
    if ( !Success )
        return FALSE;

    Status = LsaGetLogonSessionData( &Stats.AuthenticationId, ppSessionData );
    if ( FAILED(Status) || !ppSessionData )
        return FALSE;

    return TRUE;
}