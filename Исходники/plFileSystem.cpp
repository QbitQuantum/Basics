/* plFileInfo */
plFileInfo::plFileInfo(const plFileName &filename)
    : fFileSize(-1), fCreateTime(), fModifyTime(), fFlags()
{
    if (!filename.IsValid())
        return;

#if HS_BUILD_FOR_WIN32
    struct __stat64 info;
    if (_wstat64(filename.AsString().ToWchar(), &info) != 0)
        return;
#else
    struct stat info;
    if (stat(filename.AsString().c_str(), &info) != 0)
        return;
#endif

    fFlags |= kEntryExists;
    fFileSize = info.st_size;
    fCreateTime = info.st_ctime;
    fModifyTime = info.st_mtime;
    if (info.st_mode & S_IFDIR)
        fFlags |= kIsDirectory;
    if (info.st_mode & S_IFREG)
        fFlags |= kIsNormalFile;
}