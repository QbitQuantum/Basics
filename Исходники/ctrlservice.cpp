int
_tmain (int argc, char *argv[])
{
  bool rc;

  // Install a Service if -i switch used
  if (argc == 2)
    {
      if (_stricmp (argv[1], "-u") == 0)
	{
	  vDelService ();
	}
      else if (_stricmp (argv[1], "-start") == 0)
	{
	  vStartService ();
	}
      else if (_stricmp (argv[1], "-stop") == 0)
	{
	  vStopService ();
	}
      else if (_stricmp (argv[1], "-status") == 0)
	{
	  vPrintServiceStatus ();
	}
      else
	WriteLog (sLogFile, "Invalid Argument.\n");
    }
  else if (argc == 3)
    {
      if (_stricmp (argv[1], "-i") == 0)
	{
	  if (strlen (argv[2]) > 0)
	    strcpy_s (sExecPath, argv[2]);

	  vctrlService ();
	}
      else
	{
	  SERVICE_STATUS ss;
	  int service_control_code;

	  SC_HANDLE scmHandle =
	    OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);

	  if (scmHandle == NULL)	// Perform error handling.
	    {
	      WriteLog (sLogFile,
			"(%d)Cannot connect to the Windows Service Control Manager.\n",
			GetLastError ());
	      return 0;
	    }

	  SC_HANDLE scHandle =
	    OpenServiceA (scmHandle, "CUBRIDService", SERVICE_ALL_ACCESS);

	  if (_stricmp (argv[1], CUBRID_UTIL_SERVICE) == 0)
	    {
	      if (_stricmp (argv[2], CUBRID_COMMAND_START) == 0)
		{
		  service_control_code = SERVICE_CONTROL_SERVICE_START;
		}
	      else if (_stricmp (argv[2], CUBRID_COMMAND_STOP) == 0)
		{
		  service_control_code = SERVICE_CONTROL_SERVICE_STOP;
		}
	      else
		{
		  WriteLog (sLogFile, "Invalid Argument.\n");
		  CloseServiceHandle (scHandle);
		  CloseServiceHandle (scmHandle);
		  return 0;
		}
	    }
	  else if (_stricmp (argv[1], CUBRID_UTIL_BROKER) == 0)
	    {
	      if (_stricmp (argv[2], CUBRID_COMMAND_START) == 0)
		{
		  service_control_code = SERVICE_CONTROL_BROKER_START;
		}
	      else if (_stricmp (argv[2], CUBRID_COMMAND_STOP) == 0)
		{
		  service_control_code = SERVICE_CONTROL_BROKER_STOP;
		}
	      else
		{
		  WriteLog (sLogFile, "Invalid Argument.\n");
		  CloseServiceHandle (scHandle);
		  CloseServiceHandle (scmHandle);
		  return 0;
		}
	    }
	  else if (_stricmp (argv[1], CUBRID_UTIL_SHARD) == 0)
	    {
	      if (_stricmp (argv[2], CUBRID_COMMAND_START) == 0)
		{
		  service_control_code = SERVICE_CONTROL_SHARD_START;
		}
	      else if (_stricmp (argv[2], CUBRID_COMMAND_STOP) == 0)
		{
		  service_control_code = SERVICE_CONTROL_SHARD_STOP;
		}
	      else
		{
		  WriteLog (sLogFile, "Invalid Argument.\n");
		  CloseServiceHandle (scHandle);
		  CloseServiceHandle (scmHandle);
		  return 0;
		}
	    }
	  else if (_stricmp (argv[1], CUBRID_UTIL_MANAGER) == 0)
	    {
	      if (_stricmp (argv[2], CUBRID_COMMAND_START) == 0)
		{
		  service_control_code = SERVICE_CONTROL_MANAGER_START;
		}
	      else if (_stricmp (argv[2], CUBRID_COMMAND_STOP) == 0)
		{
		  service_control_code = SERVICE_CONTROL_MANAGER_STOP;
		}
	      else
		{
		  WriteLog (sLogFile, "Invalid Argument.\n");
		  CloseServiceHandle (scHandle);
		  CloseServiceHandle (scmHandle);
		  return 0;
		}
	    }
	  else
	    {
	      WriteLog (sLogFile, "Invalid Argument.\n");
	      CloseServiceHandle (scHandle);
	      CloseServiceHandle (scmHandle);
	      return 0;
	    }

	  ControlService (scHandle, SERVICE_CONTROL_INTERROGATE, &ss);
	  if (ss.dwCurrentState == SERVICE_STOPPED)
	    {
	      LPCTSTR argv[2] =
		{ "CUBRIDService", "--dont-start-cubrid-process" };

	      if (service_control_code == SERVICE_CONTROL_SERVICE_STOP)
		{
		  CloseServiceHandle (scHandle);
		  CloseServiceHandle (scmHandle);
		  return 0;
		}

	      StartService (scHandle, 2, argv);
	      Sleep (2000);

	      do
		{
		  ControlService (scHandle, SERVICE_CONTROL_INTERROGATE, &ss);
		  Sleep (100);
		}
	      while (ss.dwCurrentState == SERVICE_START_PENDING);
	    }

	  // send control code
	  rc = ControlService (scHandle, service_control_code, &ss);
	  if (!rc && ss.dwCurrentState == SERVICE_RUNNING
	      && GetLastError () == ERROR_SERVICE_REQUEST_TIMEOUT)
	    {
	      if (!ControlService
		  (scHandle, SERVICE_CONTROL_INTERROGATE, &ss))
		{
		  WriteLog (sLogFile,
			    "ControlService error. check status manually.\n");
		}
	    }
	  CloseServiceHandle (scHandle);
	  CloseServiceHandle (scmHandle);
	}
    }
  else if (argc == 4)
    {
      if (_stricmp (argv[1], CUBRID_UTIL_SERVER) == 0 ||
	  _stricmp (argv[1], CUBRID_UTIL_BROKER) == 0)
	{
	  SERVICE_STATUS ss;
	  int service_control_code;

	  SC_HANDLE scmHandle =
	    OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);

	  if (scmHandle == NULL)	// Perform error handling.
	    {
	      WriteLog (sLogFile,
			"(%d)Cannot connect to the Windows Service Control Manager.\n",
			GetLastError ());
	      return 0;
	    }

	  SC_HANDLE scHandle =
	    OpenServiceA (scmHandle, "CUBRIDService", SERVICE_ALL_ACCESS);
	  if (_stricmp (argv[1], CUBRID_UTIL_SERVER) == 0 &&
	      _stricmp (argv[2], CUBRID_COMMAND_START) == 0)
	    {
	      service_control_code = SERVICE_CONTROL_SERVER_START;
	    }
	  else if (_stricmp (argv[1], CUBRID_UTIL_SERVER) == 0 &&
		   _stricmp (argv[2], CUBRID_COMMAND_STOP) == 0)
	    {
	      service_control_code = SERVICE_CONTROL_SERVER_STOP;
	    }
	  else if (_stricmp (argv[1], CUBRID_UTIL_BROKER) == 0 &&
		   _stricmp (argv[2], CUBRID_COMMAND_ON) == 0)
	    {
	      service_control_code = SERVICE_CONTROL_BROKER_ON;
	    }
	  else if (_stricmp (argv[1], CUBRID_UTIL_BROKER) == 0 &&
		   _stricmp (argv[2], CUBRID_COMMAND_OFF) == 0)
	    {
	      service_control_code = SERVICE_CONTROL_BROKER_OFF;
	    }
	  else
	    {
	      WriteLog (sLogFile, "Invalid Argument.\n");
	      CloseServiceHandle (scHandle);
	      CloseServiceHandle (scmHandle);
	      return 0;
	    }

	  ControlService (scHandle, SERVICE_CONTROL_INTERROGATE, &ss);
	  if (ss.dwCurrentState == SERVICE_STOPPED)
	    {
	      LPCTSTR argv[2] =
		{ "CUBRIDService", "--dont-start-cubrid-process" };
	      StartService (scHandle, 2, argv);
	      Sleep (2000);

	      do
		{
		  ControlService (scHandle, SERVICE_CONTROL_INTERROGATE, &ss);
		  Sleep (100);
		}
	      while (ss.dwCurrentState == SERVICE_START_PENDING);
	    }

	  char *db_name = TEXT (argv[3]);
	  if (write_string_value_in_registry (HKEY_LOCAL_MACHINE,
					      "SOFTWARE\\CUBRID\\CUBRID",
					      "CUBRID_DBNAME_FOR_SERVICE",
					      db_name) == false)
	    {
	      WriteLog (sLogFile, "write_string_value_in_registry error.\n");

	      CloseServiceHandle (scHandle);
	      CloseServiceHandle (scmHandle);

	      return 0;
	    }

	  // send control code
	  rc = ControlService (scHandle, service_control_code, &ss);
	  if (!rc && ss.dwCurrentState == SERVICE_RUNNING
	      && GetLastError () == ERROR_SERVICE_REQUEST_TIMEOUT)
	    {
	      if (!ControlService
		  (scHandle, SERVICE_CONTROL_INTERROGATE, &ss))
		{
		  WriteLog (sLogFile,
			    "ControlService error. check status manually.\n");
		}
	    }
	  CloseServiceHandle (scHandle);
	  CloseServiceHandle (scmHandle);
	}
    }
  else
    WriteLog (sLogFile, "Invalid Argument.\n");

  return 0;
}