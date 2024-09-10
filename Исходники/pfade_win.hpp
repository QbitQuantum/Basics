        const std::string& getZusi3Datenpfad() {
            if (zusi3Datenpfad.empty()) {
                HKEY key;
                char buffer[MAX_PATH];
                DWORD len = MAX_PATH;
                if (SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Zusi3", 0, KEY_READ | KEY_WOW64_32KEY, &key)) &&
				        SUCCEEDED(RegGetValueA(key, nullptr, "DatenVerzeichnis", RRF_RT_REG_SZ, nullptr, (LPBYTE)buffer, &len))) {
                    zusi3Datenpfad = string(buffer, len - 1); // subtract terminating null character
                    RegCloseKey(key);
                }
            }
            return zusi3Datenpfad;
        }