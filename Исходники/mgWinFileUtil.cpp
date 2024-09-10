//--------------------------------------------------------------
// find a file in parent directories
BOOL mgOSFindFile(
  mgString& location,
  const char* fileName)
{
  WCHAR* oldCWD = _wgetcwd(NULL, 0);
  if (oldCWD == NULL)
    return false;
  mgString cwd(oldCWD);

  while (true)
  {
    if (cwd.endsWith("\\"))
      location.format("%s%s", (const char*) cwd, fileName);
    else location.format("%s\\%s", (const char*) cwd, fileName);

    WCHAR* wideName;
    int wideLen;
    location.toWCHAR(wideName, wideLen);
    struct _stat filestat;
    BOOL found = 0 == _wstat(wideName, &filestat);
    delete wideName; wideName = NULL;

    if (found)
      return true;
    else
    {
      // remove last directory from cwd
      int slash = cwd.reverseFind(cwd.length(), '\\');
      if (slash != -1)
        cwd.deleteAt(slash, cwd.length()-slash);
      else return false;   // no more directories. file not found.
    }
  }
}