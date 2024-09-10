//----------------------------------------------------------------------------------------
static void GetWindowsFolder(int folder, nsFileSpec& outDirectory)
//----------------------------------------------------------------------------------------
{

    if (gGetSpecialPathProc) {
        TCHAR path[MAX_PATH];
        HRESULT result = gGetSpecialPathProc(NULL, path, folder, true);
        
        if (!SUCCEEDED(result)) 
            return;

        // Append the trailing slash
        int len = PL_strlen(path);
        if (len>1 && path[len-1] != '\\') 
        {
            path[len]   = '\\';
            path[len + 1] = '\0';
        }
        outDirectory = path;
        return;
    }

    LPMALLOC pMalloc = NULL;
    LPSTR pBuffer = NULL;
    LPITEMIDLIST pItemIDList = NULL;
    int len;
 
    // Get the shell's allocator. 
    if (!SUCCEEDED(SHGetMalloc(&pMalloc))) 
        return;

    // Allocate a buffer
    if ((pBuffer = (LPSTR) pMalloc->Alloc(MAX_PATH + 2)) == NULL) 
        return; 
 
    // Get the PIDL for the folder. 
    if (!SUCCEEDED(SHGetSpecialFolderLocation( 
            NULL, folder, &pItemIDList)))
        goto Clean;
 
    if (!SUCCEEDED(SHGetPathFromIDList(pItemIDList, pBuffer)))
        goto Clean;

    // Append the trailing slash
    len = PL_strlen(pBuffer);
    pBuffer[len]   = '\\';
    pBuffer[len + 1] = '\0';

    // Assign the directory
    outDirectory = pBuffer;

Clean:
    // Clean up. 
    if (pItemIDList)
        pMalloc->Free(pItemIDList); 
    if (pBuffer)
        pMalloc->Free(pBuffer); 

	pMalloc->Release();
} // GetWindowsFolder