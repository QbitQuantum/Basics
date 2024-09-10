dbResult::dbResult (SQLHDBC& dbhandle, string& queryString,  long long& affectedRows)
{

	SQLHSTMT odbc_stmt;
	SQLRETURN ret;
	SQLSMALLINT columns;
	SQLLEN rows;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, dbhandle, &odbc_stmt);
	if ( !SQL_SUCCEEDED(ret) )
	{
		//extract_error("SQLExecDirect", dbhandle, SQL_HANDLE_DBC);
                //errNo=-3;
	}
	else
	{
		SQLExecDirect(odbc_stmt, (SQLCHAR *) queryString.c_str(), SQL_NTS);
		SQLNumResultCols (odbc_stmt, &columns);
		Fields = columns;
		SQLRowCount (odbc_stmt, &rows);
		Rows = rows;
		affectedRows = Rows;
		while ( SQL_SUCCEEDED(SQLFetch(odbc_stmt)))
		{
			//now fetch results ant put them inside a dbresult struct.
			Row Row_buff;
			SQLSMALLINT i;
			for (i=1;i<=columns;i++)
			{
				SQLINTEGER indicator;
				char buff[8192];//FIXME This is bad! Should find
						//a better way (Try with string??)
				ret = SQLGetData(odbc_stmt,
					i,
					SQL_C_CHAR,
					buff,
					sizeof(buff),
					&indicator);
				if (SQL_SUCCEEDED(ret))
				{
					if (indicator == SQL_NULL_DATA )
					{
						strcpy (buff,"NULL");
					}
					string strBuff = buff;
					Row_buff.push_back(strBuff);
				}
			}
			Result.push_back(Row_buff);
		}
		SQLFreeHandle(SQL_HANDLE_STMT, odbc_stmt);	
	}
}