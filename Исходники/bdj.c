static void *_load_jvm_win32(const char **p_java_home)
{
    static char java_home[256] = "";

    wchar_t buf_loc[4096] = L"SOFTWARE\\JavaSoft\\Java Runtime Environment\\";
    wchar_t buf_vers[128];

    char strbuf[256];

    LONG r;
    DWORD lType;
    DWORD dSize = sizeof(buf_vers);
    HKEY hkey;

    r = RegOpenKeyExW(HKEY_LOCAL_MACHINE, buf_loc, 0, KEY_READ, &hkey);
    if (r != ERROR_SUCCESS) {
        BD_DEBUG(DBG_BDJ | DBG_CRIT, "Error opening registry key SOFTWARE\\JavaSoft\\Java Runtime Environment\\");
        return NULL;
    }

    r = RegQueryValueExW(hkey, L"CurrentVersion", NULL, &lType, (LPBYTE)buf_vers, &dSize);
    RegCloseKey(hkey);
    if (r != ERROR_SUCCESS) {
        BD_DEBUG(DBG_BDJ | DBG_CRIT, "CurrentVersion registry value not found");
        return NULL;
    }

    if (debug_mask & DBG_BDJ) {
        WideCharToMultiByte(CP_UTF8, 0, buf_vers, -1, strbuf, sizeof(strbuf), NULL, NULL);
        BD_DEBUG(DBG_BDJ, "JRE version: %s\n", strbuf);
    }
    wcscat(buf_loc, buf_vers);

    dSize = sizeof(buf_loc);
    r = RegOpenKeyExW(HKEY_LOCAL_MACHINE, buf_loc, 0, KEY_READ, &hkey);
    if (r != ERROR_SUCCESS) {
        BD_DEBUG(DBG_BDJ | DBG_CRIT, "Error opening JRE version-specific registry key");
        return NULL;
    }

    r = RegQueryValueExW(hkey, L"JavaHome", NULL, &lType, (LPBYTE)buf_loc, &dSize);

    if (r == ERROR_SUCCESS) {
        /* do not fail even if not found */
        WideCharToMultiByte(CP_UTF8, 0, buf_loc, -1, java_home, sizeof(java_home), NULL, NULL);
        *p_java_home = java_home;
        BD_DEBUG(DBG_BDJ, "JavaHome: %s\n", java_home);
    }

    dSize = sizeof(buf_loc);
    r = RegQueryValueExW(hkey, L"RuntimeLib", NULL, &lType, (LPBYTE)buf_loc, &dSize);
    RegCloseKey(hkey);

    if (r != ERROR_SUCCESS) {
        BD_DEBUG(DBG_BDJ | DBG_CRIT, "RuntimeLib registry value not found");
        return NULL;
    }

    void *result = LoadLibraryW(buf_loc);

    WideCharToMultiByte(CP_UTF8, 0, buf_loc, -1, strbuf, sizeof(strbuf), NULL, NULL);
    if (!result) {
        BD_DEBUG(DBG_BDJ | DBG_CRIT, "can't open library '%s'\n", strbuf);
    } else {
        BD_DEBUG(DBG_BDJ, "Using JRE library %s\n", strbuf);
    }

    return result;
}