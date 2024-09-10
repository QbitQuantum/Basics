/**
 * Extracts the jar file from the MSI database binary field
 *
 * @param hModule Specify the handle for the MSI database
 */
void ExtractBinaryFile (MSIHANDLE hModule, const char* pFieldName, const char* pDstFileName) {
    char cSelectSql[MAX_PATH_SIZE] = {0};
    MSIHANDLE hRecord, hView, hDatabase;

    // get hView & hDatabase
    hDatabase = MsiGetActiveDatabase(hModule);
    sprintf(cSelectSql, "select * from Binary where `Name`='%s'", pFieldName);
    MsiDatabaseOpenView(hDatabase, cSelectSql, &hView);
    MsiViewExecute(hView, NULL);
    char szTemp[256] = {0};
    DWORD dwLength = 256;
    if (MsiViewFetch(hView, &hRecord) != ERROR_SUCCESS)
    {
        return;
    }
    MsiRecordGetString(hRecord, 1, szTemp, &dwLength);
    if (strncmp(szTemp, pFieldName, strlen(pFieldName)))
    {
        return;
    }
    // write into installer.jar
    #define BUFFERSIZE 1024
    char  szBuffer[BUFFERSIZE] = {0};
    DWORD cbBuf = BUFFERSIZE;
    DWORD countWrite = 0;

    FILE* fp = NULL;
    fp = fopen(pDstFileName, "wb+");
    if (NULL == fp) {
        return;
    }

    do {
        if (MsiRecordReadStream(hRecord, 2, szBuffer, &cbBuf) !=ERROR_SUCCESS)
            break; // error 
        countWrite = fwrite(szBuffer, 1, cbBuf, fp);
    } while (countWrite == BUFFERSIZE);

    fclose(fp);

    // close all handles
    MsiCloseHandle(hRecord);
    MsiViewClose(hView);
    MsiCloseHandle(hView);
    MsiCloseHandle(hDatabase);
}