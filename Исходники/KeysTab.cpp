void cAmp::PlsOpen()
{
	OPENFILENAMEA ofn;  ZeroMemory(&ofn,sizeof(ofn));  ofn.lStructSize = sizeof(ofn);
	char szFile[MP], sDir[MP];	ofn.hwndOwner = hWnd;

	ofn.lpstrFile = szFile;  ofn.lpstrFile[0]='\0';  ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "cAmp Playlists (*.cp)\0*.cp\0";	ofn.nFilterIndex=1;
	ofn.lpstrFileTitle = NULL;	ofn.nMaxFileTitle = 0;

	scpy(sDir, cSnd::appPath.c_str());  sadd(sDir, "playlists");
	ofn.lpstrInitialDir = sDir;
	ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_ENABLESIZING|
		OFN_NOCHANGEDIR|OFN_NONETWORKBUTTON|OFN_HIDEREADONLY/*|OFN_ALLOWMULTISELECT*/;

	if (GetOpenFileNameA(&ofn)==TRUE)  {
		char* pp = strrchr(ofn.lpstrFile,'\\')+1, *pe = strrchr(ofn.lpstrFile,'.');  pe[0]=0;  //no dir,ext
		//dont duplicate pls names--
		pls->name = /*ofn.lpstrFile*/pp;  pls->Load();  }
}