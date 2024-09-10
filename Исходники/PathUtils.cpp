std::wstring CPathUtils::GetAppDataPath(HMODULE hMod)
{
    PWSTR path = nullptr;
    if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, nullptr, &path) == S_OK)
    {
        std::wstring sPath = path;
        sPath += L"\\";
        sPath += CPathUtils::GetFileNameWithoutExtension(CPathUtils::GetModulePath(hMod));
        CreateDirectory(sPath.c_str(), nullptr);
        return sPath;
    }
    return CPathUtils::GetModuleDir(hMod);
}