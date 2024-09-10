BOOL CFormatRecoveryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
// 	if(__argc != 2 || 0 != strcmp(__argv[1],"NJU"))
// 		SendMessage(WM_CLOSE,0,0);
	SetErrorMode( SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);

	// TODO: Add extra initialization here
	m_allext.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_searchext.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_result.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_result.InsertColumn(0,"序号",LVCFMT_LEFT,100);
	m_result.InsertColumn(1,"文件类型",LVCFMT_LEFT,200);
	m_result.InsertColumn(2,"文件大小",LVCFMT_LEFT,100);
	m_result.InsertColumn(3,"是否有效",LVCFMT_LEFT,100);

	pthread=NULL;
	recover=NULL;
	CFormatRecovery null(NULL,m_result,m_progress);//利用空类，仅仅获取dll支持类型，其他什么都不做
	CList<CString,CString&> mylist;
	null.GetSupportFileExtension(mylist);
	POSITION pos=mylist.GetHeadPosition();
	for(int i=0;i<mylist.GetCount();i++)
	{
		m_allext.InsertItem(i,mylist.GetNext(pos));
	}

	//枚举分区
	int bufsize=GetLogicalDriveStrings(0,NULL);
	char* buf=new char[bufsize+1];
	GetLogicalDriveStrings(bufsize,buf);
	char* ptr=buf;
	int index=0;
	while(*ptr)
	{
		UINT type=GetDriveType(ptr);
		if(type == DRIVE_REMOVABLE || type == DRIVE_FIXED || type == DRIVE_REMOTE)
		{
			char drive[16]="\\\\.\\";
			strcat_s(drive,ptr);//得到设备符号
			drive[strlen(drive)-1]='\0';
			m_searcharea.AddString(drive);
		}
		ptr+=strlen(ptr)+1;
	}
	delete []buf;

	//枚举硬盘
	char drive[32];
	int disknum=0;
	while(TRUE)
	{
		sprintf_s(drive,"\\\\.\\PHYSICALDRIVE%d",disknum++);//对于硬盘以0x1000为单位搜不到文件，以后的版本需要改善，改为0x08?
		HANDLE hDisk=CreateFile(drive,0,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hDisk == INVALID_HANDLE_VALUE)//如果句柄无效说明已经枚举完毕
			break;
		CloseHandle(hDisk);
		m_searcharea.AddString(drive);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}