extern "C" int link( char* source, char* dest )
{
	HANDLE fh;

	enableprivs(); // in case we aren't admin

	fh = CreateFile( source, GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_POSIX_SEMANTICS, NULL );
	if ( fh == INVALID_HANDLE_VALUE || fh == NULL )
	return 4;

	static char buf1[MAX_PATH];
	static wchar_t buf2[MAX_PATH * 2];
	char *p;
	void *ctx = NULL;
	WIN32_STREAM_ID wsi;
	DWORD numwritten;

	GetFullPathName( dest, MAX_PATH, &buf1[0], &p );

	wsi.dwStreamId = BACKUP_LINK;
	wsi.dwStreamAttributes = 0;
	wsi.dwStreamNameSize = 0;
	wsi.Size.QuadPart = strlen( buf1 ) * 2 + 2;
	MultiByteToWideChar( CP_ACP, 0, buf1, strlen( buf1 ) + 1, buf2, MAX_PATH );

	if ( ! BackupWrite( fh, (byte *) &wsi, 20, &numwritten, FALSE, FALSE, &ctx ) )
		return 5;
	if ( numwritten != 20 )
		return 6;

	if ( ! BackupWrite( fh, (byte *) buf2, wsi.Size.LowPart, &numwritten, FALSE, FALSE, &ctx ) )
		return 7;
	if ( numwritten != wsi.Size.LowPart )
		return 8;

	// make NT release the context
	BackupWrite( fh, (byte *) &buf1[0], 0, &numwritten, TRUE, FALSE, &ctx );

	CloseHandle( fh );

	return 0;
}