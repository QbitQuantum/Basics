static VOID
StartAutoApplications(
    IN INT clsid)
{
    WCHAR szPath[MAX_PATH] = {0};
    HRESULT hResult;
    HANDLE hFind;
    WIN32_FIND_DATAW findData;
    SHELLEXECUTEINFOW ExecInfo;
    size_t len;

    TRACE("(%d)\n", clsid);

    hResult = SHGetFolderPathW(NULL, clsid, NULL, SHGFP_TYPE_CURRENT, szPath);
    len = wcslen(szPath);
    if (!SUCCEEDED(hResult) || len == 0)
    {
        WARN("SHGetFolderPath() failed with error %lu\n", GetLastError());
        return;
    }

    wcscat(szPath, L"\\*");
    hFind = FindFirstFileW(szPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        WARN("FindFirstFile(%s) failed with error %lu\n", debugstr_w(szPath), GetLastError());
        return;
    }

    do
    {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (findData.nFileSizeHigh || findData.nFileSizeLow))
        {
            ZeroMemory(&ExecInfo, sizeof(SHELLEXECUTEINFOW));
            ExecInfo.cbSize = sizeof(ExecInfo);
            wcscpy(&szPath[len+1], findData.cFileName);
            ExecInfo.lpVerb = L"open";
            ExecInfo.lpFile = szPath;
            ExecInfo.lpDirectory = NULL;
            TRACE("Executing %s in directory %s\n",
                  debugstr_w(findData.cFileName), debugstr_w(szPath));
            ShellExecuteExW(&ExecInfo);
        }
    } while (FindNextFileW(hFind, &findData));
    FindClose(hFind);
}