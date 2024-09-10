DWORD Encryption::TraverseFile(TCHAR * pFolderPath)
{
    WIN32_FIND_DATA ffd;
    TCHAR szDir[MAX_PATH];
    size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError=0;
    // Check that the input path plus 2 is not longer than MAX_PATH.
    StringCchLength(pFolderPath, MAX_PATH, &length_of_arg);
    if (length_of_arg > (MAX_PATH - 2))
        return dwError;
    // Prepare string for use with FindFile functions.  First, copy the
    // string to a buffer, then append '\*' to the directory name.
    StringCchCopy(szDir, MAX_PATH, pFolderPath);
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
    // Find the first file in the directory.
    hFind = FindFirstFile(szDir, &ffd);
    if (INVALID_HANDLE_VALUE == hFind)
    {
        ErrorHandler(TEXT("FindFirstFile"));
        return dwError;
    }
    do
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if ( (strcmp(ffd.cFileName, TEXT(".")) != 0 ) && (strcmp(ffd.cFileName, TEXT("..")) != 0))
            {
                TCHAR newFolderPath[MAX_PATH];
                StringCchCopy(newFolderPath, MAX_PATH, pFolderPath);
                StringCchCat(newFolderPath, MAX_PATH, TEXT("\\"));
                StringCchCat(newFolderPath, MAX_PATH, ffd.cFileName);
                TraverseFile(newFolderPath);
            }
        }
        else
        {
            TCHAR filePath[MAX_PATH] ;
            StringCchCopy(filePath, MAX_PATH, pFolderPath);
            StringCchCat(filePath, MAX_PATH, TEXT("\\"));
            StringCchCat(filePath, MAX_PATH, ffd.cFileName);
            _tprintf(TEXT("  %s \n"), filePath);

            // ²»²Ù×÷±¾exeµµ
            if (strcmp(ffd.cFileName, TEXT("SecreteIt.exe")) != 0 )
            {
                // for debug:
                //StringCchCopy(filePath, MAX_PATH, TEXT("test.txt"));
                if (bEncrypt)
                    Encrypt(filePath);
                else if (bDecrypt)
                    Decrypt(filePath);
                else
                    dwError = -1;
            }
        }
    }
    while(FindNextFile(hFind, &ffd) != 0);

    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES)
    {
        ErrorHandler(TEXT("FindFirstFile"));
    }

    FindClose(hFind);
    return dwError;
}