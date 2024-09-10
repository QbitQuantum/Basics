/*
 * Check to see if we're on Win7 and up, and if so, returns the default
 * save-to location for the Windows Library passed in through aFolderId.
 * Otherwise falls back on pre-win7 GetWindowsFolder.
 */
static nsresult
GetLibrarySaveToPath(int aFallbackFolderId, REFKNOWNFOLDERID aFolderId,
                     nsIFile** aFile)
{
    // Skip off checking for library support if the os is Vista or lower.
    DWORD dwVersion = GetVersion();
    if ((DWORD)(LOBYTE(LOWORD(dwVersion))) < 6 ||
        ((DWORD)(LOBYTE(LOWORD(dwVersion))) == 6 &&
         (DWORD)(HIBYTE(LOWORD(dwVersion))) == 0))
      return GetWindowsFolder(aFallbackFolderId, aFile);

    nsRefPtr<IShellLibrary> shellLib;
    nsRefPtr<IShellItem> savePath;
    HRESULT hr =
        SHLoadLibraryFromKnownFolder(aFolderId, STGM_READ,
                                     IID_IShellLibrary, getter_AddRefs(shellLib));

    if (shellLib &&
        SUCCEEDED(shellLib->GetDefaultSaveFolder(DSFT_DETECT, IID_IShellItem,
                                                 getter_AddRefs(savePath)))) {
        PRUnichar* str = nullptr;
        if (SUCCEEDED(savePath->GetDisplayName(SIGDN_FILESYSPATH, &str))) {
            nsAutoString path;
            path.Assign(str);
            path.AppendLiteral("\\");
            nsresult rv =
                NS_NewLocalFile(path, false, aFile);
            CoTaskMemFree(str);
            return rv;
        }
    }

    return GetWindowsFolder(aFallbackFolderId, aFile);
}