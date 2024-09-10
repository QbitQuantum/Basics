LPCSTR PlugSetPath(LPSTR pBuff, LPCSTR prefix, LPCSTR FileName, LPCSTR defpath)
  {
  char newname[_MAX_PATH];
  char direc[_MAX_DIR], defdir[_MAX_DIR], tmpdir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ftype[_MAX_EXT];
#if !defined(UNIX) && !defined(UNIV_LINUX)
  char drive[_MAX_DRIVE], defdrv[_MAX_DRIVE];
#else
  char *drive = NULL, *defdrv = NULL;
#endif

  if (!strncmp(FileName, "//", 2) || !strncmp(FileName, "\\\\", 2)) {
    strcpy(pBuff, FileName);       // Remote file
    return pBuff;
    } // endif

  if (PlugIsAbsolutePath(FileName))
  {
    strcpy(pBuff, FileName); // FileName includes absolute path
    return pBuff;
  } // endif
  
#if !defined(WIN32)
  if (*FileName == '~') {
    if (_fullpath(pBuff, FileName, _MAX_PATH)) {
      if (trace > 1)
        htrc("pbuff='%s'\n", pBuff);

     return pBuff;
    } else
      return FileName;     // Error, return unchanged name
      
    } // endif FileName  
#endif   // !WIN32
  
  if (prefix && strcmp(prefix, ".") && !PlugIsAbsolutePath(defpath))
  {
    char tmp[_MAX_PATH];
    int len= snprintf(tmp, sizeof(tmp) - 1, "%s%s%s",
                      prefix, defpath, FileName);
    memcpy(pBuff, tmp, (size_t) len);
    pBuff[len]= '\0';
    return pBuff;
  }

  _splitpath(FileName, drive, direc, fname, ftype);

  if (defpath) {
    char c = defpath[strlen(defpath) - 1];

    strcpy(tmpdir, defpath);

    if (c != '/' && c != '\\')
      strcat(tmpdir, "/");

  } else
    strcpy(tmpdir, "./");

  _splitpath(tmpdir, defdrv, defdir, NULL, NULL);

  if (trace > 1) {
    htrc("after _splitpath: FileName=%s\n", FileName);
#if defined(UNIX) || defined(UNIV_LINUX)
    htrc("dir=%s fname=%s ext=%s\n", direc, fname, ftype);
#else
    htrc("drive=%s dir=%s fname=%s ext=%s\n", drive, direc, fname, ftype);
    htrc("defdrv=%s defdir=%s\n", defdrv, defdir);
#endif
    } // endif trace

  if (drive && !*drive)
    strcpy(drive, defdrv);

  switch (*direc) {
    case '\0':
      strcpy(direc, defdir);
      break;
    case '\\':
    case '/':
      break;
    default:
      // This supposes that defdir ends with a SLASH
      strcpy(direc, strcat(defdir, direc));
    } // endswitch

  _makepath(newname, drive, direc, fname, ftype);

  if (trace > 1)
    htrc("newname='%s'\n", newname);

  if (_fullpath(pBuff, newname, _MAX_PATH)) {
    if (trace > 1)
      htrc("pbuff='%s'\n", pBuff);

    return pBuff;
  } else
    return FileName;     // Error, return unchanged name

  } // end of PlugSetPath