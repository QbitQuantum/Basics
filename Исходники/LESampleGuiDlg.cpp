BOOL CLESampleGuiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_DEVICE_LIST);
	lst->ModifyStyle( 0, LVS_REPORT );               // 报表模式  
	lst->SetExtendedStyle(lst->GetExtendedStyle() 
		| LVS_EX_GRIDLINES 
		| LVS_EX_FULLROWSELECT);  

	lst->InsertColumn(0,_T("Address")); 
	lst->InsertColumn(1,_T("Device Name"));  

	CRect rect;
	lst->GetClientRect(rect); //获得当前客户区信息
	lst->SetColumnWidth(0, rect.Width() / 2); //设置列的宽度。  
	lst->SetColumnWidth(1, rect.Width() / 2);  

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}