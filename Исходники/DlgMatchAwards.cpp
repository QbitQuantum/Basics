BOOL CDlgMatchAwards::OnInitDialog()
{
	CDialog::OnInitDialog();

	//变量定义
	CPngImage ImageBack;

	//加载图片
	ImageBack.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME), TEXT("MATCH_AWARDS"));
	m_btCloseAwards.SetButtonImage(IDB_BT_CLOSE_AWARDS,GetModuleHandle(GAME_FRAME_DLL_NAME),false,false);
	m_btCloseAwards.SetWindowPos(NULL,ImageBack.GetWidth()-55,30,27,22,SWP_NOZORDER);

    SetWindowPos(NULL, 0,0,ImageBack.GetWidth(),ImageBack.GetHeight(),SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);
	CenterWindow();

	//获取窗口
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//计算位置
	CRect rcUnLayered;
	rcUnLayered.top=20;
	rcUnLayered.left=20;
	rcUnLayered.right=rcWindow.Width()-20;
	rcUnLayered.bottom=rcWindow.Height()-20;

	//设置大小
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());

	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(rcUnLayered.left,rcUnLayered.top,rcUnLayered.right+1,rcUnLayered.bottom+1,7,7);

	//设置区域
	SetWindowRgn(RgnWindow,FALSE);

	//分层窗口
	m_SkinLayered.CreateLayered(this,rcWindow);
	m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(7,7),false);

	return TRUE; 
}