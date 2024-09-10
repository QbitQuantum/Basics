void hsWFolderIterator::SetWinSystemDir(const wchar_t subdir[])
{
    int ret = GetWindowsDirectoryW(fPath, _MAX_PATH);
    hsAssert(ret != 0, "Error getting windows directory in UseWindowsFontsPath");

    if (subdir)
    {
        wcscat(fPath, L"\\");
        wcscat(fPath, subdir);
        wcscat(fPath, L"\\");
    }
    Reset();
}