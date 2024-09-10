BOOL CBookTicketsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CRect tabRect;                                    //标签控件客户区的位置和大小

	m_tab.InsertItem(0, L"预售机票");
	m_tab.InsertItem(1, L"个人信息");
	if (info.user == 'e')
		m_tab.InsertItem(2, L"票务管理");
	//m_tab.InsertItem(3, L"航班管理");
	//m_tab.InsertItem(4, L"人员管理");

	m_book.Create(IDD_BOOK, &m_tab);
	m_info.Create(IDD_INFO, &m_tab);
	if (info.user == 'e')
		m_manage.Create(IDD_MAN, &m_tab);

	//开始更改客户区大小
	int cx, cy;
	cx = GetSystemMetrics(SM_CXSCREEN) * 4 / 5;
	cy = GetSystemMetrics(SM_CYSCREEN) * 4 / 5;

	//设置客户区大小并忽略hWmndInsertAfter,x,y
	::SetWindowPos(this->m_hWnd, HWND_TOP, 0, 0, cx, cy, SWP_NOZORDER | SWP_NOMOVE);

	GetClientRect(&m_rect);							//获得当前整个工作区大小

	m_tab.MoveWindow(0, 0, cx, cy);					//改变tab控件的大小

	m_tab.GetClientRect(&tabRect);					// 获取标签控件客户区Rect 
													// 调整tabRect，使其覆盖范围适合放置标签页   
	tabRect.left += 1;
	tabRect.right -= 2;
	tabRect.top += 50;
	tabRect.bottom -= 1;

	m_book.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	m_info.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	if (info.user == 'e')
		m_manage.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);


	//设置m_book为默认选项卡
	m_tab.SetCurSel(0);

	CRect rect;
	GetWindowRect(&rect);
	listRect.AddTail(rect);                //对话框的区域

	CWnd* pWnd = GetWindow(GW_CHILD);      //获取子窗体

	while (pWnd)
	{
		pWnd->GetWindowRect(rect);         //子窗体的区域
		listRect.AddTail(rect);            //CList<CRect,CRect> m_listRect成员变量
		pWnd = pWnd->GetNextWindow();      //取下一个子窗体
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}