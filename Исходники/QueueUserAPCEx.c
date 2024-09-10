DWORD QueueUserAPCEx(PAPCFUNC pfnApc, HANDLE hThread, DWORD dwData)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      Adds a user-mode asynchronous procedure call (APC) object
      *      to the APC queue of the specified thread AND sets this
      *      thread in alertarte state.
      *
      * PARAMETERS
      *      Uses the same parameters as QueueUserAPC.
      *
      * DESCRIPTION
      *      Adds a user-mode asynchronous procedure call (APC) object
      *      to the APC queue of the specified thread AND sets this
      *      thread in alertarte state.
      *
      * RESULTS
	  *		 1    Success
	  *      0    Failure
      * ------------------------------------------------------
      */
{
  DWORD cbReturned;

  /* trivial case */
  if (hThread == GetCurrentThread())
    {
      if (!QueueUserAPC(pfnApc, hThread, dwData))
        {
	      return 0;
        }

      SleepEx(0, TRUE);
      return 1;
    }

  if (INVALID_HANDLE_VALUE == hDevice
      /* && !QueueUserAPCEx_Init() */
      )
    {
      printf ("Can't get a handle to the ALERT driver\n");

      return 0;
    }

  /* probably not necessary */
  if (SuspendThread(hThread) == -1)
    {
      return 0;
    }

  /* Send the APC */
  if (!QueueUserAPC(pfnApc, hThread, dwData))
    {
      return 0;
    }

  /* Ensure the execution of the APC */
  if (DeviceIoControl (hDevice, (DWORD)IOCTL_ALERTDRV_SET_ALERTABLE2, &hThread, sizeof(HANDLE),
		NULL, 0, &cbReturned, 0))
    {
	}
  else
    {
      printf ("DeviceIoControl failed\n");
      return 0;
    }

  /* Here, we could even cancel suspended threads */
  ResumeThread(hThread);

  return 1;
}