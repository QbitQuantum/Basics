// ============================================================================
// ==============================================================================
std::vector<std::vector<std::string> > CMySQLMgr::QueryFields(const char *pszQueryFields, const char *pszTable)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	std::vector<std::vector<std::string> > vecRet;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (NULL == pszQueryFields) {
		return vecRet;
	}

	//~~~~~~~~~~~~~~~~~~~~~~
	char szFields[MAX_STRING];
	//~~~~~~~~~~~~~~~~~~~~~~

	strncpy_s(szFields, pszQueryFields, sizeof(szFields));
	MyTrim(szFields);

	//~~~~~~~~~~~~~~~~~~~~~~~~
	char szQueryCmd[MAX_STRING];
	//~~~~~~~~~~~~~~~~~~~~~~~~

	if (szFields[0] == 34) {
		_snprintf_s(szQueryCmd, sizeof(szQueryCmd), "select %s from %s ", pszQueryFields, pszTable);
		return this->Query(szQueryCmd);
	}

	//~~~~~~~~~~~~~~~~~~~
	char szKey[MAX_STRING];
	//~~~~~~~~~~~~~~~~~~~

	strncpy_s(szKey, pszQueryFields, sizeof(szKey));

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	char *pszPos = strstr(szKey, ",");
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (pszPos) {
		*pszPos = 0;
	}

	_snprintf_s(szQueryCmd, sizeof(szQueryCmd), "select %s from %s group by %s having COUNT(%s) > 1 ", pszQueryFields,
				pszTable, szKey, szKey);

	vecRet = this->Query(szQueryCmd);

	if (!vecRet.empty()) {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		std::vector<std::vector<std::string> >::const_iterator it = vecRet.begin();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		for (; it != vecRet.end(); ++it) {
			if (!it->empty()) {
				LogInfoIn("		警告: 数据库表 %s 含有两行以上 %s = %s 的数据", pszTable, szKey, it->front().c_str());
			}
		}
	}

	_snprintf_s(szQueryCmd, sizeof(szQueryCmd), "select %s from %s group by %s having COUNT(%s) = 1 ", pszQueryFields,
				pszTable, szKey, szKey);

	return this->Query(szQueryCmd);
}