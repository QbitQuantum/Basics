static void
Test(int level)
{
	SQLRETURN result;
	SQLSMALLINT InParam = level;
	SQLSMALLINT OutParam = 1;
	SQLLEN cbReturnCode = 0, cbInParam = 0, cbOutParam = 0;
	SQLLEN cbOutString = SQL_NTS;

	char sql[80];

	printf("ODBC %d nocount %s select %s level %d\n", odbc_use_version3 ? 3 : 2,
	       g_nocount ? "yes" : "no", g_second_select ? "yes" : "no", level);

	ReturnCode = INVALID_RETURN;
	memset(&OutString, 0, sizeof(OutString));

	/* test with SQLExecDirect */
	sprintf(sql, "RAISERROR('An error occurred.', %d, 1)", level);
	result = odbc_command_with_result(odbc_stmt, sql);

	TestResult(result, level, "SQLExecDirect");

	/* test with SQLPrepare/SQLExecute */
	if (!SQL_SUCCEEDED(SQLPrepare(odbc_stmt, T(SP_TEXT), strlen(SP_TEXT)))) {
		fprintf(stderr, "SQLPrepare failure!\n");
		exit(1);
	}

	SQLBindParameter(odbc_stmt, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &ReturnCode, 0, &cbReturnCode);
	SQLBindParameter(odbc_stmt, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &InParam, 0, &cbInParam);
	SQLBindParameter(odbc_stmt, 3, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &OutParam, 0, &cbOutParam);
	strcpy(OutString, "Invalid!");
	SQLBindParameter(odbc_stmt, 4, SQL_PARAM_OUTPUT, SQL_C_CHAR, SQL_VARCHAR, OUTSTRING_LEN, 0, OutString, OUTSTRING_LEN,
			 &cbOutString);

	CHKExecute("S");

	/* first select, check data are returned.
	 * SET statements before does not affect results
	 */
	CheckData("");
	CHKFetch("S");
	CheckData("Here is the first row");

	result = SQLFetch(odbc_stmt);
	if (odbc_use_version3) {
		SQLTCHAR SqlState[6];
		SQLINTEGER NativeError;
		SQLTCHAR MessageText[1000];
		SQLSMALLINT TextLength;
		SQLRETURN expected;
		SQLLEN rows;

		if (result != SQL_NO_DATA)
			ODBC_REPORT_ERROR("SQLFetch should return NO DATA");
		CHKGetDiagRec(SQL_HANDLE_STMT, odbc_stmt, 1, SqlState, &NativeError, MessageText,
				       ODBC_VECTOR_SIZE(MessageText), &TextLength, "No");
		result = SQLMoreResults(odbc_stmt);
		expected = level > 10 ? SQL_ERROR : SQL_SUCCESS_WITH_INFO;
		if (result != expected)
			ODBC_REPORT_ERROR("SQLMoreResults returned unexpected result");
		if (!g_second_select && g_nocount) {
			if (ReturnCode == INVALID_RETURN) {
				result = SQLMoreResults(odbc_stmt);
			} else {
				CheckReturnCode(result, 0);
				ReturnCode = INVALID_RETURN;
				TestResult(result, level, "SQLMoreResults");
				ReturnCode = 0;
			}
		} else {
			TestResult(result, level, "SQLMoreResults");
		}

		/* a recordset with only warnings/errors do not contains rows */
		if (CHKRowCount(&rows, "SE") == SQL_SUCCESS && rows != -1)
			ODBC_REPORT_ERROR("SQLRowCount returned some rows");
	} else {
		/* in ODBC 2 errors/warnings are not handled as different recordset */
		TestResult(result, level, "SQLFetch");
	}

	if (odbc_driver_is_freetds())
		CheckData("");

	if (!g_second_select) {
		SQLLEN rows;

		if (CHKRowCount(&rows, "SE") == SQL_SUCCESS && rows != -1)
			ODBC_REPORT_ERROR("SQLRowCount returned some rows");
		CheckReturnCode(result, g_nocount ? 0 : INVALID_RETURN);

		result = SQLMoreResults(odbc_stmt);
#ifdef ENABLE_DEVELOPING
		if (result != SQL_NO_DATA)
			ODBC_REPORT_ERROR("SQLMoreResults should return NO DATA");

		ODBC_CHECK_ROWS(-2);
#endif
		CheckReturnCode(result, 0);
		return;
	}

	if (!odbc_use_version3 || !g_nocount) {
		/* mssql 2008 return SUCCESS_WITH_INFO with previous error */
		CHKMoreResults("S");
		result = SQL_SUCCESS;
	}

	CheckReturnCode(result, INVALID_RETURN);

	CheckData("");
	if (g_nocount && odbc_use_version3 && g_second_select && level >= 10) {
		if (CHKFetch("SE") == SQL_ERROR) {
			SQLMoreResults(odbc_stmt);
			CHKFetch("S");
		}
	} else {
		CHKFetch("S");
	}
	CheckData("Here is the last row");

	CHKFetch("No");
	CheckData("");

	if (!odbc_use_version3 || g_nocount)
		CheckReturnCode(result, 0);
#ifdef ENABLE_DEVELOPING
	else
		CheckReturnCode(result, INVALID_RETURN);
#endif

	/* FIXME how to handle return in store procedure ??  */
	result = SQLMoreResults(odbc_stmt);
#ifdef ENABLE_DEVELOPING
	if (result != SQL_NO_DATA)
		ODBC_REPORT_ERROR("SQLMoreResults return other data");
#endif

	CheckReturnCode(result, 0);

	CheckData("");
	ODBC_FREE();
}