/* Return true if FD is not inherited to child processes.  */
static bool
is_cloexec (int fd)
{
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
  HANDLE h = (HANDLE) _get_osfhandle (fd);
  DWORD flags;
  ASSERT (GetHandleInformation (h, &flags));
  return (flags & HANDLE_FLAG_INHERIT) == 0;
#else
  int flags;
  ASSERT ((flags = fcntl (fd, F_GETFD)) >= 0);
  return (flags & FD_CLOEXEC) != 0;
#endif
}