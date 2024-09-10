BOOL titleShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CWnd *pWnd = this->GetDlgItem( IDC_SHOWTITLE_STATICSHOW ); 
	pWnd->SetWindowTextW ( _T("") ); 
	CString showAllTitle, showTitle; 
	TitleTemplateDlg *ttdlg = ( TitleTemplateDlg *)this->m_pParentWnd; 
	for ( int i=0; i< ttdlg->getTitleSize(); i++ )
	{
		ttdlg->changeTitleToShow( i ,showTitle ); 
		for ( int j=i; j>0; j-- )
			showAllTitle += _T('  '); 
		showAllTitle +=  showTitle ;
		showAllTitle.AppendFormat( _T(" （第%d级标题）"), i+1 );
		showAllTitle += _T("\r\n"); 
	}
	pWnd->SetWindowTextW ( showAllTitle ); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}