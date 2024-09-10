std::string WindowsPlatformInterface::getExePath()
{
    char exeFullName[MAX_PATH + 1];
    char exeFullPath[MAX_PATH + 1];
    char * lpExeName;
    GetModuleFileNameA(NULL, exeFullName, MAX_PATH + 1);
    GetFullPathNameA(exeFullName, MAX_PATH + 1, exeFullPath, &lpExeName);
    *lpExeName = '\0';

    return exeFullPath;
}