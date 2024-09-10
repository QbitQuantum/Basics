CKKPathHelper::CKKPathHelper(void)
{
    WCHAR szTempPathBuffer[MAX_PATH] = {0};
    GetTempPathW(MAX_PATH, szTempPathBuffer);
    m_strTempDir = szTempPathBuffer;

    WCHAR szAppDataPathBuffer[MAX_PATH] = {0};
    LPWSTR lpszAppDataPath = szTempPathBuffer;

    WCHAR szCommonAppDataPathBuffer[MAX_PATH] = {0};

    // AppDataDir
    SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_DEFAULT, szAppDataPathBuffer);
    m_strAppDataDir = szAppDataPathBuffer;
    // CommonAppDataDir
    SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_DEFAULT, szCommonAppDataPathBuffer);
    m_strCommonAppDataDir = szCommonAppDataPathBuffer;
    // LocalAppDataDir
    PFNSHGetKnownFolderPath SHGetKnownFolderPath = (PFNSHGetKnownFolderPath)GetProcAddress(GetModuleHandleW(L"shell32.dll"), "SHGetKnownFolderPath");
    if (SHGetKnownFolderPath == NULL) //SHGetKnownFolderPath is not supported
    {
        SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, szAppDataPathBuffer);
    }
    else
    {
        SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &lpszAppDataPath);
    }
    m_strExeDir = ultra::GetModuleFilePath();
    m_strAppDir = ultra::GetUpperPath(m_strExeDir);
    m_strXarDir = m_strAppDir + L"xar\\";
    //m_strCfgDir = m_strAppDir + L"Profiles\\";
    GetKKCfgPath(m_strCfgDir);
}