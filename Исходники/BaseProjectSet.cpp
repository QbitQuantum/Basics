BOOL CBaseProjectSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&fontTitle);
	GetDlgItem(IDC_STATIC_HEAD)->SetWindowText(strTitle);
	GetDlgItem(IDC_STATIC_CASH_STANDARD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_CASH_STANDARD)->ShowWindow(SW_SHOW);

	SetWindowText(strTitle);
	

	if( !CDialogMedXL::ReadName(strSql,combo1) ) {
		AfxMessageBox("读取数据出错!!!");
		return false;
	}

	if( flag == 1 ) { //新增



	}
	else if(flag == 2) { //修改
		combo1.SelectString(-1,str[0]);
		edit1.SetWindowText(str[2]);
		edit2.SetWindowText(str[3]);

		editPY.SetWindowText(str[4]);
		editCode.SetWindowText(str[5]);
		editStandardCash.SetWindowText(str[6]);
		

	}
	else return false;

	CenterWindow();
	AnimateWindow(m_hWnd,300,AW_SLIDE|AW_HOR_POSITIVE);
	Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}