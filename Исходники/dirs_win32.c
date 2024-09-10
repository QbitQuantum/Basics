char *win32_get_font_dir(const char *font_file)
{
    wchar_t wdir[MAX_PATH];
    if (S_OK != SHGetFolderPathW(NULL, CSIDL_FONTS, NULL, SHGFP_TYPE_CURRENT, wdir)) {
        int lenght = GetWindowsDirectoryW(wdir, MAX_PATH);
        if (lenght == 0 || lenght > (MAX_PATH - 8)) {
            BD_DEBUG(DBG_FILE, "Font directory path too long!\n");
            return NULL;
        }
        if (!wcscat(wdir, L"\\fonts")) {
            BD_DEBUG(DBG_FILE, "Could not construct font directory path!\n");
            return NULL;
        }

    }

    int   len  = WideCharToMultiByte (CP_UTF8, 0, wdir, -1, NULL, 0, NULL, NULL);
    char *path = malloc(len + strlen(font_file) + 2);
    if (path) {
        WideCharToMultiByte(CP_UTF8, 0, wdir, -1, path, len, NULL, NULL);
        path[len - 1] = '\\';
        strcpy(path + len, font_file);
    }
    return path;
}