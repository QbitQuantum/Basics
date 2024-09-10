DWORD WINAPI worker_wait (LPVOID _data)
{
  BOOL     bExit;
  LPWORKER lpWorker;
 
  lpWorker = (LPWORKER )_data;
  bExit    = FALSE;

#ifdef DBUG
  dbug_print("Worker %x starting", lpWorker);
#endif
  while (
      !bExit 
      && SignalObjectAndWait(
        lpWorker->hWorkerReady, 
        lpWorker->hCommandReady,
        INFINITE, 
        TRUE) == WAIT_OBJECT_0)
  {
#ifdef DBUG
    dbug_print("Worker %x running", lpWorker);
#endif
    switch (lpWorker->ECommand)
    {
      case WORKER_CMD_NONE:
        break;

      case WORKER_CMD_EXEC:
        if (lpWorker->hJobFunc != NULL)
        {
          SetEvent(lpWorker->hJobStarted);
          lpWorker->hJobFunc(lpWorker->hJobStop, lpWorker->lpJobUserData);
          SetEvent(lpWorker->hJobDone);
        };
        break;

      case WORKER_CMD_STOP:
        bExit = TRUE;
        break;
    }
  };
#ifdef DBUG
  dbug_print("Worker %x exiting", lpWorker);
#endif

  return 0;
}