    /*
     * The ServiceMain function to start service.
     */
VOID WINAPI
ServiceMain (DWORD argc, LPTSTR argv[])
{
  SECURITY_ATTRIBUTES SecurityAttributes;
  DWORD dwThreadId;

  /*
   * Input Arguments to function startup 
   */
  DWORD ArgCount = 0;
  LPTSTR *ArgArray = NULL;
  TCHAR szRegKey[512];
  TCHAR szValue[128];
  DWORD nSize;
  HKEY hParamKey = NULL;	/* To read startup parameters */
  DWORD TotalParams = 0;
  DWORD i;
  InputParams ThreadInputParams;

  /*
   * Build the Input parameters to pass to worker thread 
   */

  /*
   * SCM sends Service Name as first arg, increment to point
   * arguments user specified while starting contorl agent
   */

  /*
   * Read registry parameter 
   */
  ArgCount = 1;

  /*
   * Create Registry Key path 
   */
  _snprintf (szRegKey, sizeof(szRegKey), "%s%s\\%s",
	     _T ("SYSTEM\\CurrentControlSet\\Services\\"), app_name,
	     "Parameters");
  if (RegOpenKeyEx
      (HKEY_LOCAL_MACHINE, szRegKey, 0, KEY_ALL_ACCESS, &hParamKey) == ERROR_SUCCESS)
    {

      /*
       * Read startup Configuration information 
       */
      /*
       * Find number of subkeys inside parameters 
       */
      if (RegQueryInfoKey (hParamKey, NULL, NULL, 0,
	   NULL, NULL, NULL, &TotalParams,
	   NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
	{
	  if (TotalParams != 0)
	    {
	      ArgCount += TotalParams;

	      /*
	       * Allocate memory to hold strings 
	       */
	      ArgArray = (LPTSTR *) malloc (sizeof (LPTSTR) * ArgCount);

	      /*
	       * Copy first argument 
	       */
	      ArgArray[0] = _tcsdup (argv[0]);
	      for (i = 1; i <= TotalParams; i++)
		{

		  /*
		   * Create Subkey value name 
		   */
		  _snprintf (szRegKey, sizeof(szRegKey), "%s%d", "Param", i);

		  /*
		   * Set size 
		   */
		  nSize = 128;
		  RegQueryValueEx (hParamKey, szRegKey, 0, NULL,
				   (LPBYTE) & szValue, &nSize);
		  ArgArray[i] = _tcsdup (szValue);
		}
	    }
	}
      RegCloseKey (hParamKey);
    }
  if (ArgCount == 1)
    {

      /*
       * No statup agrs are given 
       */
      ThreadInputParams.Argc = argc;
      ThreadInputParams.Argv = argv;
    }

  else
    {
      ThreadInputParams.Argc = ArgCount;
      ThreadInputParams.Argv = ArgArray;
    }

  /*
   * Register Service Control Handler 
   */
  hServiceStatus = RegisterServiceCtrlHandler (app_name, ControlHandler);
  if (hServiceStatus == 0)
    {
      WriteToEventLog (EVENTLOG_ERROR_TYPE,
		       _T ("RegisterServiceCtrlHandler failed"));
      return;
    }

  /*
   * Update the service status to START_PENDING 
   */
  UpdateServiceStatus (SERVICE_START_PENDING, NO_ERROR, SCM_WAIT_INTERVAL);

  /*
   * Spin of worker thread, which does majority of the work 
   */
  TRY
  {
    if (SetSimpleSecurityAttributes (&SecurityAttributes) == FALSE)
      {
	WriteToEventLog (EVENTLOG_ERROR_TYPE,
			 _T ("Couldn't init security attributes"));
	LEAVE;
      }
    hServiceThread =
      (void *) _beginthreadex (&SecurityAttributes, 0,
			       ThreadFunction,
			       (void *) &ThreadInputParams, 0, &dwThreadId);
    if (hServiceThread == NULL)
      {
	WriteToEventLog (EVENTLOG_ERROR_TYPE, _T ("Couldn't start worker thread"));
	LEAVE;
      }

    /*
     * Set Service Status to Running 
     */
    UpdateServiceStatus (SERVICE_RUNNING, NO_ERROR, SCM_WAIT_INTERVAL);

    /*
     * Wait for termination event and worker thread to
     * * spin down.
     */
    WaitForSingleObject (hServiceThread, INFINITE);
  }
  FINALLY
  {
    /*
     * Release resources 
     */
    UpdateServiceStatus (SERVICE_STOPPED, NO_ERROR, SCM_WAIT_INTERVAL);
    if (hServiceThread)
      CloseHandle (hServiceThread);
    FreeSecurityAttributes (&SecurityAttributes);

    /*
     * Delete allocated argument list 
     */
    if (ArgCount > 1 && ArgArray != NULL)
      {
	/*
	 * Delete all strings 
	 */
	for (i = 0; i < ArgCount; i++)
	  {
	    free (ArgArray[i]);
	  }
	free (ArgArray);
      }
  }
}