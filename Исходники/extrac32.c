static void create_target_directory(LPWSTR Target)
{
    WCHAR dir[MAX_PATH];
    int res;

    strcpyW(dir, Target);
    *PathFindFileNameW(dir) = 0; /* Truncate file name */
    if(!PathIsDirectoryW(dir))
    {
        res = SHCreateDirectoryExW(NULL, dir, NULL);
        if(res != ERROR_SUCCESS && res != ERROR_ALREADY_EXISTS)
            WINE_ERR("Can't create directory: %s\n", wine_dbgstr_w(dir));
    }
}