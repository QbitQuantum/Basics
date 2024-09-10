		void BindParameter(int index, SQLSMALLINT fParamType,
			SQLSMALLINT fCType, SQLSMALLINT fSqlType, SQLULEN cbColDef,
			SQLSMALLINT ibScale, SQLPOINTER rgbValue, SQLLEN cbValueMax,
			SQLLEN *pcbValue)
		{
			assert(index > 0);
			SQLRETURN rc = 0;

			rc = SQLBindParameter(mStmt, index, fParamType, fCType, fSqlType,
				cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
			if (!SQL_SUCCEEDED(rc))
			{
				std::string message;
				HANAException::GetHANAErrorMessage(SQL_HANDLE_STMT, mStmt, rc, message);
				throw HANAException(message.c_str());
			}
		}	