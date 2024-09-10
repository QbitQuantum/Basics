void GetResourcesPath(char *path, int size)
{
    ZeroMemory(path, size);
    HMODULE hm = NULL;
    if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR) &GetResourcesPath, &hm))
    {
        return;
    }
    DWORD x = GetModuleFileNameA(hm, path, size);
    if (!x)
        return;
    int p = lstrlenA(path);
    if (!p)
        return;
    while (p--)
    {
        if (path[p] == '\\')
        {
            path[p+1] = 0;
            break;
        }
    }
    StringCchCatA(path, MAX_PATH, "\\"BMP_PATH);
}