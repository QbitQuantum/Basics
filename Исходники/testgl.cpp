std::string chooseFileName()
{
#ifdef _WINDOWS
	OPENFILENAMEA ofn ;
	static char szFile[_MAX_PATH] ;

    ZeroMemory( &ofn , sizeof( ofn) );
	ofn.lStructSize = sizeof ( ofn );
	ofn.hwndOwner = NULL  ;
	ofn.lpstrFile = szFile ;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof( szFile );
	ofn.lpstrFilter = "All\0*.*\0Images\0*.jpg;*.png\0";
	ofn.nFilterIndex =1;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir=NULL ;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST ;

	GetOpenFileNameA( &ofn );

	return ofn.lpstrFile;
#else
	return "";
#endif
}