int GetFile(char *szFileName, char *szParse=0,u32 flags=0) 
{
	cfgLoadStr("config","image",szFileName,"null");
	if (strcmp(szFileName,"null")==0)
	{
#if defined(OMAP4)
		strcpy(szFileName,GetPath("/gdimage/crazy_taxi.chd").c_str());
#else
	#if HOST_OS==OS_WINDOWS
		OPENFILENAME ofn;
		ZeroMemory( &ofn , sizeof( ofn));
	ofn.lStructSize = sizeof ( ofn );
	ofn.hwndOwner = NULL  ;
	ofn.lpstrFile = szFileName ;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "All\0*.*\0\0";
	ofn.nFilterIndex =1;
	ofn.lpstrFileTitle = NULL ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir=NULL ;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST ;

		if (GetOpenFileNameA(&ofn))
		{
			//already there
			//strcpy(szFileName,ofn.lpstrFile);
		}
	#else
		strcpy(szFileName,GetPath("/game.chd").c_str());
	#endif
#endif
	}

	if (strcmp(szFileName,"hardpath")==0)
	{
		strcpy(szFileName,"D:\\DC\\shenmue.chd");
	}

	
	return 1; 
}