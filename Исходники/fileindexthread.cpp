static QString getWindowsSystemPath()
{
    WCHAR pSystemPath[MAX_PATH];
    UINT nCopied = GetSystemDirectoryW(pSystemPath, sizeof(pSystemPath) / sizeof(WCHAR));
    if (nCopied)
        return QString::fromWCharArray(pSystemPath, nCopied);
    else
        return "";
}