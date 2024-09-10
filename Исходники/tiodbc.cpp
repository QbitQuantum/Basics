	void __bind_param(HSTMT _stmt, int _parnum,
						SQLSMALLINT _ctype, SQLSMALLINT _sqltype,
						void * dst_buf, SQLLEN & StrLenOrInPoint,
						int sz = 0, int buf_sz = 0)
	{
		RETCODE rc = SQLBindParameter(_stmt,
			_parnum,
			SQL_PARAM_INPUT,
			_ctype,
			_sqltype,
			sz,
			0,
			(SQLPOINTER *)dst_buf,
			buf_sz,
			&StrLenOrInPoint);
		if (!TIODBC_SUCCESS_CODE(rc))
			throw bind_error(_parnum);
	}