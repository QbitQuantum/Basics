void CSampleConfigDlg::OnBnClickedCheckboxSettheoryconc()
{
	//“设置理论浓度复选框”单击响应函数
	int checkState = m_CheckSetThoeryConc.GetCheck();
	if(checkState == 1)
	{
		checkState = 1;
		CWnd * pWnd = GetDlgItem(IDC_Title_StartConc);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_Title_Increament);
		pWnd->EnableWindow(TRUE);
		m_ctrlEditStartConc.EnableWindow(TRUE);
		m_ctrlSpinBtnStartConc.EnableWindow(TRUE);
		m_ctrlEditIncreament.EnableWindow(TRUE);
		m_ctrlSpinBtnIncreament.EnableWindow(TRUE);
		_AutoFillThoeryConc(true);
	}
	else
	{
		checkState = 0;
		CWnd * pWnd = GetDlgItem(IDC_Title_StartConc);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_Title_Increament);
		pWnd->EnableWindow(FALSE);
		m_ctrlEditStartConc.EnableWindow(FALSE);
		m_ctrlSpinBtnStartConc.EnableWindow(FALSE);
		m_ctrlEditIncreament.EnableWindow(FALSE);
		m_ctrlSpinBtnIncreament.EnableWindow(FALSE);
		_AutoFillThoeryConc(false);
	}
	m_ctrlConfigList.RedrawAllItems();
}