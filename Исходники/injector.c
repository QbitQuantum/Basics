BOOL CheckIniFile(PCHAR OriginalExeName, PCHAR DllName)
{
    CHAR CurrentPath[MAX_PATH];
    CHAR FilePath[MAX_PATH];

    if (!GetCurrentDirectory(sizeof(CurrentPath) - 1, CurrentPath)) {
        printf("[-] CheckIniFile - GetCurrentDirectory failed : %lu\n", GetLastError());
        return FALSE;
    }
    sprintf_s(FilePath, sizeof (FilePath) - 1, "%s\\injector.ini", CurrentPath);
    if (GetPrivateProfileStringA("injector", "original_executable_name", NULL, OriginalExeName, MAX_PATH, FilePath) == 0) {
        printf("[-] CheckIniFile - GetPrivateProfileString failed : %lu\n", GetLastError());
        return FALSE;
    }
    if (GetPrivateProfileStringA("injector", "dll_name", NULL, DllName, MAX_PATH, FilePath) == 0) {
        printf("[-] CheckIniFile - GetPrivateProfileString failed : %lu\n", GetLastError());
        return FALSE;
    }
    return TRUE;
}