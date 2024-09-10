int lstat(const char *path, struct stat *buffer)
{
    WIN32_FILE_ATTRIBUTE_DATA fdata;

    if (GetFileAttributesEx(path, GetFileExInfoStandard, &fdata))
    {
        int fMode = S_IREAD;
        if (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            fMode |= S_IFDIR;
        else
            fMode |= S_IFREG;
        if (!(fdata.dwFileAttributes & FILE_ATTRIBUTE_READONLY))
            fMode |= S_IWRITE;

        buffer->st_ino = 0;
        buffer->st_gid = 0;
        buffer->st_uid = 0;
        buffer->st_nlink = 1;
        buffer->st_mode = fMode;
        buffer->st_size = fdata.nFileSizeLow;
        buffer->st_dev = buffer->st_rdev = 0;
        buffer->st_atime = filetime_to_time_t(&fdata.ftLastAccessTime);
        buffer->st_mtime = filetime_to_time_t(&fdata.ftLastWriteTime);
        buffer->st_ctime = filetime_to_time_t(&fdata.ftCreationTime);

        if (fdata.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
        {
            WIN32_FIND_DATA find;
            HANDLE handle = FindFirstFile(path, &find);
            if (handle != INVALID_HANDLE_VALUE)
            {
                if ((find.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) &&
                        (find.dwReserved0 == IO_REPARSE_TAG_SYMLINK))
                {
                    buffer->st_mode = S_IFLNK;
                }
            }
        }
        _set_errno(0);
        return 0;
    }

    errno = winErrorToPosix(GetLastError());
    return -1;
}