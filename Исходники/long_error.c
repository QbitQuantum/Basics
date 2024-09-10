static void
extract_error(SQLHANDLE handle, SQLSMALLINT type)
{
	SQLINTEGER i = 0;
	SQLINTEGER native;
	SQLWCHAR state[7];
	SQLWCHAR text[256];
	SQLSMALLINT len;
	SQLRETURN ret;

	fprintf(stderr, "\n" "The driver reported the following diagnostics\n");

	do {
		ret = SQLGetDiagRecW(type, handle, ++i, state, &native, text, 256, &len);
		state[5] = 0;
		if (SQL_SUCCEEDED(ret))
			printf("%s:%ld:%ld:%s\n", odbc_get_sqlchar(&odbc_buf, state), (long) i,
			       (long) native, odbc_get_sqlchar(&odbc_buf, text));
	}
	while (ret == SQL_SUCCESS);
}