bool COdbcDS::FindInstalledDrvr(const char* pDrvrName)
{
	SQLCHAR Description[100];
	SQLSMALLINT descLen;
	SQLRETURN retVal = SQL_SUCCESS;

	// Loop through all of the data sources until the one we're looking for
	// is found.
	int count = 0;
	while (retVal == SQL_SUCCESS || retVal == SQL_SUCCESS_WITH_INFO)
	{
		if (count == 0)
			retVal = SQLDrivers(m_henv, SQL_FETCH_FIRST, Description,
									sizeof(Description), &descLen,
									NULL, 0, NULL);
		else
			retVal = SQLDrivers(m_henv, SQL_FETCH_NEXT, Description,
									sizeof(Description), &descLen,
									NULL, 0, NULL);
		count++;
		if (retVal == SQL_ERROR)
		{
			throw 3;
		}

		if (strcmp(pDrvrName, (const char*)Description) == 0)
		{
			return true;
		}
	}
	return false;
}