BOOL DatabaseModule_Impl::sqlGetRecentSessionInfoByGId(IN std::string& sId, OUT module::SessionEntity& sessionInfo)
{
	try
	{
		CppSQLite3Statement stmt;
		stmt = m_pSqliteDB->compileStatement(getRecentSessionByIdSql.c_str());
		stmt.bind(1, sId.c_str());

		CppSQLite3Query query = stmt.execQuery();
		if (!query.eof())
		{
			sessionInfo.sessionID = sId;
			sessionInfo.sessionType = query.getIntField(2);
			sessionInfo.updatedTime = query.getIntField(3);
			sessionInfo.latestmsgId = query.getIntField(4);
			sessionInfo.latestMsgContent = query.getStringField(5);
			sessionInfo.latestMsgFromId = query.getStringField(6);
		}
		else
		{
			return FALSE;
		}
	}
	catch (CppSQLite3Exception& sqliteException)
	{
#ifdef _DEBUG
		MessageBoxA(0, sqliteException.errorMessage(), "BD ERROR", MB_OK | MB_ICONHAND);
#endif
		CString csErrMsg = util::stringToCString(sqliteException.errorMessage(), CP_UTF8);
		LOG__(ERR, _T("db failed,error msg:%s"),
			csErrMsg);
		return FALSE;
	}
	catch (...)
	{
		LOG__(ERR, _T("db unknown exception"));
		return FALSE;
	}
	return TRUE;
}