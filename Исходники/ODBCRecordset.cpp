bool CODBCRecordset::InsertBinary(const CString& strQuery, const u8* pData, int nSize)
{
	if (!m_pDatabase->IsOpen())
	{
		assert(0);
		return false;
	}

	if ((0 == strQuery.GetLength()) || 0 == pData)
		return false;

	if (8000 < nSize)
		return false;

	HSTMT		hStmt;
	SQLTCHAR*	pWriteBuff;
	SQLLEN  ind = SQL_DATA_AT_EXEC;

	if (SQL_ERROR == SQLAllocHandle(SQL_HANDLE_STMT, m_pDatabase->GetConn(), &hStmt))
	{
		return false;
	}

	if (SQL_ERROR == SQLPrepare(hStmt, SQLData(strQuery), SQL_NTS))
	{
		return false;
	}

	if (SQL_ERROR == SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT,
		SQL_C_BINARY, SQL_BINARY,
		nSize, 0, (SQLPOINTER)pData, nSize, &ind))
	{
		return false;
	}

	if (SQL_ERROR == SQLExecute(hStmt))
	{
		return false;
	}

	if (SQL_ERROR == SQLParamData(hStmt, (SQLPOINTER*)&pWriteBuff))
	{
		return false;
	}

	int			nWrSize;
	int			len;
	SQLRETURN	sqlRet;

	for (nWrSize = 0; nWrSize < nSize; nWrSize += BINARY_CHUNK_SIZE, pWriteBuff += BINARY_CHUNK_SIZE)
	{
		if (nWrSize + BINARY_CHUNK_SIZE < nSize)
			len = BINARY_CHUNK_SIZE;
		else
			len = nSize - nWrSize;

		sqlRet = SQLPutData(hStmt, (SQLPOINTER)pWriteBuff, len);
	}

	if (SQL_ERROR == sqlRet)
	{
		return false;
	}

	if (SQL_ERROR == SQLParamData(hStmt, (SQLPOINTER*)&pWriteBuff))
	{
		return false;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	return true;
}