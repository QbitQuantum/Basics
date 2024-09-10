std::string sysdep_get_homedir()
{
    char buf[MAX_PATH];

#if 1  // works under win98se
    if (SUCCEEDED(SHGetSpecialFolderPathA(NULL, buf, CSIDL_PERSONAL,FALSE)))
#else  // newer version for NT only
    if (SUCCEEDED(SHGetFolderPath(NULL,CSIDL_PERSONAL,NULL,0,buf)))
#endif
    {
        return std::string(buf);
    }
    else
    {
        return std::string();
    }
}