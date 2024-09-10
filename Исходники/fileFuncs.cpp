/**
 *  Wrapper um SHGetKnownFolderPath, unter Vista und Größer benutzt es das
 *  originale SHGetKnownFolderPath, ansonsten SHGetFolderPath.
 *
 *  @param[in] rfid
 *  @param[in] path
 *
 *  @return liefert den Status zurück (S_OK bei OK)
 *
 *  @author FloSoft
 */
static HRESULT mySHGetKnownFolderPath(REFKNOWNFOLDERID rfid, std::string& path)
{
    HRESULT retval = S_FALSE;
    LPWSTR ppszPath = NULL;

    if(!gShell32DLLInst)
        gShell32DLLInst = LoadLibraryW(L"Shell32.dll");

    if(gShell32DLLInst && !gSHGetKnownFolderPath)
        gSHGetKnownFolderPath = (LPSHGetKnownFolderPath)GetProcAddress(gShell32DLLInst, "SHGetKnownFolderPath");

    if(gSHGetKnownFolderPath)
        retval = gSHGetKnownFolderPath(rfid, KF_FLAG_CREATE, NULL, &ppszPath);
    else if(rfid == FOLDERID_Documents)
    {
        ppszPath = (LPWSTR)CoTaskMemAlloc(MAX_PATH * sizeof(WCHAR));
        if(SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, NULL, 0, ppszPath)))
            retval = S_OK;
    }

    if(ppszPath)
    {
        LPSTR ppszPathA = UnicodeToAnsi(ppszPath);
        path = ppszPathA;
        CoTaskMemFree(ppszPath);
        delete[] ppszPathA;
    }

    return retval;
}