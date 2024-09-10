/* Changed ... Have to implement the same for translators */
void
adddrivers_to_list (ControlRef widget, WindowRef dlg, BOOL addNotify)
{
  wchar_t drvdesc[1024], drvattrs[1024], driver[1024];
  DataBrowserItemID item = DBITEM_ID + 1;
  DataBrowserCallbacks dbCallbacks;
  ThemeDrawingState outState = NULL;
  UInt16 colSize[5] = { 150, 150, 100, 50 , 50};
  void *handle;
  SInt16 outBaseline;
  Point ioBound;
  struct stat _stat;
  SQLSMALLINT len, len1;
  SQLRETURN ret;
  HENV henv, drv_henv;
  HDBC drv_hdbc;
  pSQLGetInfoFunc funcHdl;
  pSQLAllocHandle allocHdl;
  pSQLAllocEnv allocEnvHdl = NULL;
  pSQLAllocConnect allocConnectHdl = NULL;
  pSQLFreeHandle freeHdl;
  pSQLFreeEnv freeEnvHdl;
  pSQLFreeConnect freeConnectHdl;
  char *_drv_u8 = NULL;
  int i;

  if (!widget)
    return;

  GetThemeDrawingState (&outState);

  /* Install an event handler on the component databrowser */
  dbCallbacks.version = kDataBrowserLatestCallbacks;
  InitDataBrowserCallbacks (&dbCallbacks);

  if (addNotify)
    dbCallbacks.u.v1.itemNotificationCallback =
      NewDataBrowserItemNotificationUPP (drivers_notification_item);

  /* On Mac OS X 10.0.x : clientDataCallback */
  dbCallbacks.u.v1.itemDataCallback =
      NewDataBrowserItemDataUPP (drivers_getset_item);
  SetDataBrowserCallbacks (widget, &dbCallbacks);
  /* Begin the draw of the data browser */
  SetDataBrowserTarget (widget, DBITEM_ID);

  /* Make the clean up */
  for (i = 0; i < Drivers_nrows; i++, item++)
    {
      CFRelease (Drivers_array[0][i]);
      Drivers_array[0][i] = NULL;
      CFRelease (Drivers_array[1][i]);
      Drivers_array[1][i] = NULL;
      CFRelease (Drivers_array[2][i]);
      Drivers_array[2][i] = NULL;
      CFRelease (Drivers_array[3][i]);
      Drivers_array[3][i] = NULL;
      CFRelease (Drivers_array[4][i]);
      Drivers_array[4][i] = NULL;
      RemoveDataBrowserItems (widget, DBITEM_ID, 1, &item, DBNAME_ID);
    }

  /* Global Initialization */
  Drivers_nrows = 0;
  item = DBITEM_ID + 1;

  /* Create a HENV to get the list of drivers then */
  ret = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
    {
      _iodbcdm_nativeerrorbox (dlg, henv, SQL_NULL_HANDLE, SQL_NULL_HANDLE);
      goto end;
    }

  /* Set the version ODBC API to use */
  SQLSetEnvAttr (henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3,
      SQL_IS_UINTEGER);

  /* Get the list of drivers */
  ret =
      SQLDriversW (henv, SQL_FETCH_FIRST, drvdesc, sizeof (drvdesc)/sizeof(wchar_t),
        &len, drvattrs, sizeof (drvattrs)/sizeof(wchar_t), &len1);
  if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO && ret != SQL_NO_DATA)
    {
      _iodbcdm_nativeerrorbox (dlg, henv, SQL_NULL_HANDLE, SQL_NULL_HANDLE);
      goto error;
    }

  while (ret != SQL_NO_DATA)
    {
      Drivers_array[0][Drivers_nrows] = convert_wchar_to_CFString(drvdesc);

      /* Get the driver library name */
      SQLSetConfigMode (ODBC_BOTH_DSN);
      SQLGetPrivateProfileStringW (drvdesc, L"Driver", L"", driver,
	  sizeof (driver)/sizeof(wchar_t), L"odbcinst.ini");
      if (driver[0] == L'\0')
	SQLGetPrivateProfileStringW (L"Default", L"Driver", L"", driver,
	    sizeof (driver)/sizeof(wchar_t), L"odbcinst.ini");
      if (driver[0] == L'\0')
	{
	  if (Drivers_array[0][Drivers_nrows])
            {
              CFRelease (Drivers_array[0][Drivers_nrows]);
              Drivers_array[0][Drivers_nrows] = NULL;
            }
	  goto skip;
	}

      Drivers_array[1][Drivers_nrows] = convert_wchar_to_CFString(driver);

      /* Alloc a connection handle */
      drv_hdbc = NULL;
      drv_henv = NULL;

      _drv_u8 = (char *) dm_SQL_WtoU8((SQLWCHAR*)driver, SQL_NTS);
      if (_drv_u8 == NULL)
        goto skip;

      if ((handle = DLL_OPEN(_drv_u8)) != NULL)
        {
          if ((allocHdl = (pSQLAllocHandle)DLL_PROC(handle, "SQLAllocHandle")) != NULL)
            {
              ret = allocHdl(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &drv_henv);
	      if (ret == SQL_ERROR) goto nodriverver;
              ret = allocHdl(SQL_HANDLE_DBC, drv_henv, &drv_hdbc);
	      if (ret == SQL_ERROR) goto nodriverver;
            }
          else
            {
              if ((allocEnvHdl = (pSQLAllocEnv)DLL_PROC(handle, "SQLAllocEnv")) != NULL)
                {
                  ret = allocEnvHdl(&drv_henv);
	          if (ret == SQL_ERROR) goto nodriverver;
                }
              else goto nodriverver;

              if ((allocConnectHdl = (pSQLAllocConnect)DLL_PROC(handle, "SQLAllocConnect")) != NULL)
                {
                  ret = allocConnectHdl(drv_henv, &drv_hdbc);
	          if (ret == SQL_ERROR) goto nodriverver;
                }
              else goto nodriverver;
            }

	  /*
	   *  Use SQLGetInfoA for Unicode drivers
	   *  and SQLGetInfo  for ANSI drivers
	   */
          funcHdl = (pSQLGetInfoFunc)DLL_PROC(handle, "SQLGetInfoA");
	  if (!funcHdl)
	      funcHdl = (pSQLGetInfoFunc)DLL_PROC(handle, "SQLGetInfo");

	  if (funcHdl)
            {
              /* Retrieve some informations */
              ret = funcHdl (drv_hdbc, SQL_DRIVER_VER, drvattrs, sizeof(drvattrs), &len);
              if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
                {
		  char *p = drvattrs;

                  /* Find the description if one provided */
		  for (; *p ; p++) 
		    {
		      if (*p == ' ')
		        {
			  *p++ = '\0';
			  break;
			}
		    }

		  /*
		   * Store Version
		   */
                  Drivers_array[2][Drivers_nrows] = CFStringCreateWithCString(NULL, (char *)drvattrs, kCFStringEncodingUTF8);
                }
              else goto nodriverver;
            }
	  else if ((funcHdl = (pSQLGetInfoFunc)DLL_PROC(handle, "SQLGetInfoW")) != NULL) 
	    {
              /* Retrieve some informations */
              ret = funcHdl (drv_hdbc, SQL_DRIVER_VER, drvattrs, sizeof(drvattrs), &len);
              if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
                {
		  wchar_t *p = drvattrs;

                  /* Find the description if one provided */
		  for (; *p ; p++) 
		    {
		      if (*p == L' ')
		        {
			  *p++ = L'\0';
			  break;
			}
		    }

		  /*
		   * Store Version
		   */
                  Drivers_array[2][Drivers_nrows] = convert_wchar_to_CFString(drvattrs);
                }
              else goto nodriverver;
	        
	    }
          else goto nodriverver;
        }
      else
        {
nodriverver:
          Drivers_array[2][Drivers_nrows] = CFStringCreateWithCString(NULL,
            "##.##", kCFStringEncodingUTF8);
        }

      if(drv_hdbc || drv_henv)
        {
          if(allocConnectHdl &&
            (freeConnectHdl = (pSQLFreeConnect)DLL_PROC(handle, "SQLFreeConnect")) != NULL)
            { freeConnectHdl(drv_hdbc); drv_hdbc = NULL; }

          if(allocEnvHdl &&
            (freeEnvHdl = (pSQLFreeEnv)DLL_PROC(handle, "SQLFreeEnv")) != NULL)
            { freeEnvHdl(drv_henv); drv_henv = NULL; }
        }

      if ((drv_hdbc || drv_henv) &&
         (freeHdl = (pSQLFreeHandle)DLL_PROC(handle, "SQLFreeHandle")) != NULL)
        {
          if(drv_hdbc) freeHdl(SQL_HANDLE_DBC, drv_hdbc);
          if(drv_henv) freeHdl(SQL_HANDLE_ENV, drv_henv);
        }

      DLL_CLOSE(handle);

      /* Get the size and date of the driver */
      if (!stat (_drv_u8, &_stat))
	{
          CFStringRef strRef;
	  struct tm drivertime;
	  char buf[100];

          Drivers_array[3][Drivers_nrows] = 
            CFStringCreateWithFormat(NULL, NULL,
              strRef = CFStringCreateWithCString(NULL, "%d Kb", kCFStringEncodingUTF8),
              (int) (_stat.st_size / 1024));
	  CFRelease(strRef);

	  localtime_r (&_stat.st_mtime, &drivertime);
	  strftime (buf, sizeof (buf), "%c", &drivertime);
	  Drivers_array[4][Drivers_nrows] = CFStringCreateWithCString(NULL, 
	  	buf, kCFStringEncodingUTF8);
        }
      else
        {
	    Drivers_array[3][Drivers_nrows] = CFStringCreateWithCString(NULL,
	      "-", kCFStringEncodingUTF8);
	    Drivers_array[4][Drivers_nrows] = CFStringCreateWithCString(NULL,
	      "-", kCFStringEncodingUTF8);
	}

      for(i = 0 ; i < 5 ; i++)
        {
          GetThemeTextDimensions (Drivers_array[i][Drivers_nrows], kThemeSystemFont,
            kThemeStateActive, false, &ioBound, &outBaseline);
          if(colSize[i] < ioBound.h) colSize[i] = ioBound.h;
        }

      AddDataBrowserItems (widget, DBITEM_ID, 1, &item, DBNAME_ID);
      item++;
      Drivers_nrows++;

      /* Process next one */
    skip:
      MEM_FREE (_drv_u8);
      _drv_u8 = NULL;

      ret = SQLDriversW (henv, SQL_FETCH_NEXT, drvdesc,
	  sizeof (drvdesc)/sizeof(wchar_t), &len, drvattrs,
	  sizeof (drvattrs)/sizeof(wchar_t), &len1);
      if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO && ret != SQL_NO_DATA)
	{
	  _iodbcdm_nativeerrorbox (dlg, henv, SQL_NULL_HANDLE,
	      SQL_NULL_HANDLE);
	  goto error;
	}
    }

error:
  /* Clean all that */
  SQLFreeHandle (SQL_HANDLE_ENV, henv);

end:
  ActivateControl (widget);
  /* Resize the columns to have a good look */
  SetDataBrowserTableViewNamedColumnWidth (widget, DBNAME_ID, colSize[0] + 20);
  SetDataBrowserTableViewNamedColumnWidth (widget, DBFILE_ID, colSize[1] + 20);
  SetDataBrowserTableViewNamedColumnWidth (widget, DBVERSION_ID, colSize[2] + 20);
  SetDataBrowserTableViewNamedColumnWidth (widget, DBSIZE_ID, colSize[3] + 20);
  SetDataBrowserTableViewNamedColumnWidth (widget, DBDATE_ID, colSize[4] + 20);
  DrawOneControl (widget);
  /* Remove the DataBrowser callback */
  SetDataBrowserCallbacks (NULL, &dbCallbacks);
  if(outState) DisposeThemeDrawingState (outState);
}