BOOL DlgAnimationExporterMain::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);//
	// TODO:  在此添加额外的初始化

	char* szItemName[] = {" 骨骼框架", "动画序列", "纹理", "模型信息", "5"};
	
	for (int i = 0; i < MAX_PAGE; i++)
	{
		m_tabExporter.InsertItem(i, szItemName[i]);
	}

	RECT rc;
	m_tabExporter.GetClientRect(&rc);
	ClientToScreen(&rc);
	RECT rcDlg = {0,0,0,0};
	//GetClientRect(&rcDlg);
	//GetWindowRect(&rcDlg);
	//ClientToScreen(&rcDlg);
	RECT rcw = {rcDlg.left + rc.left, rcDlg.top + rc.top + 21, rcDlg.left + rc.right, rcDlg.top + rc.bottom};
	CDialog* pDlg = NULL;
	int iDlgNum = 0;
	CREATE_PAGE(IDD_DIALOG1, CDlgExporterPage1);
	pDlg->ShowWindow(SW_SHOW);
	CREATE_PAGE(IDD_DIALOG2, CDlgExporterPage2);
	CREATE_PAGE(IDD_DIALOG3, CDlgExportPage3);
	CREATE_PAGE(IDD_DIALOG4, CDlgExportPage4);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}