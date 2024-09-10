void  MoveLinkToStartup4(char *szSrcExeName)
{

	//c:\\Documents and Settings\\All Users\\「开始」菜单\\程序\\启动\\";

	TCHAR szLink[MAX_PATH];
	StrCpyA(szLink,szSrcExeName);

	*(StrRChr(szLink,0,'.'))=0;

	StrCatA(szLink,".lnk");

	CreateShortcut(szSrcExeName,0,0,szLink,0);
	TCHAR szStartLink[MAX_PATH];
 	SHGetSpecialFolderPath(NULL,szStartLink,CSIDL_COMMON_STARTUP,0);
 	StrCatA(szStartLink,StrRChr(szLink,0,'\\'));
	DeleteFile(szStartLink);
	MoveFileEx(szLink,szStartLink,MOVEFILE_DELAY_UNTIL_REBOOT|MOVEFILE_REPLACE_EXISTING);
	return ;
}