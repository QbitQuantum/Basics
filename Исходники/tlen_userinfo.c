static int TlenEnterBitmapName( char* szDest )
{
	OPENFILENAMEA ofn = {0};
	char str[ MAX_PATH ];
	char szFilter[ 512 ];
	*szDest = 0;
	CallService( MS_UTILS_GETBITMAPFILTERSTRINGS, sizeof szFilter, ( LPARAM )szFilter );
	str[0] = 0;
	ofn.lStructSize = sizeof( OPENFILENAME );
	ofn.lpstrFilter = szFilter;
	ofn.lpstrFile = szDest;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrDefExt = "bmp";
	if ( !GetOpenFileNameA( &ofn ))
		return 1;

	return ERROR_SUCCESS;
}