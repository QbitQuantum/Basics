LRESULT CFunctionPage::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (wParam == SIZE_RESTORED)
	{
		CRect rc, rc2;
		CWindow wnd = GetDlgItem(IDC_COMBO_CLASSES);
		wnd.GetWindowRect(rc);
		ScreenToClient(rc);
		CSize NewSize(LOWORD(lParam), HIWORD(lParam));
		
		CRect CheckRc(0, 0, 1,12);
		MapDialogRect(CheckRc);
		rc2.left = 0;
		rc2.right = NewSize.cx;
		rc2.top = rc.bottom + CheckRc.Height();
		rc2.bottom = NewSize.cy;
		m_SplitMessages.MoveWindow(rc2);

		if (!m_bShowWindow && lParam)
		{
			m_bShowWindow = true;
			m_SplitMessages.SetSplitterPos(m_WindowSettings.m_MesSpitPos);
			m_SplitFunctions.SetSplitterPos(m_WindowSettings.m_FuncSplitPos);
		}
	}
	return 0;
}