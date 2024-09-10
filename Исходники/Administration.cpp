// CAdministration 訊息處理常式
BOOL CAdministration::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此加入額外的初始化
	//((CButton*)GetDlgItem(IDC_RAINEWOPERATOR))->SetCheck(TRUE);
	CHeaderCtrl *pHeaderCtrl;
	pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlUser.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlUser.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrlUser.InsertColumn(0, _T("編號"), LVCFMT_CENTER, 45, -1);
	m_ListCtrlUser.InsertColumn(1, _T("帳號"), LVCFMT_CENTER, 118, -1);
	m_ListCtrlUser.InsertColumn(2, _T("密碼"), LVCFMT_CENTER, 118, -1);
	m_ListCtrlUser.InsertColumn(3, _T("職位稱"), LVCFMT_CENTER, 60, -1);
	GetDlgItem(IDC_BTNADMINMODIFY)->EnableWindow(FALSE);//關閉修改
	GetDlgItem(IDC_BTNADMINDELETE)->EnableWindow(FALSE);//關閉刪除
	ReadAccountData();
	AccountListRefresh();
    ((CEdit*)GetDlgItem(IDC_EDITNEWUSERID))->SetCueBanner(_T("注意帳號不可重複"), true);
    ((CEdit*)GetDlgItem(IDC_EDITNEWPASSWORD))->SetCueBanner(_T("密碼請輸入六位以上"), true);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}