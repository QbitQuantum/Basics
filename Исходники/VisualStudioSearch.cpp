bool VisualStudioExists(const wchar_t *key)
{
    HKEY hInst = nullptr;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, VSREG_KEY, 0, KEY_READ, &hInst) != ERROR_SUCCESS) {
        /// Not Found Key
        return false;
    }
    DWORD type = REG_SZ;
    WCHAR buffer[4096];
    DWORD dwSize = sizeof(buffer);
    if (RegGetValueW(hInst, nullptr, key, RRF_RT_REG_SZ, &type,
                     buffer, &dwSize) != ERROR_SUCCESS) {
        RegCloseKey(hInst);
        return false;
    }
    RegCloseKey(hInst);
    return true;
}