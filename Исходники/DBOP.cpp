int DBOP::open(WCHAR *DSN,WCHAR *UID,WCHAR *AuthStr){
	retcode = SQLAllocHandle (SQL_HANDLE_ENV, NULL, &henv);
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	//WCHAR* WDSN = new WCHAR[2*sizeof(DSN[0])];
	//WCHAR* WUID = new WCHAR[2*sizeof(UID[0]) ];
	//WCHAR* WAUTHSTR = new WCHAR[sizeof(AuthStr[0]) + 1];

	//MultiByteToWideChar(CP_ACP, 0, DSN, strlen(DSN) + 1, WDSN, sizeof(WDSN[0]));
	//MultiByteToWideChar(CP_ACP, 0, UID, strlen(UID) + 1, WUID, sizeof(WUID[0]));
	//MultiByteToWideChar(CP_ACP, 0, AuthStr, strlen(AuthStr) + 1, WAUTHSTR, sizeof(WAUTHSTR[0]));

	retcode = SQLConnect(hdbc, (SQLWCHAR*)DSN, wcslen((SQLWCHAR*)DSN), (SQLWCHAR*)UID, wcslen((SQLWCHAR*)UID), (SQLWCHAR*)AuthStr, wcslen((SQLWCHAR*)AuthStr));
	if ( (retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO) ) {
		SQLDisconnect(hdbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return 0;
	}
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}