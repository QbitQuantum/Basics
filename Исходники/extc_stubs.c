CAMLprim value get_real_path( value path ) {
#ifdef _WIN32
	value path2 = caml_copy_string(String_val(path));
	char *cur = String_val(path2);
	if( cur[0] == '\\' && cur[1] == '\\' ) {
		cur = strchr(cur,'\\');
		if( cur != NULL ) cur++;
	} else if( cur[0] != 0 && cur[1] == ':' ) {
		char c = cur[0];
		if( c >= 'a' && c <= 'z' )
			cur[0] = c - 'a' + 'A';
		cur += 2;
		if( cur[0] == '\\' )
			cur++;
	}
	while( cur ) {
		char *next = strchr(cur,'\\');
		SHFILEINFOA infos;
		if( next != NULL )
			*next = 0;
		else if( *cur == 0 )
			break;
		if( SHGetFileInfoA( String_val(path2), 0, &infos, sizeof(infos), SHGFI_DISPLAYNAME ) != 0 ) {
			// some special names might be expended to their localized name, so make sure we only
			// change the casing and not the whole content
			if( strcmpi(infos.szDisplayName,cur) == 0 )
				copyAscii(cur,infos.szDisplayName,strlen(infos.szDisplayName)+1);
		}
		if( next != NULL ) {
			*next = '\\';
			cur = next + 1;
		} else
			cur = NULL;
	}
	return path2;
#else
	return path;
#endif
}