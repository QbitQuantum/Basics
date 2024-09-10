void extract_error(
char *fn,
SQLHANDLE handle,
SQLSMALLINT type,
char* stret)
{
	SQLINTEGER   i = 0;
	SQLINTEGER   native;
	SQLCHAR  state[ 7 ];
	SQLCHAR  text[256];
	SQLSMALLINT  len;
	SQLRETURN	ret;

	do
	{
		ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
			sizeof(text), &len );
		if (SQL_SUCCEEDED(ret)) {
			LM_ERR("unixodbc:%s=%s:%ld:%ld:%s\n", fn, state, (long)i, 
					(long)native, text);
			if(stret) strcpy( stret, (char*)state );
		}
	}
	while( ret == SQL_SUCCESS );
}