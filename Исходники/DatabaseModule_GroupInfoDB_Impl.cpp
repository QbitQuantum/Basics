BOOL DatabaseModule_Impl::sqlUpdateGroupInfoEntity(std::string& sId, IN const module::GroupInfoEntity& groupInfo)
{
	try
	{
		//"update groupinfo set name=?,desc=?,avatarUrl=?,creatorId=?,type=?,version=?,lastUpdateTime=?,shieldStatus=?,memberlist=? where groupId=?";
		CppSQLite3Statement stmt = m_pSqliteDB->compileStatement(updateGroupInfoBySIdSql.c_str());
		stmt.bind(1, util::cStringToString(groupInfo.csName).c_str());
		stmt.bind(2, util::cStringToString(groupInfo.desc).c_str());
		stmt.bind(3, groupInfo.avatarUrl.c_str());
		stmt.bind(4, groupInfo.creatorId.c_str());
		stmt.bind(5, int(groupInfo.type));
		stmt.bind(6, int(groupInfo.version));
		stmt.bind(7, int(groupInfo.groupUpdated));
		stmt.bind(8, int(groupInfo.shieldStatus));
		std::string& strJson = _makeJsonForGroupMembers(groupInfo.groupMemeberList);
		stmt.bind(9, strJson.c_str());
		stmt.bind(9, groupInfo.gId.c_str());
		int countUpdate = stmt.execDML();
		if (0 == countUpdate)
		{
			LOG__(ERR, _T("db update failed:%s"), util::stringToCString(groupInfo.gId));
			return FALSE;
		}
	}
	catch (CppSQLite3Exception& sqliteException)
	{
#ifdef _DEBUG
		MessageBoxA(0, sqliteException.errorMessage(), "BD ERROR", MB_OK | MB_ICONHAND);
#endif
		CString csErrMsg = util::stringToCString(sqliteException.errorMessage(), CP_UTF8);
		LOG__(ERR, _T("db failed,error msg:%s"), csErrMsg);
		return FALSE;
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}