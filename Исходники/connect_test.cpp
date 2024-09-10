// Main Program
int main (int argc, char **argv)
{
	SQLCHAR		*dsnName;
	SQLCHAR		*user;
	SQLCHAR		*password;
	SQLRETURN	returnCode;
	bool		testPassed = true;
	SQLCHAR		InConnStr[MAX_CONNECT_STRING];
	SQLCHAR		OutConnStr[MAX_CONNECT_STRING];
	SQLSMALLINT	ConnStrLength;
	int c, errflag = 0;
	
	optarg = NULL;
	if (argc != 7)
		errflag++;

	while (!errflag && (c = getopt(argc, argv, ARGS)) != -1)
		switch (c) {
			case 'd':
				dsnName = (SQLCHAR*)optarg;	
				break;
			case 'u':
				user = (SQLCHAR*)optarg;
				break;
			case 'p':
				password = (SQLCHAR*)optarg;
				break;
			default :
				errflag++;
		}
	if (errflag) {
		printf("Command line error.\n");
		printf("Usage: %s [-d <datasource>] [-u <userid>] [-p <password>]\n", argv[0] );
		return FALSE;
	}

	// Initialize handles to NULL
	henv = SQL_NULL_HANDLE;
	hstmt = SQL_NULL_HANDLE;
	hdbc = SQL_NULL_HANDLE;

	// Allocate Environment Handle
	returnCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv)",returnCode);

	// Set ODBC version to 3.0
	returnCode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0)",returnCode,false);

	// Allocate Connection handle
	returnCode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc)", returnCode);

	//Connect to the database
	sprintf((char*)InConnStr,"DSN=%s;UID=%s;PWD=%s;%c",(char*)dsnName, (char*)user, (char*)password,'\0');
	printf("Using Connect String: %s\n", InConnStr);
	returnCode = SQLDriverConnect(hdbc,hWnd,InConnStr,SQL_NTS,OutConnStr,sizeof(OutConnStr),&ConnStrLength,SQL_DRIVER_NOPROMPT);
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLDriverConnect",returnCode);

	//Allocate Statement handle
	returnCode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt)", returnCode);

	//Free Statement handle
	returnCode = SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLFreeHandle(SQL_HANDLE_STMT, hstmt)", returnCode);
	hstmt = SQL_NULL_HANDLE;

	//Disconnect
	returnCode = SQLDisconnect(hdbc);
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLDisconnect(hdbc)", returnCode);

	//Free Connection handle
	returnCode = SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLFreeHandle(SQL_HANDLE_DBC, hdbc)", returnCode);
	hdbc = SQL_NULL_HANDLE;

	//Free Environment handle
	returnCode = SQLFreeHandle(SQL_HANDLE_ENV, henv);
	if(returnCode != SQL_SUCCESS)
		LogDiagnostics("SQLFreeHandle(SQL_HANDLE_ENV, henv)", returnCode);
	henv = SQL_NULL_HANDLE;

	printf("\nConnect Test Passed...\n");
	exit(EXIT_SUCCESS);
}