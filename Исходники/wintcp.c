/*
 * css_windows_startup() -
 *   return:
 */
int
css_windows_startup (void)
{
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

  old_hook = NULL;
  css_Wsa_error = CSS_ER_WINSOCK_NOERROR;
  wVersionRequested = 0x101;
  err = WSAStartup (wVersionRequested, &wsaData);
  if (err != 0)
    {
      /* don't use WSAGetLastError since it has not been initialized. */
      css_Wsa_error = CSS_ER_WINSOCK_STARTUP;
      er_set (ER_ERROR_SEVERITY, ARG_FILE_LINE, ER_CSS_WINSOCK_STARTUP, 1, err);
      return -1;
    }

  max_socket_fds = wsaData.iMaxSockets;

#if 0
  /* 
   * Establish a blocking "hook" function to prevent Windows messages
   * from being dispatched when we block on reads.
   */
  old_hook = WSASetBlockingHook ((FARPROC) css_windows_blocking_hook);
  if (old_hook == NULL)
    {
      /* couldn't set up our hook */
      css_Wsa_error = CSS_ER_WINSOCK_BLOCKING_HOOK;
      er_set (ER_ERROR_SEVERITY, ARG_FILE_LINE, ER_CSS_WINSOCK_STARTUP, 1, WSAGetLastError ());
      (void) WSACleanup ();
      return -1;
    }
#endif

  wsa_Init_count++;

  return 1;
}