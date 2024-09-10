nsresult TestWinAttribs()
{
    if (!IsXPOrGreater())
      return NS_OK;
  
    printf("Is XP or greater, running tests...\n");

    nsresult rv;

    // File variables
    HANDLE hIndexed;
    nsCOMPtr<nsIFile> localFile;
    WCHAR filePath[MAX_PATH];

    // Create and open temporary file
    hIndexed = CreateFileW(L".\\indexbit.txt", 
                            GENERIC_READ | GENERIC_WRITE,
                            0, 
                            NULL,
                            CREATE_ALWAYS,        
                            FILE_ATTRIBUTE_NORMAL, //FILE_ATTRIBUTE_NOT_CONTENT_INDEXED, not supported by cf
                            NULL);  

    if(hIndexed == INVALID_HANDLE_VALUE)
    {
        fail("Test Win Attribs: Creating Test File");
        return NS_ERROR_FAILURE;
    }

    CloseHandle(hIndexed);

    GetFullPathNameW((LPCWSTR)L".\\indexbit.txt", 
                        MAX_PATH, filePath, NULL);

    //wprintf(filePath);
    //wprintf(L"\n");

    rv = NS_NewLocalFile(nsEmbedString(filePath), false,
                         getter_AddRefs(localFile));
    if (NS_FAILED(rv))
    {
        fail("Test Win Attribs: Opening Test File");
        DeleteFileW(filePath);
        return rv;
    }

    nsCOMPtr<nsILocalFileWin> localFileWin(do_QueryInterface(localFile));

    DWORD dwAttrs = GetFileAttributesW(filePath);
    if (dwAttrs == INVALID_FILE_ATTRIBUTES)
    {
        fail("Test Win Attribs: GetFileAttributesW - couldn't find our temp file.");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }

    dwAttrs |= FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
    SetFileAttributesW(filePath, dwAttrs);

    uint32_t attribs = 0;
    rv = localFileWin->GetFileAttributesWin(&attribs);
    
    if (NS_FAILED(rv))
    {
        fail("Test Win Attribs: GetFileAttributesWin failed to GET attributes. (1)");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }
    
    if (attribs & nsILocalFileWin::WFA_SEARCH_INDEXED)
    {
        fail("Test Win Attribs: GetFileAttributesWin attributed did not match. (2)");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }

    dwAttrs &= ~FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
    SetFileAttributesW(filePath, dwAttrs);

    rv = localFileWin->GetFileAttributesWin(&attribs);
    
    if (NS_FAILED(rv))
    {
        fail("Test Win Attribs: GetFileAttributesWin failed to GET attributes. (3)");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }

    if (!(attribs & nsILocalFileWin::WFA_SEARCH_INDEXED))
    {
        fail("Test Win Attribs: GetFileAttributesWin attributed did not match. (4)");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }

    dwAttrs &= ~FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
    SetFileAttributesW(filePath, dwAttrs);

    attribs = nsILocalFileWin::WFA_SEARCH_INDEXED;
    rv = localFileWin->SetFileAttributesWin(attribs);

    dwAttrs = GetFileAttributesW(filePath);

    if (NS_FAILED(rv))
    {
        fail("Test Win Attribs: GetFileAttributesWin failed to SET attributes. (5)");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }

    if (dwAttrs & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
    {
        fail("Test Win Attribs: SetFileAttributesWin attributed did not match. (6)");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }
    
    dwAttrs |= FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
    SetFileAttributesW(filePath, dwAttrs);

    attribs = 0;
    rv = localFileWin->SetFileAttributesWin(attribs);

    dwAttrs = GetFileAttributesW(filePath);

    if (NS_FAILED(rv))
    {
        fail("Test Win Attribs: GetFileAttributesWin failed to SET attributes. (7)");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }

    if (!(dwAttrs & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED))
    {
        fail("Test Win Attribs: SetFileAttributesWin attributed did not match. (8)");
        DeleteFileW(filePath);
        return NS_ERROR_FAILURE;
    }

    DeleteFileW(filePath);

    passed("Test Win Attribs: passed tests.");

    return NS_OK;
}