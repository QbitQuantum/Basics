//////////////////////////////////////////////////////////////////////////////
// main
//
// Note: XPCOM cannot be used until AttemptGRELoad has returned successfully.
int
main(int argc, char* argv[])
{
  pargc = &argc;
  pargv = &argv;
  nsresult rv;
  char buffer[MAXPATHLEN];
  wchar_t wbuffer[MAXPATHLEN];

  // Set up curEXEPath
  if (!GetModuleFileNameW(0, wbuffer, MAXPATHLEN)) {
    Output("Couldn't calculate the application directory.");
    return 255;
  }
  wcsncpy(curExePath, wbuffer, MAXPATHLEN);

  // Get the current directory into wbuffer
  wchar_t* lastSlash = wcsrchr(wbuffer, L'\\');
  if (!lastSlash) {
    Output("Application directory format not understood.");
    return 255;
  }
  *(++lastSlash) = L'\0';

  // Set up backup file path
  if (wcslen(wbuffer) + _countof(kAPP_RT_BACKUP) >= MAXPATHLEN) {
    Output("Application directory path is too long (couldn't set up backup file path).");
  }
  wcsncpy(lastSlash, kAPP_RT_BACKUP, _countof(kAPP_RT_BACKUP));
  wcsncpy(backupFilePath, wbuffer, MAXPATHLEN);

  *lastSlash = L'\0';

  // Convert current directory to utf8 and stuff it in buffer
  if (0 == WideCharToMultiByte(CP_UTF8,
                               0,
                               wbuffer,
                               -1,
                               buffer,
                               MAXPATHLEN,
                               NULL,
                               NULL)) {
    Output("Application directory could not be processed.");
    return 255;
  }

  // Set up appIniPath with path to webapp.ini.
  // This should be in the same directory as the running executable.
  char appIniPath[MAXPATHLEN];
  if (NS_FAILED(joinPath(appIniPath, buffer, kWEBAPP_INI, MAXPATHLEN))) {
    Output("Path to webapp.ini could not be processed.");
    return 255;
  }

  // Open webapp.ini as an INI file (as opposed to using the
  // XRE webapp.ini-specific processing we do later)
  nsINIParser parser;
  if (NS_FAILED(parser.Init(appIniPath))) {
    Output("Could not open webapp.ini");
    return 255;
  }

  // Set up our environment to know where webapp.ini was loaded from.
  char appEnv[MAXPATHLEN + _countof(kAPP_ENV_PREFIX)];
  strcpy(appEnv, kAPP_ENV_PREFIX);
  strcpy(appEnv + _countof(kAPP_ENV_PREFIX) - 1, appIniPath);
  if (putenv(appEnv)) {
    Output("Couldn't set up app environment");
    return 255;
  }

  // Get profile dir from webapp.ini
  if (NS_FAILED(parser.GetString("Webapp",
                                 "Profile",
                                 profile,
                                 MAXPATHLEN))) {
    Output("Unable to retrieve profile from web app INI file");
    return 255;
  }

  char firefoxDir[MAXPATHLEN];

  // First attempt at loading Firefox binaries:
  //   Get the location of Firefox from our webapp.ini

  // XXX: This string better be UTF-8...
  rv = parser.GetString("WebappRT",
                        "InstallDir",
                        firefoxDir,
                        MAXPATHLEN);
  if (NS_SUCCEEDED(rv)) {
    if (AttemptLoadFromDir(firefoxDir)) {
      return 0;
    }
  }

  // Second attempt at loading Firefox binaries:
  //   Get the location of Firefox from the registry
  if (GetFirefoxDirFromRegistry(firefoxDir)) {
    if (AttemptLoadFromDir(firefoxDir)) {
      // XXX: Write gre dir location to webapp.ini
      return 0;
    }
  }

  // We've done all we know how to do to try to find and launch FF
  Output("This app requires that Firefox version 15 or above is installed."
         " Firefox 15+ has not been detected.");
  return 255;
}