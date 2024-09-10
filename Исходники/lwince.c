/*
** Implementation of freopen() - requires wide char conversion
*/
RTEXP	FILE *freopen( const char *path, const char *mode, FILE *stream ) {
	wchar_t	wpath[BUFSIZ];
	wchar_t	wmode[8];

	MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, path, -1, wpath, BUFSIZ);
	MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, mode, -1, wmode, 8);
	return(_wfreopen(wpath, wmode, stream));
}