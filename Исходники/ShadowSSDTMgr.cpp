BOOL CShadowSSDTMgr::GetShadowSSDTNativeAddrBySymbol()
{
	BOOL			boRetn;
	PDWORD			pW32pServiceTable = 0;
	DWORD			dwload = 0;
	PLOADED_IMAGE	ploadImage = {0};
	char			imgPath[MAX_PATH];

	// 初始化
	if ( !InitSymbolsHandler() )
	{
		return FALSE;
	}

	// 获取系统目录"C:\WINDOWS\system32"
	GetSystemDirectory( imgPath, MAX_PATH );
	// 加载模块
	ploadImage = ImageLoad( "win32k.sys", imgPath );

	// 加载符号"C:\WINDOWS\system32\win32k.sys"
	strcat( imgPath, "\\win32k.sys" );
	dwload=SymLoadModule ( g_ixerhProc, ploadImage->hFile,
									imgPath, "win32k.pdb",
									0, ploadImage->SizeOfImage );

	boRetn=SymEnumSymbols( g_ixerhProc, dwload, NULL, (PSYM_ENUMERATESYMBOLS_CALLBACK)EnumSymRoutine, NULL );
	if (g_W32pServiceTable)
	{
		pW32pServiceTable = (PDWORD)( g_W32pServiceTable - dwload + (DWORD)ploadImage->MappedAddress );
		boRetn=SymEnumSymbols( g_ixerhProc, dwload, NULL, (PSYM_ENUMERATESYMBOLS_CALLBACK)EnumSymRoutine, pW32pServiceTable );
	}

	ImageUnload(ploadImage);
	SymCleanup(g_ixerhProc);
	return boRetn;
}