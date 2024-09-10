int
wisvc_StartKublService (int argc, char **argv, SC_HANDLE schService,
			char *service_name, char *BinaryPathName,
			int discard_argv)
{				/* The last two arguments not really needed except for error messages */
  int called_as_service = 0;	/* Needed by macro err_printf */
  int checkpoint_has_stayed_stagnant_n_iterations = 0;
  SERVICE_STATUS ssStatus;
  DWORD dwOldCheckPoint = 0, dwOlderCheckPoint = 0;

/*
   err_printf(("StartKublService: argc=%d, argv[0]=%s, argv[1]=%s\n",
   argc,argv[0],argv[1]));
 */

  if (!StartService (schService,	/* handle of service    */
		     (discard_argv ? 0 : (argc - 1)),	/* number of arguments  */
		     (discard_argv ? NULL : (argv + 1))))	/* Arg vector from main */
    {				/* without argv[0] */
      DWORD erhe = GetLastError ();

      err_printf ((
		    "%s: Starting service \"%s\" (path: \"%s\") failed. "
		    "StartService returned zero, errno=%ld%s\n",
		    argv[0], service_name, BinaryPathName, erhe,
		    ((ERROR_SERVICE_ALREADY_RUNNING == erhe) ?
		     " because service has been already started!" : ".")
		  ));
      return (0);
    }
  else
    {
      err_printf (("Service %s start in progress, BinaryPathName=%s\n",
		   service_name, BinaryPathName));
    }

  /* Check the status until the service is running. */

  if (!QueryServiceStatus (schService,	/* handle of service       */
			   &ssStatus))	/* address of status info  */
    {
      DWORD erhe = GetLastError ();

      err_printf ((
	     "%s: Querying status of service \"%s\" (path: \"%s\") failed. "
		    "QueryServiceStatus returned zero, errno=%ld.\n",
		    argv[0], service_name, BinaryPathName, erhe));
      return (0);
    }

  Sleep (10);			/* First sleep ten seconds. */
  while (ssStatus.dwCurrentState != SERVICE_RUNNING)
    {
      if (SERVICE_STOPPED == ssStatus.dwCurrentState)
	{
	  break;
	}

      dwOlderCheckPoint = dwOldCheckPoint;
      dwOldCheckPoint = ssStatus.dwCheckPoint;	/* Save current checkpoint */

      if (ssStatus.dwWaitHint > 300)
	{
	  ssStatus.dwWaitHint = 300;
	}
      Sleep (ssStatus.dwWaitHint);	/* Wait for the specified interval. */

      /* Check the status again. */
      if (!QueryServiceStatus (schService, &ssStatus))
	{
	  break;
	}
/*
   err_printf((
   "dwOlderCheckPoint=%ld, dwOldCheckPoint=%ld, ssStatus.dwCheckPoint=%ld, ssStatus.dwWaitHint=%ld\n",
   dwOlderCheckPoint, dwOldCheckPoint,
   ssStatus.dwCheckPoint, ssStatus.dwWaitHint));
 */

/* Break if the checkpoint has not been incremented for three times. */
      if ((dwOldCheckPoint >= ssStatus.dwCheckPoint)
	  && (dwOlderCheckPoint >= ssStatus.dwCheckPoint))
	{
	  if (++checkpoint_has_stayed_stagnant_n_iterations > 3)
	    {
	      break;
	    }
	}
      checkpoint_has_stayed_stagnant_n_iterations = 0;
    }


  if (ssStatus.dwCurrentState == SERVICE_RUNNING)
    {
      {
	err_printf ((
		 "%s: Service \"%s\" started successfully (path: \"%s\").\n",
		      argv[0], service_name, BinaryPathName));
      }
      return (1);
    }
  else
    {
      err_printf ((
		"%s: Service \"%s\" (path: \"%s\") %s started correctly.\n",
		    argv[0], service_name, BinaryPathName,
	     ((SERVICE_START_PENDING != ssStatus.dwCurrentState) ? "has not"
	      : "may or may not have")));
      err_printf (("  Current State: %d\n",
		   ssStatus.dwCurrentState));
      err_printf (("  Exit Code: %d\n", ssStatus.dwWin32ExitCode));
      err_printf (("  Service Specific Exit Code: %d\n",
		   ssStatus.dwServiceSpecificExitCode));
      err_printf (("  Check Point: %d\n", ssStatus.dwCheckPoint));
      err_printf (("  Wait Hint: %d\n", ssStatus.dwWaitHint));
      err_printf ((
		    "Please use services icon in Control Panel to see whether service \"%s\" was really started."
	 " Check also the file wi.err in the server's working directory.\n",
		    service_name));
      return (0);
    }
}