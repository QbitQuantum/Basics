int OpenTempFile(const char* prefix)
{
  unsigned c = 0;
  std::string tname = prefix;
  tname += "_";
  tname += std::to_string(_getpid());
  tname += "_";
  while (c++ < 20) { // Loop because several threads can generate same filename.
#ifdef _WIN32
    char dir[MAX_PATH+1];
    if (!GetTempPath(sizeof(dir), dir)) { return -1; }
#else // _WIN32
    char *dir = NULL;
#endif // _WIN32
    char *name = _tempnam(dir, tname.c_str());
    if (!name) { return -1; }
#ifdef _WIN32
    HANDLE h = CreateFile(
      name,
      GENERIC_READ | GENERIC_WRITE,
      0, // No sharing
      NULL,
      CREATE_NEW,
      FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE,
      NULL);
    free(name);
    if (h == INVALID_HANDLE_VALUE) { continue; }
    return _open_osfhandle((intptr_t)h, 0);
#else // _WIN32
    int d = _open(name, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (d < 0) { free(name); continue; }
    if (unlink(name) < 0) { free(name); _close(d); return -1; }
    free(name);
    return d;
#endif // _WIN32
  }
  return -1;
}