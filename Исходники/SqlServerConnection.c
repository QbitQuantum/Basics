ResultSet_T SqlServerConnection_executeQuery(T C, const char *sql, va_list ap) {
	va_list ap_copy;
	const char *tail;
	SQLHSTMT hstmt;

	assert(C);
	StringBuffer_clear(C->sb);
	va_copy(ap_copy, ap);
	StringBuffer_vappend(C->sb, sql, ap_copy);
	va_end(ap_copy);

	C->lastError = SQLAllocStmt(C->db->hdbc,&hstmt);


	C->lastError = SQLPrepare(hstmt,
		StringBuffer_toString(C->sb), StringBuffer_length(C->sb)); 
	if(!SQLSERVERSUCCESS(C->lastError)) {
		getSqlErr(C,hstmt);
		return NULL;
	}
	C->lastError = SQLExecute(hstmt);
	if(SQLSERVERSUCCESS(C->lastError))
		return ResultSet_new(SqlServerResultSet_new(hstmt, C->maxRows, false), (Rop_T)&sqlserverrops);
	else {
		getSqlErr(C,hstmt);
	}
	return NULL;
}