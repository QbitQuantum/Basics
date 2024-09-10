void showItem( Item* pItem )
{
    FILETIME lastWriteFTIME;
    SYSTEMTIME lastWriteSYSTIME;
    LARGE_INTEGER entrySize;
    TCHAR dirsCtStr[ 32 ] = { 0 };
    TCHAR filesCtStr[ 32 ] = { 0 };
    TCHAR sizeStr[ 32 ] = { 0 };

    // Fetch and prepare entry last modification date & time

    // UTC time (FILETIME) to local time (FILETIME)
    FileTimeToLocalFileTime( &pItem->findInfo.ftLastWriteTime,
        &lastWriteFTIME );

    // local time (FILETIME) to local time (SYSTIME)
    FileTimeToSystemTime( &lastWriteFTIME, &lastWriteSYSTIME );

    // Disp entry last modification date & time
    wprintf_s( TEXT( "    %04d-%02d-%02d %02d:%02d:%02d" ),
        lastWriteSYSTIME.wYear,
        lastWriteSYSTIME.wMonth,
        lastWriteSYSTIME.wDay,
        lastWriteSYSTIME.wHour,
        lastWriteSYSTIME.wMinute,
        lastWriteSYSTIME.wSecond );

    // Disp entry type (dir/file)
    if ( pItem->findInfo.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT )
        wprintf_s( TEXT( " %5s" ), TEXT( "<LIN>" ) );
    else if ( pItem->findInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        wprintf_s( TEXT( " %5s" ), TEXT( "<DIR>" ) );
    else
        wprintf_s( TEXT( " %5s" ), TEXT( "     " ) );

    // Fetch entry size
    entrySize.LowPart = pItem->findInfo.nFileSizeLow;
    entrySize.HighPart = pItem->findInfo.nFileSizeHigh;

    // Convert nums to strings (thousands separated)
    sepThousands( &pItem->dirsCount.QuadPart, dirsCtStr,
        _countof( dirsCtStr ) );
    sepThousands( &pItem->filesCount.QuadPart, filesCtStr,
        _countof( filesCtStr ) );
    sepThousands( &entrySize.QuadPart, sizeStr,
        _countof( sizeStr ) );

    // Disp entry details
    wprintf_s( TEXT( " %10s %10s %18s %s\n" ),
        dirsCtStr,
        filesCtStr,
        sizeStr,
        pItem->findInfo.cFileName );
}