BOOL INSTAPI
ConfigDriver (
    HWND	  hwndParent,
    WORD	  fRequest,
    LPCSTR	  lpszDriver,
    LPCSTR	  lpszArgs,
    LPSTR	  lpszMsg,
    WORD	  cbMsgMax,
    WORD	* pcbMsgOut)
{
  char *curr, *cour;
  char driverread[4096] = { 0 };
  BOOL retcode = FALSE;
  UWORD confMode = ODBC_USER_DSN;

  /* Map the request User/System */
  if (fRequest < ODBC_INSTALL_DRIVER || fRequest > ODBC_CONFIG_DRIVER_MAX)
    {
      SQLPostInstallerError (ODBC_ERROR_INVALID_REQUEST_TYPE, NULL);
      goto done;
    }

  if (!lpszDriver || !STRLEN (lpszDriver))
    {
      SQLPostInstallerError (ODBC_ERROR_INVALID_NAME, NULL);
      goto done;
    }

  /* Retrieve the config mode */
  SQLGetConfigMode (&confMode);

  /* Treat corresponding to the request */
  switch (fRequest)
    {
    case ODBC_INSTALL_DRIVER:
      /* Check if the DRIVER with this name already exists */
      SQLSetConfigMode (confMode);
#ifdef WIN32
      if (hwndParent
	  && SQLGetPrivateProfileString ("ODBC 32 bit Drivers", lpszDriver,
	      "", driverread, sizeof (driverread), "odbcinst.ini")
	  && !create_confirm (hwndParent, NULL,
	      "Are you sure you want to overwrite this driver ?"))
#else
#  ifdef _MACX
      if (hwndParent
	  && SQLGetPrivateProfileString ("ODBC Drivers", lpszDriver, "",
	      driverread, sizeof (driverread), "odbcinst.ini")
	  && !create_confirm (hwndParent, NULL,
	      "Are you sure you want to overwrite this driver ?"))
#  else
      if (hwndParent
	  && SQLGetPrivateProfileString ("ODBC Drivers", lpszDriver, "",
	      driverread, sizeof (driverread), "odbcinst.ini")
	  && !create_confirm (hwndParent, NULL,
	      "Are you sure you want to overwrite this driver ?"))
#  endif
#endif
	{
	  SQLPostInstallerError (ODBC_ERROR_DRIVER_SPECIFIC,
	      "Driver already installed previously.");
	  goto done;
	}

      /* Add the Driver to the ODBC Drivers */
      SQLSetConfigMode (confMode);
      if (!SQLInstallDriverEx (lpszArgs, NULL, driverread,
	      sizeof (driverread), NULL, ODBC_INSTALL_COMPLETE, NULL))
	{
	  SQLPostInstallerError (ODBC_ERROR_DRIVER_SPECIFIC,
	      "Could not add the driver information.");
	  goto done;
	}

      break;

    case ODBC_CONFIG_DRIVER:
      if (!lpszArgs || !STRLEN (lpszArgs))
	{
	  SQLPostInstallerError (ODBC_ERROR_DRIVER_SPECIFIC,
	      "No enough parameters for configururation.");
	  goto done;
	}

      /* Add each keyword and values */
      for (curr = (LPSTR) lpszArgs; *curr; curr += (STRLEN (curr) + 1))
	{
	  STRCPY (driverread, curr);
	  cour = strchr (driverread, '=');
	  if (cour)
	    *cour = 0;
	  SQLSetConfigMode (confMode);
	  if (!SQLWritePrivateProfileString (lpszDriver, driverread, (cour
		      && STRLEN (cour + 1)) ? cour + 1 : NULL,
		  "odbcinst.ini"))
	    goto done;
	}
      break;

    case ODBC_REMOVE_DRIVER:
      /* Remove the Driver to the ODBC Drivers */
      SQLSetConfigMode (confMode);
      if (!SQLRemoveDriver (lpszDriver, TRUE, NULL))
	{
	  SQLPostInstallerError (ODBC_ERROR_DRIVER_SPECIFIC,
	      "Could not remove driver information.");
	  goto done;
	}
      break;

    default:
      SQLPostInstallerError (ODBC_ERROR_REQUEST_FAILED, NULL);
      goto done;
    };

quit:
  retcode = TRUE;

done:
  if (pcbMsgOut)
    *pcbMsgOut = 0;
  return retcode;
}