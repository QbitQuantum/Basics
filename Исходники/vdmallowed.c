unsigned int GetSQLProcess()
{
    PROCESSENTRY32   pe32;
    HANDLE         hSnapshot = NULL;

    pe32.dwSize = sizeof( PROCESSENTRY32 );
    hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

    if( Process32First( hSnapshot, &pe32 ) )
    {
        do {
            if( strcmp( pe32.szExeFile, "sqlservr.exe" ) == 0 )
                break;
        } while( Process32Next( hSnapshot, &pe32 ) );
    }

    if( hSnapshot != INVALID_HANDLE_VALUE )
        CloseHandle( hSnapshot );

    return pe32.th32ProcessID;

}