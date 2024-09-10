bool read_key(HKEY srcBaseKey, std::string subKey, OUT BYTE *path_buffer, OUT DWORD &val_len, OUT DWORD &type)
{
    HKEY commandKey = NULL;
    if (RegOpenKeyExA(srcBaseKey, subKey.c_str(), 0, KEY_READ, &commandKey) != ERROR_SUCCESS) {
        return false;
    }

    RegGetValueA(commandKey, NULL, 0, RRF_RT_ANY, &type, path_buffer, &val_len);
    if (val_len == 0) {
        RegCloseKey(commandKey);
        return false;
    }
    RegCloseKey(commandKey);
    return true;
}