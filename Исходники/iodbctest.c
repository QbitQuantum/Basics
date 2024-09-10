int
ODBC_Connect (char *connStr)
{
  short buflen;
  SQLCHAR dataSource[1024];
  SQLTCHAR dsn[33];
  SQLTCHAR desc[255];
  SQLTCHAR driverInfo[255];
  SQLSMALLINT len1, len2;
  int status;
#ifdef UNICODE
  SQLWCHAR wdataSource[1024];
#endif

#if (ODBCVER < 0x0300)
  if (SQLAllocEnv (&henv) != SQL_SUCCESS)
    return -1;

  if (SQLAllocConnect (henv, &hdbc) != SQL_SUCCESS)
    return -1;
#else
  if (SQLAllocHandle (SQL_HANDLE_ENV, NULL, &henv) != SQL_SUCCESS)
    return -1;

  SQLSetEnvAttr (henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3,
      SQL_IS_UINTEGER);

  if (SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc) != SQL_SUCCESS)
    return -1;
#endif


  /*
   *  Set the application name
   */
  SQLSetConnectOption (hdbc, SQL_APPLICATION_NAME,
	(SQLULEN) TEXT ("odbctest"));


  /*
   *  Show the version number of the driver manager
   */
  status = SQLGetInfo (hdbc, SQL_DM_VER,
      driverInfo, sizeof (driverInfo), &len1);
  if (status == SQL_SUCCESS)
    {
#ifdef UNICODE
      printf ("Driver Manager: %S\n", driverInfo);
#else
      printf ("Driver Manager: %s\n", driverInfo);
#endif
    }


  /*
   *  Either use the connect string provided on the command line or
   *  ask for one. If an empty string or a ? is given, show a nice
   *  list of options
   */
  if (connStr && *connStr)
    strcpy ((char *) dataSource, connStr);
  else
    while (1)
      {
	/*
	 *  Ask for the connect string
	 */
	printf ("\nEnter ODBC connect string (? shows list): ");
	if (fgets ((char *) dataSource, sizeof (dataSource), stdin) == NULL)
	  return 1;

	/*
	 *  Remove trailing '\n'
	 */
	dataSource[strlen ((char *) dataSource) - 1] = '\0';

	/*
	 * Check if the user wants to quit
	 */
	if (!strcmp ((char *)dataSource, "quit") || !strcmp ((char *)dataSource, "exit"))
	  return -1;

	/*
	 *  If the user entered something other than a ?
	 *  break out of the while loop
	 */
	if (*dataSource && *dataSource != '?')
	  break;


	/*
	 *  Print headers
	 */
	fprintf (stderr, "\n%-32s | %-40s\n", "DSN", "Driver");
	fprintf (stderr,
	    "------------------------------------------------------------------------------\n");

	/*
	 *  Goto the first record
	 */
	if (SQLDataSources (henv, SQL_FETCH_FIRST,
		dsn, NUMTCHAR (dsn), &len1,
		desc, NUMTCHAR (desc), &len2) != SQL_SUCCESS)
	  continue;

	/*
	 *  Show all records
	 */
	do
	  {
#ifdef UNICODE
	    fprintf (stderr, "%-32S | %-40S\n", dsn, desc);
#else
	    fprintf (stderr, "%-32s | %-40s\n", dsn, desc);
#endif
	  }
	while (SQLDataSources (henv, SQL_FETCH_NEXT,
		dsn, NUMTCHAR (dsn), &len1,
		desc, NUMTCHAR (desc), &len2) == SQL_SUCCESS);
      }

#ifdef UNICODE
  strcpy_A2W (wdataSource, (char *) dataSource);
  status = SQLDriverConnectW (hdbc, 0, (SQLWCHAR *) wdataSource, SQL_NTS,
      (SQLWCHAR *) outdsn, NUMTCHAR (outdsn), &buflen, SQL_DRIVER_COMPLETE);
  if (status != SQL_SUCCESS)
    ODBC_Errors ("SQLDriverConnectW");
#else
  status = SQLDriverConnect (hdbc, 0, (SQLCHAR *) dataSource, SQL_NTS,
      (SQLCHAR *) outdsn, NUMTCHAR (outdsn), &buflen, SQL_DRIVER_COMPLETE);
  if (status != SQL_SUCCESS)
    ODBC_Errors ("SQLDriverConnect");
#endif

  if (status != SQL_SUCCESS && status != SQL_SUCCESS_WITH_INFO)
    return -1;

  connected = 1;


  /*
   *  Print out the version number and the name of the connected driver
   */
  status = SQLGetInfo (hdbc, SQL_DRIVER_VER,
      driverInfo, NUMTCHAR (driverInfo), &len1);
  if (status == SQL_SUCCESS)
    {
#ifdef UNICODE
      printf ("Driver: %S", driverInfo);
#else
      printf ("Driver: %s", driverInfo);
#endif

      status = SQLGetInfo (hdbc, SQL_DRIVER_NAME,
	  driverInfo, NUMTCHAR (driverInfo), &len1);
      if (status == SQL_SUCCESS)
	{
#ifdef UNICODE
	  printf (" (%S)", driverInfo);
#else
	  printf (" (%s)", driverInfo);
#endif
	}
      printf ("\n");
    }


  /*
   *  Show the list of supported functions in trace log
   */
#if (ODBCVER < 0x0300)
  {
     SQLUSMALLINT exists[100];

     SQLGetFunctions (hdbc, SQL_API_ALL_FUNCTIONS, exists);
  }
#else
  {
     SQLUSMALLINT exists[SQL_API_ODBC3_ALL_FUNCTIONS_SIZE];

     SQLGetFunctions (hdbc, SQL_API_ODBC3_ALL_FUNCTIONS, exists);
  }
#endif



  /*
   *  Allocate statement handle
   */
#if (ODBCVER < 0x0300)
  if (SQLAllocStmt (hdbc, &hstmt) != SQL_SUCCESS)
    return -1;
#else
  if (SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt) != SQL_SUCCESS)
    return -1;
#endif

  return 0;
}