bool createDirPath(const std::string& path)
{
#ifdef WIN32
    //FIXME: Will work only on WinXP SP2 or newer.
    std::wstring wp = fromUTF8(directory(path).c_str());
    int result = SHCreateDirectoryExW(NULL, wp.c_str(), NULL);
    if ((result != ERROR_SUCCESS) && (result != ERROR_FILE_EXISTS) && (result != ERROR_ALREADY_EXISTS))
        return false;
#else
    int startPos = 0;
    int endPos = 0;
    while ((endPos = path.find(L'/', startPos)) != std::string::npos)
    {
        if (createDir(path.substr(0, endPos + 1).c_str(), 0777))
            return false;
        startPos = endPos + 1;
    }
    if (createDir(path.c_str(), 0777))
        return false;
#endif
    return true;
}