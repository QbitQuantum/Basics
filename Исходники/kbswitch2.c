static void NotifyCtl(DWORD action,const wchar_t *pTip,UINT extraFlags)
{
	NOTIFYICONDATAW nid;

	ZeroFill(&nid,sizeof nid);

	nid.cbSize=sizeof nid;
	nid.hWnd=g_hWnd;
	nid.uID=NOTIFY_ID;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|extraFlags;
	nid.uCallbackMessage=NOTIFY_MSG;
	nid.hIcon=LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1));
	nid.uTimeout=500;

	if(pTip)
	{
		enum {
			MAX_TIP_SIZE=sizeof nid.szTip/sizeof nid.szTip[0],
			MAX_INFO_SIZE=sizeof nid.szInfo/sizeof nid.szInfo[0],
			MAX_INFO_TITLE_SIZE=sizeof nid.szInfoTitle/sizeof nid.szInfoTitle[0],
		};

		nid.uFlags|=NIF_TIP;

		lstrcpynW(nid.szTip,pTip,MAX_TIP_SIZE);
		nid.szTip[MAX_TIP_SIZE-1]=0;

		lstrcpynW(nid.szInfo,pTip,MAX_INFO_SIZE);
		nid.szInfo[MAX_INFO_SIZE-1]=0;

		lstrcpynW(nid.szInfoTitle,L"kbswitch2",MAX_INFO_TITLE_SIZE);
		nid.szInfoTitle[MAX_INFO_TITLE_SIZE-1]=0;
	}

	Shell_NotifyIconW(action,&nid);
}