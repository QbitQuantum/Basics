int __cdecl main(int argc, char *argv[]) {

    WCHAR* lpPath        = NULL;
    WCHAR* lpFileName    = NULL;
    WCHAR* lpExtension   = NULL;
    DWORD  nBufferLength = 0;
    WCHAR  lpBuffer[_MAX_PATH];
    WCHAR** lpFilePart    = NULL;
    DWORD  error         = 0;
    DWORD  result        = 0;

    HANDLE hsearchfile;
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    char   fullPath[_MAX_DIR];
	char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];


    if(0 != (PAL_Initialize(argc, argv)))
    {
        return FAIL;
    }

   /* Initalize the buffer.
     */
    memset(fullPath, 0, _MAX_DIR);

    if (GetTempPathA(_MAX_DIR, fullPath) == 0)
    {
        Fail("ERROR: GetTempPathA failed to get a path\n");
    }

    memset(fileloc, 0, _MAX_PATH);
    sprintf_s(fileloc, _countof(fileloc), "%s%s", fullPath, szFileNameExistsWithExt);

    RemoveAll();

    hsearchfile = CreateFileA(fileloc, GENERIC_WRITE, 0, 0, CREATE_ALWAYS,                        
                            FILE_ATTRIBUTE_NORMAL, 0);

    if (hsearchfile == NULL)
    {
        Trace("ERROR[%ul]: couldn't create %s\n", GetLastError(), fileloc);
        return FAIL;    
    }

    CloseHandle(hsearchfile);

    //
    // find a file that doesn't exist
    //
    ZeroMemory( lpBuffer, sizeof(lpBuffer));
    lpPath        = convert((LPSTR)fullPath);
    lpFileName    = convert((LPSTR)szNoFileName);
    lpExtension   = NULL;

    if( SearchPathW( lpPath, lpFileName, lpExtension, nBufferLength, lpBuffer, lpFilePart) != 0 ){
        error = GetLastError();
        free(lpPath);
        free(lpFileName);
        Fail ("SearchPathW: ERROR1 -> Found invalid file[%s][%s][%s][%d]\n", lpPath, szNoFileName, szNoFileNameExt, error);
    }

    free(lpPath);
    free(lpFileName);

    //
    // find a file that exists, when path is mentioned explicitly
    //
    ZeroMemory( lpBuffer, sizeof(lpBuffer));
    lpPath        = convert((LPSTR)fullPath);
    lpFileName    = convert((LPSTR)szFileNameExistsWithExt);
    lpExtension   = NULL;

    result  = SearchPathW( lpPath, lpFileName, lpExtension, nBufferLength, lpBuffer, lpFilePart);

    if( result == 0 ){
        error = GetLastError();
        free(lpPath);
        free(lpFileName);
        Fail ("SearchPathA: ERROR2 -> Did not Find valid file[%s][%s][%d]\n", lpPath, szFileNameExistsWithExt, error);
    }

    free(lpPath);
    free(lpFileName);

    RemoveAll();

    PAL_Terminate();
    return PASS; 
}