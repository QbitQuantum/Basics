char *LocateCfgFile(const char *filename, char *paths_to_check[])
// 喘ergabe: filename == string im 8.3 format
// R…kgabe: vollst. Pfad zur gefundenen Datei (current dir first)
{
  int i = 0;
  static char fullpath[_MAX_PATH];

  while (paths_to_check[i] != NULL) {
    _searchenv(filename, paths_to_check[i], fullpath);
    if (fullpath[0]) break;
    i++;
  }

  if (fullpath[0])
    return &fullpath;
  else
    return NULL;

} // LocateCfgFile()