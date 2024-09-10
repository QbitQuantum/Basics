bool DoDirect(HSTMT	lpStmt, SQLCHAR* input)
{
	RETCODE		RetCode;
	SQLSMALLINT	sNumResults;

	RetCode = SQLExecDirect(lpStmt, (SQLCHAR*) input, SQL_NTS);

	switch (RetCode)
	{
	case	SQL_SUCCESS_WITH_INFO:
	{
		HandleError(lpStmt, SQL_HANDLE_STMT, RetCode);
		// fall through
	}
	case	SQL_SUCCESS:
	{
		// If this is a row-returning query, display
		// results
		TRYODBC(lpStmt,
		        SQL_HANDLE_STMT,
		        SQLNumResultCols(lpStmt, &sNumResults));

		if (sNumResults > 0)
		{
			DisplayResults(lpStmt, sNumResults);
		} else
		{
			SQLLEN		siRowCount;

			TRYODBC(lpStmt,
			        SQL_HANDLE_STMT,
			        SQLRowCount(lpStmt, &siRowCount));

			if (siRowCount >= 0)
			{
				_tprintf(TEXT("%ld %s affected\n"),
				         static_cast<long>(siRowCount),
				         siRowCount == 1 ? TEXT("row") : TEXT("rows"));
			}
		}
		break;
	}

	case	SQL_ERROR:
	{
		_tprintf(TEXT("going to call handle error\n"));
		HandleError(lpStmt, SQL_HANDLE_STMT, RetCode);
		break;
	}

	default:
		fprintf(stderr, "Unexpected return code %d!\n", RetCode);
	}

	return true;
Exit:
	return false;
}