static HANDLE RPCSS_NPConnect(void)
{
  HANDLE the_pipe;
  DWORD dwmode, wait_result;
  HANDLE master_mutex = RPCSS_GetMasterMutex();
  
  WINE_TRACE("\n");

  while (TRUE) {

    wait_result = WaitForSingleObject(master_mutex, MASTER_MUTEX_TIMEOUT);
    switch (wait_result) {
      case WAIT_ABANDONED: 
      case WAIT_OBJECT_0:
        break;
      case WAIT_FAILED:
      case WAIT_TIMEOUT:
      default: 
        WINE_ERR("This should never happen: couldn't enter mutex.\n");
        return NULL;
    }

    /* try to open the client side of the named pipe. */
    the_pipe = CreateFileA(
      NAME_RPCSS_NAMED_PIPE,           /* pipe name */
      GENERIC_READ | GENERIC_WRITE,    /* r/w access */
      0,                               /* no sharing */
      NULL,                            /* no security attributes */
      OPEN_EXISTING,                   /* open an existing pipe */
      0,                               /* default attributes */
      NULL                             /* no template file */
    );

    if (the_pipe != INVALID_HANDLE_VALUE)
      break;

    if (GetLastError() != ERROR_PIPE_BUSY) {
      WINE_WARN("Unable to open named pipe %s (assuming unavailable).\n", 
        wine_dbgstr_a(NAME_RPCSS_NAMED_PIPE));
      break;
    }

    WINE_WARN("Named pipe busy (will wait)\n");
    
    if (!ReleaseMutex(master_mutex))
      WINE_ERR("Failed to release master mutex.  Expect deadlock.\n");

    /* wait for the named pipe.  We are only 
       willing to wait only 5 seconds.  It should be available /very/ soon. */
    if (! WaitNamedPipeA(NAME_RPCSS_NAMED_PIPE, MASTER_MUTEX_WAITNAMEDPIPE_TIMEOUT))
    {
      WINE_ERR("Named pipe unavailable after waiting.  Something is probably wrong.\n");
      return NULL;
    }

  }

  if (the_pipe != INVALID_HANDLE_VALUE) {
    dwmode = PIPE_READMODE_MESSAGE;
    /* SetNamedPipeHandleState not implemented ATM, but still seems to work somehow. */
    if (! SetNamedPipeHandleState(the_pipe, &dwmode, NULL, NULL))
      WINE_WARN("Failed to set pipe handle state\n");
  }

  if (!ReleaseMutex(master_mutex))
    WINE_ERR("Uh oh, failed to leave the RPC Master Mutex!\n");

  return the_pipe;
}