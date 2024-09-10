static int32 expand_dir(char* buffer, const char* dir)
{
	int32 size=0;
	while( dir && *dir ) {
		if( *dir == '%' ) {
			dir++;
			switch( *dir ) {
				case '%':
					break;
				case 'A': {
					BPath path;
					if( get_app_path(&path) == B_NO_ERROR ) {
						if( path.GetParent(&path) == B_NO_ERROR ) {
							const char* dir = path.Path();
							if( dir ) {
								ArpD(cdb << ADH << "App dir = " << dir << endl);
								int len = strlen(dir);
								size += len;
								if( buffer ) {
									memcpy(buffer,dir,len);
									buffer += len;
								}
							}
						}
					}
					dir++;
				} break;
				case 0:
					if( buffer ) *buffer = 0;
					return size+1;
				default:
					dir++;
					break;
			}
		}
		if( buffer ) *(buffer++) = *dir;
		dir++;
		size++;
	}
	if( buffer ) *buffer = 0;
	return size+1;
}