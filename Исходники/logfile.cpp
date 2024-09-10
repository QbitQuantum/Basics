UnicodeString Logfile::getFilename(const UnicodeString& logfileName)
{
    auto logsDirectory = UnicodeString::Period;

#ifdef WINDOWS

    // On Windows logfiles are put into the current user's AppData/Roaming/<client name> directory
    auto path = PWSTR();
    SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);
    logsDirectory = FileSystem::joinPaths(fromUTF16(path), Globals::getClientName());
    CoTaskMemFree(path);

#elif defined(LINUX)

    // On Linux logfiles are put into the ~/.<client name> directory
    logsDirectory = FileSystem::joinPaths(FileSystem::getHomeDirectory(), String::Period + Globals::getClientName());

#elif defined(APPLE)

    // Put logfiles under ~/Library/Logs
    logsDirectory = FileSystem::joinPaths(FileSystem::getUserLibraryDirectory(), "Logs");

#ifdef MACOS
    logsDirectory = FileSystem::joinPaths(logsDirectory, Globals::getClientName());
#endif

#endif

    return FileSystem::joinPaths(logsDirectory, logfileName + ".html");
}