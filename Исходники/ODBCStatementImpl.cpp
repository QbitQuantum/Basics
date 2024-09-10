std::string ODBCStatementImpl::nativeSQL()
{
	std::string statement = toString();

	SQLINTEGER length = (SQLINTEGER) statement.size() * 2;

	char* pNative = 0;
	SQLINTEGER retlen = length;
	do
	{
		delete [] pNative;
		pNative = new char[retlen];
		memset(pNative, 0, retlen);
		length = retlen;
		if (Utility::isError(SQLNativeSql(_rConnection,
			(SQLCHAR*) statement.c_str(),
			(SQLINTEGER) statement.size(),
			(SQLCHAR*) pNative,
			length,
			&retlen)))
		{
			delete [] pNative;
			throw ConnectionException(_rConnection, "SQLNativeSql()");
		}
		++retlen;//accomodate for terminating '\0'
	}while (retlen > length);

	std::string sql(pNative);
	delete [] pNative;
	return sql;
}