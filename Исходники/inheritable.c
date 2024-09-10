int get_inheritable(int fd) {
#ifdef MS_WINDOWS
   HANDLE handle;
   DWORD flags = 0;

   handle = (HANDLE)_get_osfhandle(fd);
   if (handle == INVALID_HANDLE_VALUE) {
      return -1;
   }

   if (!GetHandleInformation(handle, &flags)) {
      return -1;
   }

   return (flags & HANDLE_FLAG_INHERIT);
#else
   int flags = 0;

   flags = fcntl(fd, F_GETFD, 0);
   if (flags == -1) {
      return -1;
   }
   return !(flags & FD_CLOEXEC);
#endif
}