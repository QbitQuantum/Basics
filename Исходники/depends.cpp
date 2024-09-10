void DisplayFileInformation( PMODULE_FILE_INFO pModInfo, BOOL bQuiet )
{
    LPCTSTR base = getModuleBase(pModInfo,bQuiet);
    if ( !base ) return ;
    printf( "%-14s", base) ; // ->GetBaseName() );

    PSTR pszFullName = pModInfo->GetFullName();

    if ( g_fShowDateTime )
    {
        HFILE hFile = _lopen( pszFullName, OF_READ );
        if ( HFILE_ERROR != hFile )
        {
            FILETIME ft;

            if ( GetFileTime( (HANDLE)hFile, 0, 0, &ft ) )
            {
                char szFileDate[32] = { 0 };
                char szFileTime[32] = { 0 };

                GetFileDateAsString(&ft, szFileDate, sizeof(szFileDate) );
                GetFileTimeAsString(&ft, szFileTime, sizeof(szFileTime),
                                    TRUE);

                printf( "%s %s  ", szFileDate, szFileTime );
            }

            _lclose( hFile );
        }
    }

    if ( g_fShowLinkDateTime )
    {
        FILETIME ft;
        char szFileDate[32] = { 0 };
        char szFileTime[32] = { 0 };

        PE_EXE exe( pszFullName );

        TimeDateStampToFileTime( exe.GetTimeDateStamp(), &ft );

        GetFileDateAsString(&ft, szFileDate, sizeof(szFileDate) );
        GetFileTimeAsString(&ft, szFileTime, sizeof(szFileTime),
                            TRUE);

        printf( "%s %s  ", szFileDate, szFileTime );
    }

    if ( g_fShowFullPath )
        printf( "(%s)", pszFullName );

    printf( "\n" );

    if ( g_fShowVersion )
        ShowVersionInfo( pszFullName );
}