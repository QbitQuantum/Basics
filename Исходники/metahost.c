static BOOL get_mono_path(LPWSTR path)
{
    static const WCHAR subdir_mono[] = {'\\','m','o','n','o','\\','m','o','n','o','-','2','.','0', 0};
    WCHAR base_path[MAX_PATH], mono_dll_path[MAX_PATH];

    /* c:\windows\mono\mono-2.0 */
    GetWindowsDirectoryW(base_path, MAX_PATH);
    strcatW(base_path, subdir_mono);

    if (find_mono_dll(base_path, mono_dll_path))
    {
        strcpyW(path, base_path);
        return TRUE;
    }

    return FALSE;
}