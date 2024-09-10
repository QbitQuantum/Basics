//
// 从资源中加载动画光标
// 如果动画光标是 256 色的，CreateIconFromResource() 就会失败返回 NULL，但 GetLastError() 返回 0
//
HCURSOR
LoadAniCursor(
	const char *pResourceType,  // 资源类型
	UINT        uID )           // 资源 ID
{
	HINSTANCE hInst = _Module.GetResourceInstance();
	HRSRC hRes = FindResource( hInst, MAKEINTRESOURCE( uID ), pResourceType );
	if( hRes )
	{
		DWORD   dwSize = SizeofResource( hInst, hRes );
		HGLOBAL hGlob  = LoadResource( hInst, hRes );
		if( hGlob )
		{
			LPBYTE pBytes = (LPBYTE)LockResource( hGlob ); 
			if( pBytes )
				return( (HCURSOR)CreateIconFromResource( pBytes, dwSize, FALSE, 0x00030000 ) );
		}
	}

	return( NULL );
}