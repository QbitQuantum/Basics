bool FileUtils::renameFile(const std::string &path, const std::string &oldname, const std::string &name)
{
    CCASSERT(!path.empty(), "Invalid path");
    std::string oldPath = path + oldname;
    std::string newPath = path + name;
 
    // Rename a file
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    std::regex pat("\\/");
    std::string _old = std::regex_replace(oldPath, pat, "\\");
    std::string _new = std::regex_replace(newPath, pat, "\\");
    if (MoveFileEx(std::wstring(_old.begin(), _old.end()).c_str(), 
        std::wstring(_new.begin(), _new.end()).c_str(),
        MOVEFILE_REPLACE_EXISTING & MOVEFILE_WRITE_THROUGH))
    {
        return true;
    }
    return false;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
    std::regex pat("\\/");
    std::string _old = std::regex_replace(oldPath, pat, "\\");
    std::string _new = std::regex_replace(newPath, pat, "\\");

    if(FileUtils::getInstance()->isFileExist(_new))
    {
        if (!DeleteFileA(_new.c_str()))
        {
            CCLOGERROR("Fail to delete file %s !Error code is 0x%x", newPath.c_str(), GetLastError());
        }
    }

    if (MoveFileA(_old.c_str(), _new.c_str()))
    {
        return true;
    }
    else
    {
        CCLOGERROR("Fail to rename file %s to %s !Error code is 0x%x", oldPath.c_str(), newPath.c_str(), GetLastError());
        return false;
    }
#else
    int errorCode = rename(oldPath.c_str(), newPath.c_str());

    if (0 != errorCode)
    {
        CCLOGERROR("Fail to rename file %s to %s !Error code is %d", oldPath.c_str(), newPath.c_str(), errorCode);
        return false;
    }
    return true;
#endif
}