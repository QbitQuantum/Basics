void CVCDlg::InitPropList()
{
	CRect rcPropList;
	CWnd* pWnd = GetDlgItem(IDC_OUTPUT_PROP_LIST);
	ASSERT(pWnd != NULL);
	pWnd->GetWindowRect(&rcPropList);
	ScreenToClient(&rcPropList);
	
	pWnd->DestroyWindow();
	
	if(!m_propListMgr.CreatePropList(rcPropList, this, IDC_OUTPUT_PROP_LIST))
	{
		return;
	}
}