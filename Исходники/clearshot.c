static int ShowSaveDialog(wchar_t* name, size_t nameLength)
{
    wchar_t* defaultPath = xmalloc(MAX_PATH * sizeof(wchar_t));

    OPENFILENAMEW ofn = {
        .lStructSize  = sizeof(OPENFILENAMEW),
        .lpstrFilter  = L"PNG image\0*.png\0",
        .nFilterIndex = 1,
        .lpstrFile    = name,
        .nMaxFile     = nameLength,
        .Flags        = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
    };

    /* This may seem like an archaic way of getting the default pictures
       directory since it doesn't understand Windows 7 libraries, however
       GetSaveFileName will open the library anyway if given CSIDL_MYPICTURES
       and doing it this way is backwards compatible with Windows Vista */
    if (SHGetFolderPathW(NULL, CSIDL_MYPICTURES, NULL, SHGFP_TYPE_CURRENT, defaultPath) == S_OK)
        ofn.lpstrInitialDir = defaultPath;

    if (!GetSaveFileNameW(&ofn))
    {
        free(defaultPath);
        return 0;
    }

    free(defaultPath);
    return 1;
}

static FILE* OpenFileWrite(wchar_t* name)
{
    /* Every Windows program should have a variant of this function to replace
       fopen. That is, one that supports Unicode and FILE_SHARE_DELETE. */
    HANDLE winHandle = CreateFileW(
                           name,
                           GENERIC_READ | GENERIC_WRITE,
                           FILE_SHARE_READ | FILE_SHARE_DELETE,
                           NULL,
                           CREATE_ALWAYS,
                           0, NULL);
    if (!winHandle)
        return NULL;

    int crtHandle = _open_osfhandle((intptr_t)winHandle, 0);
    if (crtHandle == -1)
    {
        CloseHandle(winHandle);
        return NULL;
    }

    FILE* result = _fdopen(crtHandle, "wb");
    if (!result)
    {
        _close(crtHandle);
        return NULL;
    }

    return result;
}