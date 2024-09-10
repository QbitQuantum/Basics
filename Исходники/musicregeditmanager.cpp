int MusicRegeditManager::getLocalIEVersion() const
{
#ifdef Q_OS_WIN
    DWORD versionInfoSize = GetFileVersionInfoSizeW(L"mshtml.dll", nullptr);
    if(versionInfoSize == 0)
    {
        return -1;
    }

    BYTE *pData = new BYTE[versionInfoSize];
    if(!GetFileVersionInfoW(L"mshtml.dll", 0, versionInfoSize, pData))
    {
        delete[] pData;
        return -1;
    }

    VS_FIXEDFILEINFO *fixedFileInfo = nullptr;
    UINT fixedFileInfoSize = 0;
    if(!VerQueryValueW(pData, L"\\", (LPVOID*)&fixedFileInfo, &fixedFileInfoSize))
    {
        delete[] pData;
        return -1;
    }

    delete[] pData;
    return HIWORD(fixedFileInfo->dwProductVersionMS);
#endif
    return -1;
}