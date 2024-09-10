BOOL InitBRegDll()
{
        LONG lResult;
        HKEY hKey;

        CHAR cPath[MAX_PATH + 32] = { 0 };
        DWORD dwPathLen = MAX_PATH;

        lResult = RegOpenKeyA(HKEY_LOCAL_MACHINE, AppPath, &hKey);
        if (FAILED(lResult))
                return FALSE;

        DWORD dwType = REG_SZ;
        lResult = RegQueryValueExA(hKey, "Path", NULL, &dwType, (LPBYTE)cPath, &dwPathLen);
        RegCloseKey(hKey);
        if (FAILED(lResult))
                return FALSE;

        strcat(cPath, "\\deepscan\\BREGDLL.dll");

        HMODULE modBReg = LoadLibraryA(cPath);
        if (!modBReg)
                return FALSE;

        INIT_REG_ENGINE InitRegEngine = (INIT_REG_ENGINE)GetProcAddress(modBReg, "InitRegEngine");
        BRegDeleteKey = (BREG_DELETE_KEY)GetProcAddress(modBReg, "BRegDeleteKey");
        BRegOpenKey = (BREG_OPEN_KEY)GetProcAddress(modBReg, "BRegOpenKey");
        BRegCloseKey = (BREG_CLOSE_KEY)GetProcAddress(modBReg, "BRegCloseKey");
        BRegSetValueEx = (REG_SET_VALUE_EX)GetProcAddress(modBReg, "BRegSetValueEx");

        if (!InitRegEngine || !BRegDeleteKey || !BRegOpenKey || !BRegCloseKey || !BRegSetValueEx) {
                FreeLibrary(modBReg);
                return FALSE;
        }

        if (!InitRegEngine()) {
                FreeLibrary(modBReg);
                return FALSE;
        }

        return TRUE;
}