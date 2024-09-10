inline Try<Nothing> nonblock(int fd)
{
  if (net::is_socket(fd)) {
    const u_long non_block_mode = 1;
    u_long mode = non_block_mode;

    int result = ioctlsocket(fd, FIONBIO, &mode);
    if (result != NO_ERROR) {
      return WindowsSocketError();
    }
  } else {
    // Extract handle from file descriptor.
    HANDLE handle = reinterpret_cast<HANDLE>(::_get_osfhandle(fd));
    if (handle == INVALID_HANDLE_VALUE) {
      return WindowsError("Failed to get `HANDLE` for file descriptor");
    }

    if (GetFileType(handle) == FILE_TYPE_PIPE) {
      DWORD pipe_mode = PIPE_NOWAIT;
      if (SetNamedPipeHandleState(handle, &pipe_mode, nullptr, nullptr)) {
        return WindowsError();
      }
    }
  }

  return Nothing();
}