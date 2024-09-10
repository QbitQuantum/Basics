DWORD WINAPI thread_func (LPVOID param)
{
    thread_t *t = (thread_t *)param;
    char szStrTo[512];
    RETCODE rc;
    SDWORD cbRet = SQL_DATA_AT_EXEC,
	cb1 = SQL_NULL_DATA,
	cb2 = SQL_NULL_DATA,
	cb3 = SQL_NULL_DATA,
	cb4 = SQL_NULL_DATA,
	cb5 = SQL_NULL_DATA,
	cb6 = SQL_NULL_DATA,
	cb7 = SQL_NULL_DATA,
	cb8 = SQL_NULL_DATA;
    szStrTo[0] = 0;
    ::WideCharToMultiByte (CP_ACP, 0, t->bStrTo, -1, szStrTo, sizeof (szStrTo), NULL, NULL);
    CDBConnection *conn = _ppool->getConnection();
//    _Module.LogEvent ("After conn");
//    _Module.LogEvent ("From: %s, To: %s, CC: %s, BCC: %s, Subject: %s, SentOn :%s", 
//	szStrFrom, szStrTo, szStrCC, szStrBCC, szStrSubj, szStrSent);
    long ofs = 0;
    char szTo[512];
    while (-1 != (ofs = GetNextID (szStrTo, ofs, szTo)))
    {
    cb1 = SQL_NULL_DATA;
    HSTMT hstmt = SQL_NULL_HSTMT;
    try 
    {
	int reconnect_count;
again:
	reconnect_count = 0;
	hstmt = SQL_NULL_HSTMT;
	if (SQL_SUCCESS != SQLAllocStmt (conn->hdbc, &hstmt))
	    throw _T ("SQLAllocStmt error");

//	SQLSetStmtOption (hstmt, SQL_QUERY_TIMEOUT, 10);
	SQLSetParam (hstmt, 1, SQL_C_CHAR, SQL_CHAR, 0, 0, szTo, szTo[0] ? NULL : &cb1);
	SQLSetParam (hstmt, 2, SQL_C_WCHAR, SQL_CHAR, 0, 0, t->bStrSubj, t->bStrSubj[0] ? NULL : &cb2);
	SQLSetParam (hstmt, 3, SQL_C_WCHAR, SQL_CHAR, 0, 0, t->bStrCC, t->bStrCC[0] ? NULL : &cb3);
	SQLSetParam (hstmt, 4, SQL_C_WCHAR, SQL_CHAR, 0, 0, t->bStrBCC, t->bStrBCC[0] ? NULL : &cb4);
	SQLSetParam (hstmt, 5, SQL_C_WCHAR, SQL_CHAR, 0, 0, t->bStrSent, t->bStrSent[0] ? NULL : &cb5);
	SQLSetParam (hstmt, 6, SQL_C_WCHAR, SQL_CHAR, 0, 0, t->bStrTo, t->bStrTo[0] ? NULL : &cb6);
	SQLSetParam (hstmt, 7, SQL_C_WCHAR, SQL_CHAR, 0, 0, t->bStrFrom, t->bStrFrom[0] ? NULL : &cb7);
	SQLSetParam (hstmt, 8, SQL_C_WCHAR, SQL_LONGVARCHAR, 0, 0, t->bStrContent, t->bStrContent[0] ? NULL : &cb8);
//        _Module.LogEvent ("After setparam");
	rc = SQLExecDirect (hstmt, 
	    (SQLCHAR *)"BARE_NEW_MAIL (?, ?, ?, ?, ?, ?, ?, ?)", SQL_NTS);
	if (rc != SQL_SUCCESS && !reconnect_count)
	{
	    conn->ReportODBCError (hstmt, "Retry SQLExec error");
	    _Module.LogEvent ("Reconnecting ...");
	    reconnect_count = 1;
	    SQLFreeStmt (hstmt, SQL_DROP);
	    hstmt = SQL_NULL_HSTMT;
	    delete conn;
	    conn = new CDBConnection ();
	    goto again;
	}
	else if (rc != SQL_SUCCESS)
	{
	    throw _T("SQLExec Error");
	}


	SQLFreeStmt (hstmt, SQL_DROP);
//	SQLFreeStmt (hstmt, SQL_RESET_PARAMS);
	_Module.LogEvent ("Message (%ld chars) from %s routed to %s", wcslen (t->bStrContent), (char *)(bstr_t)t->bStrFrom, (char *)(bstr_t)t->bStrTo);
    }
    catch (TCHAR *ch)
    {
	int deadlock = conn->ReportODBCError (hstmt, ch);
//	SQLFreeStmt (hstmt, SQL_RESET_PARAMS);
	if (deadlock)
	    goto again;
	_ppool->releaseConnection(conn);
	delete t;
    }
    }
    _ppool->releaseConnection(conn);
    delete t;
    return 0;
}