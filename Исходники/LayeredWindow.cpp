void CLayeredDialog::SetLayeredDialog( HINSTANCE hInstance,LPCTSTR lpResource,CSize szSizeLT,CSize szSizeRB )
{
	//设置窗口
	RemoveBorder();

	//加载资源
	m_ImageBack.LoadImage(hInstance,lpResource);

	//设置大小
	CSize SizeWindow(m_ImageBack.GetWidth(),m_ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//获取窗口
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//计算位置
	CRect rcUnLayered;
	rcUnLayered.top=szSizeLT.cy;
	rcUnLayered.left=szSizeLT.cx;
	rcUnLayered.right=rcWindow.Width()-szSizeRB.cx;
	rcUnLayered.bottom=rcWindow.Height()-szSizeRB.cy;

	//设置区域
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(rcUnLayered.left,rcUnLayered.top,rcUnLayered.right+1,rcUnLayered.bottom+1,0,0);

	//设置区域
	SetWindowRgn(RgnWindow,FALSE);

	//分层窗口
	m_LayeredWindow.CreateLayered(this,rcWindow);
	m_LayeredWindow.InitLayeredArea(m_ImageBack,255,rcUnLayered,CPoint(0,0),false);
}