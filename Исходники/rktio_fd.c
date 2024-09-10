int rktio_system_fd_is_terminal(rktio_t *rktio, intptr_t fd)
{
#ifdef RKTIO_SYSTEM_UNIX
  return isatty(fd);
#endif
#ifdef RKTIO_SYSTEM_WINDOWS
  if (GetFileType((HANDLE)fd) == FILE_TYPE_CHAR) {
    DWORD mode;
    if (GetConsoleMode((HANDLE)fd, &mode))
      return 1;
    else
      return 0;
  } else
    return 0;
#endif
}