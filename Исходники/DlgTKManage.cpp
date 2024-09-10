bool CDlgTKManage::InitGraphList()
{
	CWnd* pWnd = GetDlgItem(IDC_STATIC_BMP);
	if (NULL == pWnd)
	{
		return false;
	}

	DWORD dwStyle = pWnd->GetStyle();
	CRect rc;
	pWnd->GetWindowRect(rc);
	ScreenToClient(rc);

	pWnd->DestroyWindow();
	if (!m_gsView.Create(rc, this, IDC_STATIC_BMP, dwStyle))
	{
		return false;
	}

	m_gsView.SetCurDatabase(m_pDb);
	m_gsView.ShowItemCaption(false);
	m_gsView.EnableDefault(false);
	m_gsView.EnableSel(true);
	m_gsView.SetLayer(1, 1);

	m_gsView.InsertItem(0, ACDB_MODEL_SPACE);
	return true;
}