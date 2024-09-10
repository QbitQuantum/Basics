// CArbiReportDlg 消息处理程序
void CArbiReportDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CDialog::OnSize(nType, cx, cy);
	if (GetSafeHwnd())
	{
		CEdit * peditLog = (CEdit*)GetDlgItem(IDC_EDIT_LOG);
		if (peditLog->GetSafeHwnd())
		{
			CRect rect(0,0,cx,cy);
			peditLog->MoveWindow(&rect);
		}
	}
}