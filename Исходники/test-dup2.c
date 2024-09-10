/* Return non-zero if FD is open and inheritable across exec/spawn.  */
static int
is_inheritable (int fd)
{
# if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
  /* On Win32, the initial state of unassigned standard file
     descriptors is that they are open but point to an
     INVALID_HANDLE_VALUE, and there is no fcntl.  */
  HANDLE h = (HANDLE) _get_osfhandle (fd);
  DWORD flags;
  if (h == INVALID_HANDLE_VALUE || GetHandleInformation (h, &flags) == 0)
    return 0;
  return (flags & HANDLE_FLAG_INHERIT) != 0;
# else
#  ifndef F_GETFD
#   error Please port fcntl to your platform
#  endif
  int i = fcntl (fd, F_GETFD);
  return 0 <= i && (i & FD_CLOEXEC) == 0;
# endif
}