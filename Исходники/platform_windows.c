char *__PHYSFS_platformCalcPrefDir(const char *org, const char *app)
{
    /*
     * Vista and later has a new API for this, but SHGetFolderPath works there,
     *  and apparently just wraps the new API. This is the new way to do it:
     *
     *     SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE,
     *                          NULL, &wszPath);
     */

    WCHAR path[MAX_PATH];
    char *utf8 = NULL;
    size_t len = 0;
    char *retval = NULL;

    if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_APPDATA | CSIDL_FLAG_CREATE,
                                   NULL, 0, path)))
        BAIL_MACRO(PHYSFS_ERR_OS_ERROR, NULL);

    utf8 = unicodeToUtf8Heap(path);
    BAIL_IF_MACRO(!utf8, ERRPASS, NULL);
    len = strlen(utf8) + strlen(org) + strlen(app) + 4;
    retval = allocator.Malloc(len);
    if (!retval)
    {
        allocator.Free(utf8);
        BAIL_MACRO(PHYSFS_ERR_OUT_OF_MEMORY, NULL);
    } /* if */

    sprintf(retval, "%s\\%s\\%s\\", utf8, org, app);
    return retval;
} /* __PHYSFS_platformCalcPrefDir */