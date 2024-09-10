static void
_efl_net_socket_windows_handle_close(HANDLE h)
{
   if (!FlushFileBuffers(h))
     {
        DWORD win32err = GetLastError();
        if (win32err != ERROR_PIPE_NOT_CONNECTED)
          {
             char *msg = _efl_net_windows_error_msg_get(GetLastError());
             WRN("HANDLE=%p could not flush buffers: %s", h, msg);
             free(msg);
          }
     }
   if (!DisconnectNamedPipe(h))
     {
        DWORD win32err = GetLastError();
        if ((win32err != ERROR_NOT_SUPPORTED) && /* dialer socket don't support it */
            (win32err != ERROR_PIPE_NOT_CONNECTED))
          {
             char *msg = _efl_net_windows_error_msg_get(win32err);
             WRN("HANDLE=%p could not disconnect: %s", h, msg);
             free(msg);
          }
     }
   CloseHandle(h);
   DBG("HANDLE=%p closed", h);
}