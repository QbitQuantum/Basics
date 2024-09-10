bool OdbcCommand::Execute(const tstring & szSQL)
{
	if (!Open())
		return false;

#ifdef _DEBUG
	OutputDebugString((szSQL + _T("\n")).c_str());
#endif

	if (!BindParameters())
		return false;

	if (!SQL_SUCCEEDED(SQLExecDirect(m_hStmt, (SQLTCHAR *)szSQL.c_str(), szSQL.length())))
	{
		if (m_odbcConnection != NULL)
			m_szError = m_odbcConnection->ReportSQLError(SQL_HANDLE_STMT, m_hStmt, (TCHAR *)szSQL.c_str(), _T("Failed to execute statement."));
		else
			m_szError = OdbcConnection::GetSQLError(SQL_HANDLE_STMT, m_hStmt);

		Close();
		return false;
	}

	if (!MoveNext())
		MoveNextSet();

	return true;
}