BOOL
EnumAvailableApplications(INT EnumType, AVAILENUMPROC lpEnumProc)
{
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAW FindFileData;
    WCHAR szPath[MAX_PATH];
    WCHAR szAppsPath[MAX_PATH];
    WCHAR szSectionLocale[MAX_PATH] = L"Section.";
    WCHAR szCabPath[MAX_PATH];
    WCHAR szLocale[4 + 1];
    APPLICATION_INFO Info;

    if (!GetCurrentDirectoryW(MAX_PATH, szPath))
    {
        return FALSE;
    }

    swprintf(szCabPath, L"%s\\rappmgr.cab", szPath);

    wcscat(szPath, L"\\rapps\\");
    wcscpy(szAppsPath, szPath);

    if (!CreateDirectory(szPath, NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS)
    {
        return FALSE;
    }

    GetLocaleInfoW(GetUserDefaultLCID(), LOCALE_ILANGUAGE, szLocale, sizeof(szLocale) / sizeof(WCHAR));
    wcscat(szSectionLocale, szLocale);

    wcscat(szPath, L"*.txt");

    hFind = FindFirstFileW(szPath, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        if (GetFileAttributesW(szCabPath) == INVALID_FILE_ATTRIBUTES)
            DownloadApplicationsDB(APPLICATION_DATEBASE_URL);

        ExtractFilesFromCab(szCabPath, szAppsPath);
        hFind = FindFirstFileW(szPath, &FindFileData);
        if (hFind == INVALID_HANDLE_VALUE)
            return FALSE;
    }

#define GET_STRING1(a, b)  \
    if (!ParserGetString(szSectionLocale, a, b, MAX_PATH, FindFileData.cFileName)) \
        if (!ParserGetString(L"Section", a, b, MAX_PATH, FindFileData.cFileName)) \
            continue;

#define GET_STRING2(a, b)  \
    if (!ParserGetString(szSectionLocale, a, b, MAX_PATH, FindFileData.cFileName)) \
        if (!ParserGetString(L"Section", a, b, MAX_PATH, FindFileData.cFileName)) \
            b[0] = '\0';

    do
    {
        Info.Category = ParserGetInt(szSectionLocale, L"Category", FindFileData.cFileName);
        if (Info.Category == -1)
        {
            Info.Category = ParserGetInt(L"Section", L"Category", FindFileData.cFileName);
            if (Info.Category == -1)
                continue;
        }

        if (EnumType != Info.Category && EnumType != ENUM_ALL_AVAILABLE) continue;

        GET_STRING1(L"Name", Info.szName);
        GET_STRING1(L"URLDownload", Info.szUrlDownload);

        GET_STRING2(L"RegName", Info.szRegName);
        GET_STRING2(L"Version", Info.szVersion);
        GET_STRING2(L"Licence", Info.szLicence);
        GET_STRING2(L"Description", Info.szDesc);
        GET_STRING2(L"Size", Info.szSize);
        GET_STRING2(L"URLSite", Info.szUrlSite);
        GET_STRING2(L"CDPath", Info.szCDPath);

        if (!lpEnumProc(Info)) break;
    }
    while (FindNextFileW(hFind, &FindFileData) != 0);

    FindClose(hFind);

    return TRUE;
}