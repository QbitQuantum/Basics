static bool DetectDriver(const char *pszName) {
    char szDriverANSI[256];
    ICINFO info = { sizeof(ICINFO) };

    for(int i=0; ICInfo(ICTYPE_VIDEO, i, &info); ++i) {
        if (WideCharToMultiByte(CP_ACP, 0, info.szDriver, -1, szDriverANSI, sizeof szDriverANSI, NULL, NULL)
                && !_stricmp(szDriverANSI, pszName))

            return true;
    }

    return false;
}