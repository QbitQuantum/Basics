/*
 * Convert to forward slashes. Resolve to full pathname optionally
*/
char* w32ify(char* filename, int resolve)
{
  static char w32_path[FILENAME_MAX];
  char* p;
  
  if (resolve)
    _fullpath(w32_path, filename, sizeof(w32_path));
  else
    strncpy(w32_path, filename, sizeof(w32_path));
  
  for (p = w32_path; p && *p; p++)
    if (*p == '\\')
      *p = '/';
    
    return w32_path;
}