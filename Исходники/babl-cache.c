static const char *fish_cache_path (void)
{
  struct stat stat_buf;
  static char path[4096];

  strncpy (path, FALLBACK_CACHE_PATH, 4096);
#ifndef _WIN32
  if (getenv ("HOME"))
    sprintf (path, "%s/.cache/babl/babl-fishes", getenv("HOME"));
#else
{
  char win32path[4096];
  if (SHGetFolderPathA (NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, win32path) == S_OK)
    sprintf (path, "%s\\%s\\babl-fishes.txt", win32path, BABL_LIBRARY);
  else if (getenv ("TEMP"))
    sprintf (path, "%s\\babl-fishes.txt", getenv("TEMP"));
}
#endif

  if (stat (path, &stat_buf)==0 && S_ISREG(stat_buf.st_mode))
    return path;

  if (mk_ancestry (path) != 0)
    return FALLBACK_CACHE_PATH;

  return path;
}