/**
 * Redirects the output streams to point to the log file with the given path.
 *
 * @param path specifies the location of log file, may start with ~
 * @param append should be nonzero if it should not truncate the log file.
 */
static int setup_logging(const char *path, int append) {
#ifdef _WIN32
  // Does it start with a tilde?  Perform tilde expansion if so.
  wchar_t pathw[MAX_PATH * 2];
  size_t offset = 0;
  if (path[0] == '~' && (path[1] == 0 || path[1] == '/' || path[1] == '\\')) {
    // Strip off the tilde.
    ++path;

    // Get the home directory path for the current user.
    if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, pathw))) {
      return 0;
    }
    offset = wcslen(pathw);
  }

  // We need to convert the rest of the path from UTF-8 to UTF-16.
  if (MultiByteToWideChar(CP_UTF8, 0, path, -1, pathw + offset,
                          (int)(_countof(pathw) - offset)) == 0) {
    return 0;
  }

  DWORD access = append ? FILE_APPEND_DATA : (GENERIC_READ | GENERIC_WRITE);
  int creation = append ? OPEN_ALWAYS : CREATE_ALWAYS;
  HANDLE handle = CreateFileW(pathw, access, FILE_SHARE_DELETE | FILE_SHARE_READ,
                              NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);

  if (handle == INVALID_HANDLE_VALUE) {
    // Make the parent directories first.
    mkdir_parent(pathw);
    handle = CreateFileW(pathw, access, FILE_SHARE_DELETE | FILE_SHARE_READ,
                         NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
  }

  if (handle == INVALID_HANDLE_VALUE) {
    return 0;
  }

  if (append) {
    SetFilePointer(handle, 0, NULL, FILE_END);
  }

  SetStdHandle(STD_OUTPUT_HANDLE, handle);
  SetStdHandle(STD_ERROR_HANDLE, handle);

  // If we are running under the UCRT in a GUI application, we can't be sure
  // that we have valid fds for stdout and stderr, so we have to set them up.
  // One way to do this is to reopen them to something silly (like NUL).
  if (_fileno(stdout) < 0) {
    _close(1);
    _wfreopen(L"\\\\.\\NUL", L"w", stdout);
  }

  if (_fileno(stderr) < 0) {
    _close(2);
    _wfreopen(L"\\\\.\\NUL", L"w", stderr);
  }

  // Now replace the stdout and stderr file descriptors with one pointing to
  // our desired handle.
  int fd = _open_osfhandle((intptr_t)handle, _O_WRONLY | _O_TEXT | (append ? _O_APPEND : 0));
  _dup2(fd, _fileno(stdout));
  _dup2(fd, _fileno(stderr));
  _close(fd);

  return 1;
#else
  // Does it start with a tilde?  Perform tilde expansion if so.
  char buffer[PATH_MAX * 2];
  size_t offset = 0;
  if (path[0] == '~' && (path[1] == 0 || path[1] == '/')) {
    // Strip off the tilde.
    ++path;

    // Get the home directory path for the current user.
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
      home_dir = getpwuid(getuid())->pw_dir;
    }
    offset = strlen(home_dir);
    assert(offset < sizeof(buffer));
    strncpy(buffer, home_dir, sizeof(buffer));
  }

  // Copy over the rest of the path.
  strcpy(buffer + offset, path);

  mode_t mode = O_CREAT | O_WRONLY | (append ? O_APPEND : O_TRUNC);
  int fd = open(buffer, mode, 0644);
  if (fd == -1) {
    // Make the parent directories first.
    mkdir_parent(buffer);
    fd = open(buffer, mode, 0644);
  }

  if (fd == -1) {
    perror(buffer);
    return 0;
  }

  fflush(stdout);
  fflush(stderr);

  dup2(fd, 1);
  dup2(fd, 2);

  close(fd);
  return 1;
#endif
}