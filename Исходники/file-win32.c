static bool create_dir(char const* path, int flags, int permissions, bool okay_if_exists, tr_error** error)
{
    TR_ASSERT(path != NULL);

    (void)permissions;

    bool ret;
    DWORD error_code = ERROR_SUCCESS;
    wchar_t* wide_path = path_to_native_path(path);

    if ((flags & TR_SYS_DIR_CREATE_PARENTS) != 0)
    {
        error_code = SHCreateDirectoryExW(NULL, wide_path, NULL);
        ret = error_code == ERROR_SUCCESS;
    }
    else
    {
        ret = CreateDirectoryW(wide_path, NULL);

        if (!ret)
        {
            error_code = GetLastError();
        }
    }

    if (!ret && error_code == ERROR_ALREADY_EXISTS && okay_if_exists)
    {
        DWORD const attributes = GetFileAttributesW(wide_path);

        if (attributes != INVALID_FILE_ATTRIBUTES &&
            (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
            ret = true;
        }
    }

    if (!ret)
    {
        set_system_error(error, error_code);
    }

    tr_free(wide_path);

    return ret;
}