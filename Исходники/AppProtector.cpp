CAppProtector::CAppProtector(const char *lpszProtectedFileName,const char *lpszOriginalPEImageName, CAppSecureDlg* t)
{
	ui=t;
	/*
	lpszProtectedFileName is the output filename, which is "SecureFile.EXE" by default
	lpszOriginalPEImageName is the PE File to protect. This file will NOT be modified in anyway.
	*/
	szProtectedFileName=new char[lstrlen(lpszProtectedFileName)+1];
	lstrcpy(szProtectedFileName,lpszProtectedFileName);
	szMyFileName=new char[lstrlen(lpszOriginalPEImageName)+1];
	lstrcpy(szMyFileName,lpszOriginalPEImageName);
	/////////////////////////////////////////////////////////////////////////
	LOADED_IMAGE li;
	if(MapAndLoad(szMyFileName,0,&li,FALSE,TRUE)) RVAToFileOffset(li.FileHeader,li.FileHeader->OptionalHeader.AddressOfEntryPoint,li.FileHeader->FileHeader.NumberOfSections);
    else
    {
        AfxMessageBox("Load Failed !");
        exit(1);
    }
	UnMapAndLoad(&li);
	/////////////////////////////////////////////////////////////////////////
}