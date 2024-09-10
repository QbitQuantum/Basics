int x509_crt_parse_path( x509_crt *chain, const char *path )
{
    int ret = 0;
#if defined(_WIN32) && !defined(EFIX64) && !defined(EFI32)
    int w_ret;
    WCHAR szDir[MAX_PATH];
    char filename[MAX_PATH];
	char *p;
    int len = (int) strlen( path );

	WIN32_FIND_DATAW file_data;
    HANDLE hFind;

    if( len > MAX_PATH - 3 )
        return( POLARSSL_ERR_X509_BAD_INPUT_DATA );

	memset( szDir, 0, sizeof(szDir) );
	memset( filename, 0, MAX_PATH );
	memcpy( filename, path, len );
	filename[len++] = '\\';
	p = filename + len;
    filename[len++] = '*';

	w_ret = MultiByteToWideChar( CP_ACP, 0, filename, len, szDir, MAX_PATH - 3 );

    hFind = FindFirstFileW( szDir, &file_data );
    if (hFind == INVALID_HANDLE_VALUE)
        return( POLARSSL_ERR_X509_FILE_IO_ERROR );

    len = MAX_PATH - len;
    do
    {
		memset( p, 0, len );

        if( file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            continue;

		w_ret = WideCharToMultiByte( CP_ACP, 0, file_data.cFileName,
									 lstrlenW(file_data.cFileName),
									 p, len - 1,
									 NULL, NULL );

        w_ret = x509_crt_parse_file( chain, filename );
        if( w_ret < 0 )
            ret++;
        else
            ret += w_ret;
    }
    while( FindNextFileW( hFind, &file_data ) != 0 );

    if (GetLastError() != ERROR_NO_MORE_FILES)
        ret = POLARSSL_ERR_X509_FILE_IO_ERROR;

    FindClose( hFind );
#else /* _WIN32 */
    int t_ret;
    struct stat sb;
    struct dirent *entry;
    char entry_name[255];
    DIR *dir = opendir( path );

    if( dir == NULL)
        return( POLARSSL_ERR_X509_FILE_IO_ERROR );

#if defined(POLARSSL_THREADING_PTHREAD)
    if( ( ret = polarssl_mutex_lock( &readdir_mutex ) ) != 0 )
        return( ret );
#endif

    while( ( entry = readdir( dir ) ) != NULL )
    {
        snprintf( entry_name, sizeof entry_name, "%s/%s", path, entry->d_name );

        if( stat( entry_name, &sb ) == -1 )
        {
            closedir( dir );
            ret = POLARSSL_ERR_X509_FILE_IO_ERROR;
            goto cleanup;
        }

        if( !S_ISREG( sb.st_mode ) )
            continue;

        // Ignore parse errors
        //
        t_ret = x509_crt_parse_file( chain, entry_name );
        if( t_ret < 0 )
            ret++;
        else
            ret += t_ret;
    }
    closedir( dir );

cleanup:
#if defined(POLARSSL_THREADING_PTHREAD)
    if( polarssl_mutex_unlock( &readdir_mutex ) != 0 )
        ret = POLARSSL_ERR_THREADING_MUTEX_ERROR;
#endif

#endif /* _WIN32 */

    return( ret );
}