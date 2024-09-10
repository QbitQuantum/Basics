BOOL CMatrix428Dlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	CRect dlgRect;
	dlgRect.left = 0;
	dlgRect.top= 0;
	dlgRect.right = 800;
	dlgRect.bottom = 76;
	CWnd::SetWindowPos(NULL,0,0,dlgRect.Width(),dlgRect.Height(), SWP_NOZORDER);

	// 设置控件的位置和尺寸
	CWnd *pWnd;
	pWnd = GetDlgItem( IDC_BUTTON_MINMIZEBOX );    // 获取控件指针，IDC_BUTTON_MINMIZEBOX为控件ID号
	pWnd->MoveWindow( CRect(2,2,32,32) );	// 在窗口左上角显示一个宽32、高32的按钮控件

	pWnd = GetDlgItem( IDC_BUTTON_CLOSEBOX );
	pWnd->MoveWindow( CRect(36,2,68,32) );	// 两个按钮之间间距为2

	pWnd = GetDlgItem( IDC_STATIC_E428 );
	pWnd->MoveWindow( CRect(2,36,68,68) );	// 设置静态控件位置

	GetCurrentDirectory(500, CurrentPath);	// 获取当前路径

	LoadToolBar();
	return TRUE;  // return TRUE  unless you set the focus to a control
}