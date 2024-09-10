int
set_nonblocking_flag (int desc, bool value)
{
  HANDLE h = (HANDLE) _get_osfhandle (desc);
  if (h == INVALID_HANDLE_VALUE)
    {
      errno = EBADF;
      return -1;
    }
  if (GetFileType (h) == FILE_TYPE_PIPE)
    {
      /* h is a pipe or socket.  */
      DWORD state;
      if (GetNamedPipeHandleState (h, &state, NULL, NULL, NULL, NULL, 0))
        {
          /* h is a pipe.  */
          if ((state & PIPE_NOWAIT) != 0)
            {
              if (value)
                return 0;
              state &= ~PIPE_NOWAIT;
            }
          else
            {
              if (!value)
                return 0;
              state |= PIPE_NOWAIT;
            }
          if (SetNamedPipeHandleState (h, &state, NULL, NULL))
            return 0;
          errno = EINVAL;
          return -1;
        }
      else
        {
          /* h is a socket.  */
          int v = value;
          return ioctl (desc, FIONBIO, &v);
        }
    }
  else
    {
      /* The native Windows API does not support non-blocking on regular
         files.  */
      if (!value)
        return 0;
      errno = ENOTSUP;
      return -1;
    }
}