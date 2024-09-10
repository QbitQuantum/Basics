void	CDLListWindow::OnClose()
{
	/* 設定を保存する */
	CIniFileO	pr(CDLOptions::s_DLIniFilePath, _T("DLList"));
	
	CRect rc;
	GetWindowRect(&rc);
	pr.SetValue(rc.top, _T("top"));
	pr.SetValue(rc.left, _T("left"));
	pr.SetValue(rc.right, _T("right"));
	pr.SetValue(rc.bottom, _T("bottom"));

	pr.SetValue(m_cmbParallelDL.GetCurSel(), _T("ParallelDL"));

	pr.SetValue(m_DLList.GetColumnWidth(0), _T("ColumnWidthURL"));

	CString strPath = MtlGetWindowText(m_cmbDLFolder);
	CDLOptions::_SavePathHistory(strPath, CDLOptions::s_vecImageDLFolderHistory);

	pr.SetValue(m_cmbDLOption.GetCurSel(), _T("DLOption"));

	RevokeDragDrop();

	CMessageLoop *pLoop = _Module.GetMessageLoop();
	pLoop->RemoveMessageFilter(this);

	DestroyWindow();
}