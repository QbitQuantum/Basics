void TypeInfo::fillTypeInfo(SQLHDBC pHDBC)
{
	_pHDBC = &pHDBC;

	if (_typeInfo.empty() && _pHDBC)
	{
		const static int stringSize = 512;
		TypeInfoVec().swap(_typeInfo);

		SQLRETURN rc;
		SQLHSTMT hstmt = SQL_NULL_HSTMT;

		rc = SQLAllocHandle(SQL_HANDLE_STMT, *_pHDBC, &hstmt);
		if (!SQL_SUCCEEDED(rc))
			throw StatementException(hstmt, "SQLGetData()");

		rc = SQLGetTypeInfo(hstmt, SQL_ALL_TYPES);
		if (SQL_SUCCEEDED(rc))
		{
			while (SQLFetch(hstmt) != SQL_NO_DATA_FOUND)
			{
				char typeName[stringSize] = { 0 };
				char literalPrefix[stringSize] = { 0 };
				char literalSuffix[stringSize] = { 0 };
				char createParams[stringSize] = { 0 };
				char localTypeName[stringSize] = { 0 };
				
				TypeInfoTup ti("TYPE_NAME", "",
					"DATA_TYPE", 0,
					"COLUMN_SIZE", 0,
					"LITERAL_PREFIX", "",
					"LITERAL_SUFFIX", "",
					"CREATE_PARAMS", "",
					"NULLABLE", 0,
					"CASE_SENSITIVE", 0,
					"SEARCHABLE", 0,
					"UNSIGNED_ATTRIBUTE", 0,
					"FIXED_PREC_SCALE", 0,
					"AUTO_UNIQUE_VALUE", 0,
					"LOCAL_TYPE_NAME", "",
					"MINIMUM_SCALE", 0,
					"MAXIMUM_SCALE", 0,
					"SQL_DATA_TYPE", 0,
					"SQL_DATETIME_SUB", 0,
					"NUM_PREC_RADIX", 0,
					"INTERVAL_PRECISION", 0);

				SQLLEN ind = 0;
				rc = SQLGetData(hstmt, 1, SQL_C_CHAR, typeName, sizeof(typeName), &ind);
				ti.set<0>(typeName);
				rc = SQLGetData(hstmt, 2, SQL_C_SSHORT, &ti.get<1>(), sizeof(SQLSMALLINT), &ind);
				rc = SQLGetData(hstmt, 3, SQL_C_SLONG, &ti.get<2>(), sizeof(SQLINTEGER), &ind);
				rc = SQLGetData(hstmt, 4, SQL_C_CHAR, literalPrefix, sizeof(literalPrefix), &ind);
				ti.set<3>(literalPrefix);
				rc = SQLGetData(hstmt, 5, SQL_C_CHAR, literalSuffix, sizeof(literalSuffix), &ind);
				ti.set<4>(literalSuffix);
				rc = SQLGetData(hstmt, 6, SQL_C_CHAR, createParams, sizeof(createParams), &ind);
				ti.set<5>(createParams);
				rc = SQLGetData(hstmt, 7, SQL_C_SSHORT, &ti.get<6>(), sizeof(SQLSMALLINT), &ind); 
				rc = SQLGetData(hstmt, 8, SQL_C_SSHORT, &ti.get<7>(), sizeof(SQLSMALLINT), &ind); 
				rc = SQLGetData(hstmt, 9, SQL_C_SSHORT, &ti.get<8>(), sizeof(SQLSMALLINT), &ind); 
				rc = SQLGetData(hstmt, 10, SQL_C_SSHORT, &ti.get<9>(), sizeof(SQLSMALLINT), &ind); 
				rc = SQLGetData(hstmt, 11, SQL_C_SSHORT, &ti.get<10>(), sizeof(SQLSMALLINT), &ind);
				rc = SQLGetData(hstmt, 12, SQL_C_SSHORT, &ti.get<11>(), sizeof(SQLSMALLINT), &ind);
				rc = SQLGetData(hstmt, 13, SQL_C_CHAR, localTypeName, sizeof(localTypeName), &ind);
				ti.set<12>(localTypeName);
				rc = SQLGetData(hstmt, 14, SQL_C_SSHORT, &ti.get<13>(), sizeof(SQLSMALLINT), &ind);
				rc = SQLGetData(hstmt, 15, SQL_C_SSHORT, &ti.get<14>(), sizeof(SQLSMALLINT), &ind);
				rc = SQLGetData(hstmt, 16, SQL_C_SSHORT, &ti.get<15>(), sizeof(SQLSMALLINT), &ind);
				rc = SQLGetData(hstmt, 17, SQL_C_SSHORT, &ti.get<16>(), sizeof(SQLSMALLINT), &ind);
				rc = SQLGetData(hstmt, 18, SQL_C_SLONG, &ti.get<17>(), sizeof(SQLINTEGER), &ind);
				rc = SQLGetData(hstmt, 19, SQL_C_SSHORT, &ti.get<18>(), sizeof(SQLSMALLINT), &ind);

				_typeInfo.push_back(ti);
			}
		}

		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	}
}