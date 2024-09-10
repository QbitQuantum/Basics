/**
 * Makes sure a library named "Subversion" exists and has our template
 * set to it.
 * If the library already exists, the template is set.
 * If the library doesn't exist, it is created.
 */
void EnsureSVNLibrary(bool bCreate /* = true*/)
{
    // when running the 32-bit version of TortoiseProc on x64 OS,
    // we must not create the library! This would break
    // the library in the x64 explorer.
    BOOL bIsWow64 = FALSE;
    IsWow64Process(GetCurrentProcess(), &bIsWow64);
    if (bIsWow64)
        return;

    CComPtr<IShellLibrary> pLibrary = NULL;
    if (FAILED(OpenShellLibrary(L"Subversion", &pLibrary)))
    {
        if (!bCreate)
            return;
        if (FAILED(SHCreateLibrary(IID_PPV_ARGS(&pLibrary))))
            return;

        // Save the new library under the user's Libraries folder.
        CComPtr<IShellItem> pSavedTo = NULL;
        if (FAILED(pLibrary->SaveInKnownFolder(FOLDERID_UsersLibraries, L"Subversion", LSF_OVERRIDEEXISTING, &pSavedTo)))
            return;
    }

    if (SUCCEEDED(pLibrary->SetFolderType(IsWindows8OrGreater() ? FOLDERTYPEID_Documents : FOLDERTYPEID_SVNWC)))
    {
        // create the path for the icon
        CString path;
        CString appDir = CPathUtils::GetAppDirectory();
        if (appDir.GetLength() < MAX_PATH)
        {
            TCHAR buf[MAX_PATH] = {0};
            PathCanonicalize(buf, (LPCTSTR)appDir);
            appDir = buf;
        }
        path.Format(L"%s%s,-%d", (LPCTSTR)appDir, L"TortoiseProc.exe", IsWin10OrLater() ? IDI_LIBRARY_WIN10 : IDI_LIBRARY);
        pLibrary->SetIcon((LPCTSTR)path);
        pLibrary->Commit();
    }
}