/*fid:
CSIDL_BITBUCKET   回收站    
CSIDL_CONTROLS   控制面板    
CSIDL_DESKTOP   Windows   桌面Desktop    
CSIDL_DESKTOPDIRECTORY   Desktop的目录    
CSIDL_DRIVES   我的电脑    
CSIDL_FONTS   字体目录    
CSIDL_NETHOOD   网上邻居    
CSIDL_NETWORK   网上邻居虚拟目录    
CSIDL_PERSONAL   我的文档    
CSIDL_PRINTERS   打印机    
CSIDL_PROGRAMS   程序组    
CSIDL_RECENT   最近打开的文档    
CSIDL_SENDTO   “发送到”菜单项    
CSIDL_STARTMENU   任务条启动菜单项    
CSIDL_STARTUP   启动目录    
CSIDL_TEMPLATES   文档模板
*/
CString GetSysFolderPath(int fid)
{
	CString path;
	LPITEMIDLIST pidl=0;
	HRESULT hr = SHGetFolderLocation(NULL,fid,NULL,NULL,&pidl);
	if (pidl)
	{
		TCHAR fpath[MAX_PATH]={0};
		if(SHGetPathFromIDList(pidl,fpath))
		{
			TCHAR ffpath[MAX_PATH]={0};
			GetShortPathName(fpath,ffpath,MAX_PATH);
			path = ffpath;
		}
	}
	return path;
}