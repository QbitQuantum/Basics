 //================================================================================================
//---------------------------+++--> Verify Existance of Launch T-Clock on Windows Startup ShortCut:
BOOL FileExists(HWND hDlg) { //-------------------------------------------------------------+++-->
	LPITEMIDLIST pidl;
	char dstpath[MAX_PATH], path[MAX_PATH], path2[MAX_PATH];
	char *lpStr1, *lpStr2;
	int	retval;	

  if(SHGetSpecialFolderLocation(hDlg, CSIDL_STARTUP, &pidl) == NOERROR 
						&& SHGetPathFromIDList(pidl, dstpath) == TRUE);
  else return FALSE;

  strcpy(path, dstpath);
  strcat(path, "\\");
  strcat(path, CONF_START);
  strcat(path, ".lnk");
  lpStr1 = path;
  retval = PathFileExists(lpStr1);
  if(retval == 1) return TRUE;
  else{
	strcpy(path2, dstpath);
	strcat(path2, "\\");
	strcat(path2, CONF_START);
    strcat(path2, ".lnk");
	lpStr2 = path2;
	retval = PathFileExists(lpStr2);
	if(retval == 1) return TRUE;
  }
 return FALSE;
}