//! \brief Finds the OS specific directory path to save and retrieve user config data
static const std::string _SetupUserConfigPath()
{
#if defined _WIN32
    char path[MAX_PATH];
    // %APPDATA% (%USERPROFILE%\Application Data)
    if(SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_APPDATA, nullptr, 0, path))) {
        std::string user_path = std::string(path) + "/" APPUPCASEDIRNAME "/";
        if(!DoesFileExist(user_path))
            MakeDirectory(user_path);
        _CopyOldSettingsFile(user_path);
        return user_path;
     }

#elif defined __APPLE__
    passwd *pw = getpwuid(getuid());
    if(pw) {
        std::string path = std::string(pw->pw_dir) + "/Library/Preferences/" APPUPCASEDIRNAME "/";
        if(!DoesFileExist(path))
            MakeDirectory(path);
        return path;
    }

#else // Linux, BSD, other POSIX systems
    // Implementation of the freedesktop specs (at least partially)
    // http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html

    // $XDG_CONFIG_HOME/valyriatear/
    // equals to: ~/.config/valyriatear/ most of the time
    if (getenv("XDG_CONFIG_HOME")) {
        std::string path = std::string(getenv("XDG_CONFIG_HOME")) + "/" APPSHORTNAME "/";
        if(!DoesFileExist(path))
            MakeDirectory(path);
        _CopyOldSettingsFile(path);

        return path;
    }

    // We create a sane default: ~/.config/valyriatear
    passwd *pw = getpwuid(getuid());
    if(pw) {
        std::string path = std::string(pw->pw_dir) + "/.config/";
        if(!DoesFileExist(path))
            MakeDirectory(path);
        path += "/" APPSHORTNAME "/";
        if(!DoesFileExist(path))
            MakeDirectory(path);
        _CopyOldSettingsFile(path);

        return path;
    }
#endif

    // Default path if a specific solution could not be found. Note that this path may
    // not be writable by the user since it could be installed in administrator/root space
    PRINT_WARNING << "could not idenfity user config path, defaulting to system path" << std::endl;
    return "data/";
}