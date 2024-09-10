POFFSET
ImlWriteFileContents(
    PINSTALLATION_MODIFICATION_LOGFILE pIml,
    PWSTR FileName
    )
{
    HANDLE hFindFirst, hFile, hMapping;
    WIN32_FIND_DATA FindFileData;
    PVOID p;
    IML_FILE_RECORD_CONTENTS ImlFileContentsRecord;

    hFindFirst = FindFirstFile( FileName, &FindFileData );
    if (hFindFirst == INVALID_HANDLE_VALUE) {
        return 0;
        }
    FindClose( hFindFirst );

    ImlFileContentsRecord.LastWriteTime = FindFileData.ftLastWriteTime;
    ImlFileContentsRecord.FileAttributes = FindFileData.dwFileAttributes;
    if (!(ImlFileContentsRecord.FileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        ImlFileContentsRecord.FileSize = FindFileData.nFileSizeLow;
        hFile = CreateFile( FileName,
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_EXISTING,
                            0,
                            NULL
                          );
        if (hFile == INVALID_HANDLE_VALUE) {
            printf( "*** CreateFile( '%ws' ) failed (%u)\n", FileName, GetLastError() );
            return 0;
            }

        if (ImlFileContentsRecord.FileSize != 0) {
            hMapping = CreateFileMapping( hFile,
                                         NULL,
                                         PAGE_READONLY,
                                         0,
                                         0,
                                         NULL
                                       );
            CloseHandle( hFile );
            hFile = NULL;
            if (hMapping == NULL) {
                printf( "*** CreateFileMapping( '%ws' ) failed (%u)\n", FileName, GetLastError() );
                return 0;
                }

            p = MapViewOfFile( hMapping,
                               FILE_MAP_READ,
                               0,
                               0,
                               0
                             );
            CloseHandle( hMapping );
            if (p == NULL) {
                printf( "*** MapViewOfFile( '%ws' ) failed (%u)\n", FileName, GetLastError() );
                return 0;
                }
            }
        else {
            CloseHandle( hFile );
            p = NULL;
            }
        }
    else {
        ImlFileContentsRecord.FileSize = 0;
        p = NULL;
        }

    ImlFileContentsRecord.Contents = ImlWrite( pIml, p, ImlFileContentsRecord.FileSize );
    if (p != NULL) {
        UnmapViewOfFile( p );
        }

    return ImlWrite( pIml,
                     &ImlFileContentsRecord,
                     sizeof( ImlFileContentsRecord )
                   );
}