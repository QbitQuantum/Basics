PRInt32
_PR_MD_GETFILEINFO64(const char *fn, PRFileInfo64 *info)
{
    HANDLE hFindFile;
    WIN32_FIND_DATA findFileData;
    char pathbuf[MAX_PATH + 1];
    
    if (NULL == fn || '\0' == *fn) {
        PR_SetError(PR_INVALID_ARGUMENT_ERROR, 0);
        return -1;
    }

    /*
     * FindFirstFile() expands wildcard characters.  So
     * we make sure the pathname contains no wildcard.
     */
    if (NULL != _mbspbrk(fn, "?*")) {
        PR_SetError(PR_FILE_NOT_FOUND_ERROR, 0);
        return -1;
    }

    hFindFile = FindFirstFile(fn, &findFileData);
    if (INVALID_HANDLE_VALUE == hFindFile) {
        DWORD len;
        char *filePart;

        /*
         * FindFirstFile() does not work correctly on root directories.
         * It also doesn't work correctly on a pathname that ends in a
         * slash.  So we first check to see if the pathname specifies a
         * root directory.  If not, and if the pathname ends in a slash,
         * we remove the final slash and try again.
         */

        /*
         * If the pathname does not contain ., \, and /, it cannot be
         * a root directory or a pathname that ends in a slash.
         */
        if (NULL == _mbspbrk(fn, ".\\/")) {
            _PR_MD_MAP_OPENDIR_ERROR(GetLastError());
            return -1;
        } 
        len = GetFullPathName(fn, sizeof(pathbuf), pathbuf,
                &filePart);
        if (0 == len) {
            _PR_MD_MAP_OPENDIR_ERROR(GetLastError());
            return -1;
        }
        if (len > sizeof(pathbuf)) {
            PR_SetError(PR_NAME_TOO_LONG_ERROR, 0);
            return -1;
        }
        if (IsRootDirectory(pathbuf, sizeof(pathbuf))) {
            info->type = PR_FILE_DIRECTORY;
            info->size = 0;
            /*
             * These timestamps don't make sense for root directories.
             */
            info->modifyTime = 0;
            info->creationTime = 0;
            return 0;
        }
        if (!_PR_IS_SLASH(pathbuf[len - 1])) {
            _PR_MD_MAP_OPENDIR_ERROR(GetLastError());
            return -1;
        } else {
            pathbuf[len - 1] = '\0';
            hFindFile = FindFirstFile(pathbuf, &findFileData);
            if (INVALID_HANDLE_VALUE == hFindFile) {
                _PR_MD_MAP_OPENDIR_ERROR(GetLastError());
                return -1;
            }
        }
    }

    FindClose(hFindFile);

    if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        info->type = PR_FILE_DIRECTORY;
    } else {
        info->type = PR_FILE_FILE;
    }

    info->size = findFileData.nFileSizeHigh;
    info->size = (info->size << 32) + findFileData.nFileSizeLow;

    _PR_FileTimeToPRTime(&findFileData.ftLastWriteTime, &info->modifyTime);

    if (0 == findFileData.ftCreationTime.dwLowDateTime &&
            0 == findFileData.ftCreationTime.dwHighDateTime) {
        info->creationTime = info->modifyTime;
    } else {
        _PR_FileTimeToPRTime(&findFileData.ftCreationTime,
                &info->creationTime);
    }

    return 0;
}