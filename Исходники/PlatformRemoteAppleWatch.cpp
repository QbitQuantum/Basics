Error PlatformRemoteAppleWatch::GetSymbolFile(const FileSpec &platform_file,
                                              const UUID *uuid_ptr,
                                              FileSpec &local_file) {
  Log *log = lldb_private::GetLogIfAllCategoriesSet(LIBLLDB_LOG_HOST);
  Error error;
  char platform_file_path[PATH_MAX];
  if (platform_file.GetPath(platform_file_path, sizeof(platform_file_path))) {
    char resolved_path[PATH_MAX];

    const char *os_version_dir = GetDeviceSupportDirectoryForOSVersion();
    if (os_version_dir) {
      ::snprintf(resolved_path, sizeof(resolved_path), "%s/%s", os_version_dir,
                 platform_file_path);

      local_file.SetFile(resolved_path, true);
      if (local_file.Exists()) {
        if (log) {
          log->Printf("Found a copy of %s in the DeviceSupport dir %s",
                      platform_file_path, os_version_dir);
        }
        return error;
      }

      ::snprintf(resolved_path, sizeof(resolved_path), "%s/Symbols.Internal/%s",
                 os_version_dir, platform_file_path);

      local_file.SetFile(resolved_path, true);
      if (local_file.Exists()) {
        if (log) {
          log->Printf(
              "Found a copy of %s in the DeviceSupport dir %s/Symbols.Internal",
              platform_file_path, os_version_dir);
        }
        return error;
      }
      ::snprintf(resolved_path, sizeof(resolved_path), "%s/Symbols/%s",
                 os_version_dir, platform_file_path);

      local_file.SetFile(resolved_path, true);
      if (local_file.Exists()) {
        if (log) {
          log->Printf("Found a copy of %s in the DeviceSupport dir %s/Symbols",
                      platform_file_path, os_version_dir);
        }
        return error;
      }
    }
    local_file = platform_file;
    if (local_file.Exists())
      return error;

    error.SetErrorStringWithFormat(
        "unable to locate a platform file for '%s' in platform '%s'",
        platform_file_path, GetPluginName().GetCString());
  } else {
    error.SetErrorString("invalid platform file argument");
  }
  return error;
}