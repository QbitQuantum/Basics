apr_status_t filepath_root_test(char *path, apr_pool_t *p)
{
    apr_status_t rv;
#if APR_HAS_UNICODE_FS
    if (apr_os_level >= APR_WIN_NT)
    {
        apr_wchar_t wpath[APR_PATH_MAX];
        if (rv = utf8_to_unicode_path(wpath, sizeof(wpath) 
                                           / sizeof(apr_wchar_t), path))
            return rv;
        rv = GetDriveTypeW(wpath);
    }
    else
#endif
        rv = GetDriveType(path);

    if (rv == DRIVE_UNKNOWN || rv == DRIVE_NO_ROOT_DIR)
        return APR_EBADPATH;
    return APR_SUCCESS;
}