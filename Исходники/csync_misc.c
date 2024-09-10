char *csync_get_user_home_dir(void) {
    char tmp[MAX_PATH] = {0};
    char *szPath = NULL;

    if (SHGetSpecialFolderPathA(NULL, tmp, CSIDL_PROFILE, TRUE)) {
        szPath = c_malloc(strlen(tmp) + 1);
        if (szPath == NULL) {
            return NULL;
        }

        strcpy(szPath, tmp);
        return szPath;
    }

    return NULL;
}