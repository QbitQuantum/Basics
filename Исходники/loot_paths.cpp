boost::filesystem::path LootPaths::getLocalAppDataPath() {
#ifdef _WIN32
  HWND owner = 0;
  PWSTR path;

  if (SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path) != S_OK)
    throw std::system_error(GetLastError(), std::system_category(), boost::locale::translate("Failed to get %LOCALAPPDATA% path."));

  boost::filesystem::path localAppDataPath(FromWinWide(path));
  CoTaskMemFree(path);

  return localAppDataPath;
#else
        // Use XDG_CONFIG_HOME environmental variable if it's available.
  const char * xdgConfigHome = getenv("XDG_CONFIG_HOME");

  if (xdgConfigHome != nullptr)
    return boost::filesystem::path(xdgConfigHome);

// Otherwise, use the HOME env. var. if it's available.
  xdgConfigHome = getenv("HOME");

  if (xdgConfigHome != nullptr)
    return boost::filesystem::path(xdgConfigHome) / ".config";

// If somehow both are missing, use the current path.
  return boost::filesystem::current_path();
#endif
}