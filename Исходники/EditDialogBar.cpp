BOOL CEditDialogBar::OnInitDialogBar()
{
	CRect rect;
	GetWindowRect (rect);

	m_szWindow = rect.Size ();

	int count = (int)m_ResizeInfo.GetSize ();
	for (int i = 0; i < count; i++)
	{
		XResizeInfo& ri = m_ResizeInfo[i];

		CWnd* pWnd = GetDlgItem (ri.m_id);
		ASSERT_VALID (pWnd);

		pWnd->GetWindowRect (ri.m_rectInit);
		ScreenToClient (ri.m_rectInit);
	}

	return TRUE;
}