static BOOL msidbExportStorage(LPCWSTR dbfile, LPCWSTR wdir, LPWSTR storageName)
{
    UINT r, len;
    MSIHANDLE dbhandle, view, rec;
    char queryBuffer[100];
    char *storageNameA = strdupWtoA(CP_ACP, storageName);
    char *wdirA = strdupWtoA(CP_ACP, wdir);
    char *storagePath = NULL;
    char *dataBuffer;
    DWORD dataLen = 0;
    FILE *fp = NULL;
    sprintf(queryBuffer, "SELECT * FROM _Storages WHERE Name = '%s'", storageNameA);

    r = MsiOpenDatabaseW(dbfile, (LPWSTR) MSIDBOPEN_READONLY, &dbhandle);
    if (r != ERROR_SUCCESS) return FALSE;

    MsiDatabaseOpenView(dbhandle, queryBuffer, &view);
    MsiViewExecute(view, 0);
    r = MsiViewFetch(view, &rec);
    if (r != ERROR_SUCCESS) return FALSE;

    if ((r = MsiRecordReadStream(rec, 2, 0, &dataLen)) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    if ((dataBuffer = malloc(dataLen)) == NULL) return FALSE;
    if (MsiRecordReadStream(rec, 2, dataBuffer, &dataLen) != ERROR_SUCCESS) return FALSE;

    len = strlen(wdirA) + strlen(storageNameA) + 2;
    storagePath = malloc(len * sizeof(WCHAR));
    if (storagePath == NULL) return FALSE;

    strcpy(storagePath, wdirA);
    strcat(storagePath, "/");
    strcat(storagePath, storageNameA);

    fp = fopen(storagePath , "wb");
    if (fp != NULL)
    {
        fwrite(dataBuffer, 1, dataLen, fp);
        fclose(fp);
    }

    free(storagePath);
    MsiCloseHandle(rec);

    MsiViewClose(view);
    MsiCloseHandle(view);
    MsiCloseHandle(dbhandle);
    free(storageNameA);
    free(wdirA);
    return TRUE;
}