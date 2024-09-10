list<wstring> get_volume_mount_points( const wstring& volume_guid_path ) {
	unsigned buf_size = MAX_PATH;
	unique_ptr<wchar_t[ ]> buffer( new wchar_t[ buf_size ] );
	DWORD len;
	BOOL res = GetVolumePathNamesForVolumeNameW( add_trailing_slash( volume_guid_path ).c_str( ), buffer.get( ), buf_size, &len );
	if ( !res ) {
		if ( GetLastError( ) == ERROR_MORE_DATA ) {
			buf_size = len;
			buffer.reset( new wchar_t[ buf_size ] );
			res = GetVolumePathNamesForVolumeNameW( add_trailing_slash( volume_guid_path ).c_str( ), buffer.get( ), buf_size, &len );
			}
		CHECK_SYS( res );
		}
	list<wstring> result;
	const wchar_t* path = buffer.get( );
	while ( *path ) {
		unsigned len = wcslen( path );
		result.push_back( wstring( path, len ) );
		path += len + 1;
		}
	return result;
	}