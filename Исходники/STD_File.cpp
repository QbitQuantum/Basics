// ---------------------------------------------------------------------------
//	iniファイルから文字を読み取る
// ---------------------------------------------------------------------------
int ReadIniFileStr( char *vname, char *str, char *def, int size, char *sec_name, char *ini_fname )
{
	char	*buf = (char*)GAlloc( size+1 );
//	char	*buf = (char*)GAlloc( size );
	
	if( ini_fname==NULL){
		if(IniFileName[0]==0){
			ini_fname = "default.ini";
		}else{
			ini_fname = IniFileName;
		}
	}

	GetPrivateProfileString( sec_name, vname, def, buf, size, ini_fname );
	if( _mbscmp( (BYTE*)def, (BYTE*)buf ) ){
		_mbscpy( (BYTE*)str, (BYTE*)buf+1 );
	}else{
		_mbscpy( (BYTE*)str, (BYTE*)buf );
	}
//	_mbscpy( (BYTE*)str, (BYTE*)buf );
	GFree(buf);

	return 0;
}