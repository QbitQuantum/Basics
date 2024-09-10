DOS_TIME
DateTimeFile2(
    LPSTR DirName,
    LPSTR FileName
    )
{
    char path[ DB_MAX_PATH_LENGTH ];
    WIN32_FILE_ATTRIBUTE_DATA FileData;
    DOS_TIME FileDateTime;
    BOOL rc;

    if (DirName == NULL || DirName[0] == '\0') {
        strcpy( path, FileName );
    } else {
        sprintf( path, "%s" PATH_SEPARATOR "%s", DirName, FileName );
    }

    rc = (*pGetFileAttributesExA) (path, GetFileExInfoStandard, (LPVOID)&FileData);

    if (!rc) {
        FileDateTime.value = 0;
    } else {
        FILETIME ftSystemTime;
        unsigned __int64 ui64Local, ui64File;
        GetSystemTimeAsFileTime(&ftSystemTime);

        ui64Local = (((unsigned __int64) ftSystemTime.dwHighDateTime) << 32) +
                      (unsigned __int64) ftSystemTime.dwLowDateTime;

        ui64File = (((unsigned __int64) FileData.ftLastWriteTime.dwHighDateTime) << 32) +
                     (unsigned __int64) FileData.ftLastWriteTime.dwLowDateTime;

        // Take into account that file times may have two second intervals (0x989680 = 1 second)
        // for FAT drives.
        if (ui64File > (ui64Local + (0x989680*2))) {
            BuildError("ERROR - \"%s\" file time is in the future.\n", path);
        }

        FileDateTime.value = 0L;
        FileTimeToDosDateTime( &FileData.ftLastWriteTime,
                               &FileDateTime.time.wDate,
                               &FileDateTime.time.wTime
                             );
    }
    return( FileDateTime );
}