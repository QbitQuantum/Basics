    std::wstring PlatformWin::GetUserDocumentsDirectoryW()
    {
        LPITEMIDLIST pidl;

        if (SHGetFolderLocation(0, CSIDL_PERSONAL | CSIDL_FLAG_CREATE, NULL, 0, &pidl) == S_OK)
        {
            wchar_t cpath[MAX_PATH];
            SHGetPathFromIDListW( pidl, cpath );
            CoTaskMemFree(pidl);

            return std::wstring(cpath) + L"\\" + ToWString(std::string(APPLICATION_NAME));
        }
        throw Exception("Failed to access user documents directory.");
    }