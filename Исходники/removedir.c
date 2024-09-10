static int DeleteDirectory(wchar_t *refcstrRootDirectory)
{
    #define DEFAULT_PATTERN L"%s/*.*"
    BOOL bDeleteSubdirectories = TRUE;
    BOOL bSubdirectory = FALSE;
    HANDLE hFile;
    WIN32_FIND_DATAW FileInformation;
    DWORD dwError;
    wchar_t	*strPattern		= NULL;
    wchar_t	*strFilePath	= NULL;
    int len = 0;

    if (refcstrRootDirectory == NULL) return 1;

    len = (int)(wcslen(refcstrRootDirectory) + (int)wcslen(DEFAULT_PATTERN) + 1);

    strPattern = (wchar_t*)MALLOC(sizeof(wchar_t) * len);
    if (strPattern)
    {
        swprintf(strPattern, len, DEFAULT_PATTERN, refcstrRootDirectory);
    }
    else
    {
        return 1;
    }

    hFile = FindFirstFileW(strPattern, &FileInformation);
    if (strPattern) { FREE(strPattern);strPattern=NULL;}

    if(hFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ( (wcscmp(FileInformation.cFileName,L".") != 0) && (wcscmp(FileInformation.cFileName,L"..") != 0) )
            {
                #define FORMAT_PATH_TO_REMOVE L"%s\\%s"
                int len = (int) (wcslen(refcstrRootDirectory) + wcslen(FORMAT_PATH_TO_REMOVE) + wcslen((wchar_t*)(FileInformation.cFileName)) + 1);
                strFilePath = (wchar_t*) MALLOC(sizeof(wchar_t) * len);
                if (strFilePath)
                {
                    swprintf(strFilePath, len, FORMAT_PATH_TO_REMOVE, refcstrRootDirectory, FileInformation.cFileName);
                }

                if(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if(bDeleteSubdirectories)
                    {
                        int iRC = DeleteDirectory(strFilePath);
                        if (strFilePath) {FREE(strFilePath); strFilePath = NULL;}
                        if (strPattern) {FREE(strPattern); strPattern = NULL;}

                        if(iRC) 
                        {
                            return iRC;
                        }
                    }
                    else bSubdirectory = TRUE;
                }
                else
                {
                    if(SetFileAttributesW(strFilePath,FILE_ATTRIBUTE_NORMAL) == FALSE) 
                    {
                        if (strFilePath) {FREE(strFilePath); strFilePath = NULL;}
                        if (strPattern) {FREE(strPattern); strPattern = NULL;}
                        return GetLastError();
                    }

                    if(DeleteFileW(strFilePath) == FALSE) 
                    {
                        if (strFilePath) {FREE(strFilePath); strFilePath = NULL;}
                        if (strPattern) {FREE(strPattern); strPattern = NULL;}
                        return GetLastError();
                    }
                }
            }
        } while(FindNextFileW(hFile, &FileInformation) == TRUE);

        FindClose(hFile);
        if (strFilePath) {FREE(strFilePath); strFilePath = NULL;}
        if (strPattern) {FREE(strPattern); strPattern = NULL;}

        dwError = GetLastError();
        if(dwError != ERROR_NO_MORE_FILES) 
        {
            return dwError;
        }
        else
        {
            if(!bSubdirectory)
            {
                if(SetFileAttributesW(refcstrRootDirectory,FILE_ATTRIBUTE_NORMAL) == FALSE) 
                {
                    return GetLastError();
                }
                if(RemoveDirectoryW(refcstrRootDirectory) == FALSE)	
                {
                    return GetLastError();
                }
            }
        }
    }

    if (strFilePath) {FREE(strFilePath); strFilePath = NULL;}
    if (strPattern) {FREE(strPattern); strPattern = NULL;}
    return 0;
}