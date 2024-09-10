BOOL CKeyborDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();
 
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_tab.InsertItem(0," 基本设置 "); //添加参数一选项卡 
    m_tab.InsertItem(1," 快捷映射 "); //添加参数二选项卡 
	m_tab.InsertItem(2," 计划任务 "); 
	m_tab.InsertItem(3," 扩展应用 ");
    m_tab.InsertItem(4," 关于 "); //添加结果选项卡 

	//关联对话框,并且将IDC_TAB控件设为父窗口 
	dlg1.Create(IDD_DIALOG1,GetDlgItem(IDC_TAB)); 
	dlg2.Create(IDD_DIALOG2,GetDlgItem(IDC_TAB)); 
	dlg4.Create(IDD_DIALOG4,GetDlgItem(IDC_TAB)); 
	dlg5.Create(IDD_DIALOG5,GetDlgItem(IDC_TAB));
	dlg3.Create(IDD_DIALOG3,GetDlgItem(IDC_TAB)); 

	//获得IDC_TABTEST客户区大小 
	CRect rs; 
	m_tab.GetClientRect(&rs ); 
	//调整子对话框在父窗口中的位置 
	rs.top+=22; 
	rs.bottom+=30; 
	//rs.left+=1; 
	//rs.right-=2; 

	//设置子对话框尺寸并移动到指定位置 
	dlg1.MoveWindow(&rs); 
	dlg2.MoveWindow(&rs); 
	dlg3.MoveWindow(&rs); 
	dlg4.MoveWindow(&rs);
	dlg5.MoveWindow(&rs);

	//分别设置隐藏和显示  
	dlg1.ShowWindow(true);
	dlg2.ShowWindow(false); 
	dlg3.ShowWindow(false); 
	dlg4.ShowWindow(false); 
	dlg5.ShowWindow(false);

	//设置默认的选项卡 
	m_tab.SetCurSel(0);

    CString m_good;
	CTime ct = CTime::GetCurrentTime();
	int hour = ct.GetHour();
	if(hour>=0 && hour<6)
		m_good="凌晨好，熬夜？强悍！注意休息！";
	else if(hour>=6 && hour<8)
		m_good="早上好，这个时候得看书啊！";
	else if(hour>=8 && hour<11)
		m_good="上午好，现在清净啊，呵呵！";
	else if(hour>=11 && hour<13)
		m_good="中午好，现在是休息时间咯！";
	else if(hour>=13 && hour<19)
		m_good="下午好，嘿嘿";
	else if(hour>=19)
		m_good="晚上好，别玩太晚了，早点睡觉lo！";

	notifydata.cbSize=sizeof(NOTIFYICONDATA);
	notifydata.hWnd=this->m_hWnd;
	notifydata.uCallbackMessage=WM_NOTIFYICON;
	notifydata.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
	notifydata.uID=IDI_ICON1;
	notifydata.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	strcpy_s(notifydata.szTip," Keybor for you");
	Shell_NotifyIconA(NIM_ADD,&notifydata);

	if(GetPrivateProfileIntA("System","Balloon",1,CAfx::filepath))
	{
		ShowBalloonTip("尊敬的客户"+m_good,"Keybor", 3000, 1);//弹出气泡提示
	}

//*******************************获取对话框坐标*********************************//
	RECT rect;
	rect.left=GetPrivateProfileIntA("System","PosX",0,CAfx::filepath);
	rect.top=GetPrivateProfileIntA("System","PosY",0,CAfx::filepath);
	rect.right=rect.left+473;
	rect.bottom=rect.top+362;
	MoveWindow(&rect);

    UpdateWindow();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}