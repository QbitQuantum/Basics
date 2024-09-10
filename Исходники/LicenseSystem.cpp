String LicenseSystem::GenerateMachineID()
{
#if defined(ATOMIC_PLATFORM_OSX) || defined(ATOMIC_PLATFORM_LINUX)
    String path = getenv("HOME");
#else
    wchar_t pathName[MAX_PATH];
    pathName[0] = 0;
    SHGetSpecialFolderPathW(0, pathName, CSIDL_PERSONAL, 0);
    String path(pathName);
#endif

    Poco::MD5Engine md5;
    md5.update(path.CString(), path.Length());
    String id = Poco::MD5Engine::digestToHex(md5.digest()).c_str();
    return id;
}