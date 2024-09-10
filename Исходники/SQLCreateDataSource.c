BOOL INSTAPI SQLCreateDataSourceW     (HWND       hwndParent,
                                      LPCWSTR     lpszDSN)
{
	BOOL ret;
	char *ms = _multi_string_alloc_and_copy( lpszDSN );

	ret = SQLCreateDataSource( hwndParent, ms );

	free( ms );

	return ret;
}