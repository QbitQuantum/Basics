/*
 * Code to figure out the user's home directory using shell32.dll
 */
WCHAR*
getHomeFromShell32()
{
    HRESULT rc;
    LPITEMIDLIST item_list = 0;
    WCHAR *p;
    WCHAR path[MAX_PATH+1];
    int size = MAX_PATH+1;

    rc = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOPDIRECTORY, &item_list);
    if (!SUCCEEDED(rc)) {
        // we can't find the shell folder.
        return NULL;
    }

    path[0] = 0;
    SHGetPathFromIDListW(item_list, (LPWSTR)path);

    /* Get the parent of Desktop directory */
    p = wcsrchr(path, L'\\');
    if (p) {
        *p = 0;
    }

    /*
     * We've been successful.  Note that we don't free the memory allocated
     * by ShGetSpecialFolderLocation.  We only ever come through here once,
     * and only if the registry lookup failed, so it's just not worth it.
     *
     * We also don't unload the SHELL32 DLL.  We've paid the hit for loading
     * it and we may need it again later.
     */
    return _wcsdup(path);
}