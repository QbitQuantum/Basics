int fcntl(int fd, int cmd, ...)
{
   va_list va;
   int     res = -1;

   va_start (va, cmd);

   if (cmd == F_GETFD)
     {
        HANDLE  h;
        DWORD flag;

        h = (HANDLE)_get_osfhandle(fd);
        if (h == INVALID_HANDLE_VALUE)
          return -1;

	if (!GetHandleInformation(h, &flag))
          {
             /* FIXME: should we close h ? MSDN seems to say that */
             return -1;
          }

	res = 0;
     }

   if (cmd == F_SETFD)
     {
        HANDLE  h;
        long flag;

        h = (HANDLE)_get_osfhandle(fd);
        if (h == INVALID_HANDLE_VALUE)
          return -1;

        flag = va_arg(va, long);
        if (flag == FD_CLOEXEC)
          {
             if (SetHandleInformation(h, HANDLE_FLAG_INHERIT, 0))
               res = 0;
          }
     }