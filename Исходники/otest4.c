int main(int argc, char **argv)
{
  SQLHENV     hEnv = NULL;
  SQLHDBC     hDbc = NULL;
  SQLHSTMT    hStmt = NULL;
  char*       pConnStr;
  char        pQuery[1000];
  bool        silent = true;

  if (argc != 5) {
    fprintf(stderr, "Usage: %s <ConnString> <pkey range> <ccol range> <rand seed>\n", argv[0]);
    return 1;
  }
  pConnStr = argv[1];
  char *endptr;
  long long numkeys = strtoll(argv[2], &endptr, 10);
  long long rowsperkey = strtoll(argv[3], &endptr, 10);
  int seed = atoi(argv[4]);
  struct drand48_data lcg;
  srand48_r(seed, &lcg);

  // Allocate an environment
  if (!silent)
    fprintf(stderr, "Allocating Handle Enviroment\n");
  if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) == SQL_ERROR)
    {
      fprintf(stderr, "Unable to allocate an environment handle\n");
      exit(-1);
    }

  // Register this as an application that expects 3.x behavior,
  // you must register something if you use AllocHandle
  if (!silent)
    fprintf(stderr, "Setting to ODBC3\n");
  TRYODBC(hEnv,
	  SQL_HANDLE_ENV,
	  SQLSetEnvAttr(hEnv,
			SQL_ATTR_ODBC_VERSION,
			(SQLPOINTER)SQL_OV_ODBC3,
			0));

  // Allocate a connection
  if (!silent)
    fprintf(stderr, "Allocating Handle\n");
  TRYODBC(hEnv,
	  SQL_HANDLE_ENV,
	  SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc));

  // Connect to the driver.  Use the connection string if supplied
  // on the input, otherwise let the driver manager prompt for input.
  if (!silent)
    fprintf(stderr, "Connecting to driver\n");
  TRYODBC(hDbc,
	  SQL_HANDLE_DBC,
	  SQLDriverConnect(hDbc,
			   NULL,
			   pConnStr,
			   SQL_NTS,
			   NULL,
			   0,
			   NULL,
			   SQL_DRIVER_COMPLETE));

  fprintf(stderr, "Connected!\n");

  if (!silent)
    fprintf(stderr, "Allocating statement\n");
  TRYODBC(hDbc,
	  SQL_HANDLE_DBC,
	  SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt));

  RETCODE     RetCode;
  SQLSMALLINT sNumResults;

  // Execute the query
  if (!silent)
    fprintf(stderr, "Executing query\n");
  long long i;
  double rval;
  for (i = 0; i < 100000; i++) {
    drand48_r(&lcg, &rval);
    sprintf(pQuery, "SELECT MAX(col1) FROM otest.test10 WHERE ccol = %lld", (long long)(rval * numkeys));
    RetCode = SQLExecDirect(hStmt, pQuery, SQL_NTS);

    switch(RetCode)
      {
      case SQL_SUCCESS_WITH_INFO:
	{
	  HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
	  // fall through
	}
      case SQL_SUCCESS:
	{
	  // If this is a row-returning query, display
	  // results
	  TRYODBC(hStmt,
		  SQL_HANDLE_STMT,
		  SQLNumResultCols(hStmt,&sNumResults));
	  
	  if (sNumResults > 0)
	    {
	      DisplayResults(hStmt,sNumResults, silent);
	    } 
	  else
	    {
	      SQLLEN cRowCount;
	      
	      TRYODBC(hStmt,
		      SQL_HANDLE_STMT,
		      SQLRowCount(hStmt,&cRowCount));
	      
	      if (cRowCount >= 0)
		{
		  printf("%d %s returned\n",
			 (int)cRowCount,
			 (cRowCount == 1) ? "row" : "rows");
		}
	    }
	  break;
	}
	
      case SQL_ERROR:
	{
	  HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
	  break;
	}
	
      default:
	fprintf(stderr, "Unexpected return code %hd!\n", RetCode);
	
      }
  }

  TRYODBC(hStmt,
	  SQL_HANDLE_STMT,
	  SQLFreeStmt(hStmt, SQL_CLOSE));

 Exit:

  // Free ODBC handles and exit

  if (hStmt)
    {
      SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    }

  if (hDbc)
    {
      SQLDisconnect(hDbc);
      SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    }

  if (hEnv)
    {
      SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    }

  return 0;

}