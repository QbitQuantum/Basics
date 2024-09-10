char *mp_get_win_config_path(const char *filename)
{
    wchar_t w_appdir[MAX_PATH + 1] = {0};
    wchar_t w_exedir[MAX_PATH + 1] = {0};
    char *res = NULL;
    void *tmp = talloc_new(NULL);

#ifndef __CYGWIN__
    if (SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, NULL,
        SHGFP_TYPE_CURRENT, w_appdir) != S_OK)
        w_appdir[0] = '\0';
#endif

    get_exe_dir(w_exedir);

    if (filename && filename[0] && w_exedir[0]) {
        char *dir = mp_to_utf8(tmp, w_exedir);
        char *temp = mp_path_join(tmp, bstr0(dir), bstr0("mpv"));
        res = mp_path_join(NULL, bstr0(temp), bstr0(filename));
        if (!mp_path_exists(res) || mp_path_isdir(res)) {
            talloc_free(res);
            res = NULL;
        }
    }

    if (!res && w_appdir[0]) {
        char *dir = mp_to_utf8(tmp, w_appdir);
        char *temp = mp_path_join(tmp, bstr0(dir), bstr0("mpv"));
        res = mp_path_join(NULL, bstr0(temp), bstr0(filename));
    }

    talloc_free(tmp);
    return res;
}