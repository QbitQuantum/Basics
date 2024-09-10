// Returns the size of filename (64bit)
u64 GetSize(const std::string &filename)
{
    if (!Exists(filename))
    {
        LOG_ERROR(Common_Filesystem, "failed %s: No such file", filename.c_str());
        return 0;
    }

    if (IsDirectory(filename))
    {
        LOG_ERROR(Common_Filesystem, "failed %s: is a directory", filename.c_str());
        return 0;
    }

    struct stat64 buf;
#ifdef _WIN32
    if (_wstat64(Common::UTF8ToUTF16W(filename).c_str(), &buf) == 0)
#else
    if (stat64(filename.c_str(), &buf) == 0)
#endif
    {
        LOG_TRACE(Common_Filesystem, "%s: %lld",
                filename.c_str(), (long long)buf.st_size);
        return buf.st_size;
    }

    LOG_ERROR(Common_Filesystem, "Stat failed %s: %s",
            filename.c_str(), GetLastErrorMsg());
    return 0;
}