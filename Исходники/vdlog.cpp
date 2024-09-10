VDLog* VDLog::get(TCHAR* path)
{
    if (_log || !path) {
        return _log;
    }
    DWORD size = 0;
    HANDLE file = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                             NULL);
    if (file != INVALID_HANDLE_VALUE) {
        size = GetFileSize(file, NULL);
        CloseHandle(file);
    }
    if (size != INVALID_FILE_SIZE && size > LOG_ROLL_SIZE) {
        TCHAR roll_path[MAX_PATH];
        _sntprintf(roll_path, MAX_PATH, TEXT("%s.1"), path);
        if (!MoveFileEx(path, roll_path, MOVEFILE_REPLACE_EXISTING)) {
            return NULL;
        }
    }
    FILE* handle = _wfsopen(path, L"a+", _SH_DENYNO);
    if (!handle) {
        return NULL;
    }
    _log = new VDLog(handle);
    return _log;
}