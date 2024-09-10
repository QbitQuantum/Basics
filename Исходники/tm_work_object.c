/* realpath implementation for Windows found at http://bugzilla.gnome.org/show_bug.cgi?id=342926
 * this one is better than e.g. liberty's lrealpath because this one uses Win32 API and works
 * with special chars within the filename */
static char *realpath (const char *pathname, char *resolved_path)
{
  int size;

  if (resolved_path != NULL)
  {
    int path_max = get_path_max(pathname);
	size = GetFullPathNameA (pathname, path_max, resolved_path, NULL);
    if (size > path_max)
      return NULL;
    else
      return resolved_path;
  }
  else
  {
    size = GetFullPathNameA (pathname, 0, NULL, NULL);
    resolved_path = g_new0 (char, size);
    GetFullPathNameA (pathname, size, resolved_path, NULL);
    return resolved_path;
  }
}