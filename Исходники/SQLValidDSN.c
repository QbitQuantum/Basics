BOOL INSTAPI SQLValidDSNW(LPCWSTR lpszDSN)
{
	char *dsn;
	BOOL ret;

	dsn = _single_string_alloc_and_copy( lpszDSN );

	ret = SQLValidDSN( dsn );

	free( dsn );

	return ret;
}