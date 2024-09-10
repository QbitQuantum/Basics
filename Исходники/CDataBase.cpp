bool CDataBase::Query(const char *query, CVarDefMap &mapQueryResult)
{
	ADDTOCALLSTACK("CDataBase::Query");
	mapQueryResult.Empty();
	mapQueryResult.SetNumNew("NUMROWS", 0);

	if ( !m_connected )
		return false;

	// Connection can only handle one query at a time, so lock the thread until the query finishes
	SimpleThreadLock lock(m_connectionMutex);

	int resultCode = mysql_query(m_socket, query);
	if ( resultCode == 0 )
	{
		MYSQL_RES *result = mysql_store_result(m_socket);
		if ( !result )
			return false;

		unsigned int num_fields = mysql_num_fields(result);
		char key[64];
		if ( num_fields > COUNTOF(key) )
		{
			// This check is not really needed, MySQL client should be able to handle the same columns amount of MySQL server (4096).
			// But since this value is too big and create an 4096 char array at -every- query call is not performance-friendly, maybe
			// it's better just use an smaller array to prioritize performance.
			g_Log.EventError("MySQL query returned too many columns [Max: %" FMTSIZE_T " / Cmd: \"%s\"]\n", COUNTOF(key), query);
			mysql_free_result(result);
			return false;
		}

		MYSQL_FIELD *fields = mysql_fetch_fields(result);
		mapQueryResult.SetNum("NUMROWS", mysql_num_rows(result));
		mapQueryResult.SetNum("NUMCOLS", num_fields);

		int rownum = 0;
		char **row = NULL;
		char *pszKey = Str_GetTemp();
		char *pszVal = NULL;
		while ( (row = mysql_fetch_row(result)) != NULL )
		{
			for ( unsigned int i = 0; i < num_fields; i++ )
			{
				pszVal = row[i];
				if ( !rownum )
				{
					mapQueryResult.SetStr(ITOA(i, key, 10), true, pszVal);
					mapQueryResult.SetStr(fields[i].name, true, pszVal);
				}

				sprintf(pszKey, "%d.%u", rownum, i);
				mapQueryResult.SetStr(pszKey, true, pszVal);
				sprintf(pszKey, "%d.%s", rownum, fields[i].name);
				mapQueryResult.SetStr(pszKey, true, pszVal);
			}
			rownum++;
		}

		mysql_free_result(result);
		return true;
	}
	else
	{
		g_Log.EventError("MySQL error #%u: %s [Cmd: \"%s\"]\n", mysql_errno(m_socket), mysql_error(m_socket), query);
		if ( (resultCode == CR_SERVER_GONE_ERROR) || (resultCode == CR_SERVER_LOST) )
			Close();

		return false;
	}
}