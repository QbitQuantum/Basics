extern "C" void __declspec(dllexport) CreateMediaCenterShortcut( HWND hwndParent,
																  int string_size,
																  char *variables,
																  stack_t **stacktop)
{
	EXDLL_INIT();

	char *cBinPath = NULL;
	cBinPath = (char*)GlobalAlloc(GPTR, string_size);
	popstring( cBinPath );

	char shortcutLink[MAX_PATH];
	sprintf( shortcutLink, "\"%s\" -media", cBinPath );

	HRESULT hr = CoInitialize(NULL);
	char *mediaCenterPath = (char*)GlobalAlloc(GPTR, string_size);
	hr = SHGetFolderPathA( NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_CURRENT, mediaCenterPath );

	char shortcutPath[MAX_PATH];
	char filename[MAX_PATH];
	sprintf( shortcutPath, "%s\\Media Center Programs\\Darwinia", mediaCenterPath );
	sprintf( filename, "%s\\darwinia.lnk", shortcutPath );

	CreateLink( cBinPath, shortcutPath, filename, "", "-mediacenter" );
}