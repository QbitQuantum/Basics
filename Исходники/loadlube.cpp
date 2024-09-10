int LoadLubeFromDll(const char *pszName, PLUBEHEADER *ppLube)
{
    int nSize;
    HRSRC hResInfo;
    HGLOBAL hRes;
    LPVOID lpLockRes;
    HMODULE handle;

    if (pszName) {
        handle = LoadLibraryExA(pszName, NULL, LOAD_LIBRARY_AS_DATAFILE);
        if (!handle) goto ErrorExit;
    }
    else {
        handle = NULL;
    }

    hResInfo = FindResourceA(handle, "#1", "Lube");
    if (!hResInfo) goto ErrorExit;

    nSize = SizeofResource(handle, hResInfo);
    if (0 == nSize) goto ErrorExit;

    hRes = LoadResource(handle, hResInfo);
    if (!hRes) goto ErrorExit;

    lpLockRes = LockResource(hRes);
    if (!lpLockRes) goto ErrorExit;

    return RelocFlattedLube((PLUBEHEADER)lpLockRes, nSize, ppLube);

ErrorExit:
    fprintf(stderr, "[ERROR] lube (0x0303 : Can't load lube resource from file.\n");
    return LUBE_FAIL;
}