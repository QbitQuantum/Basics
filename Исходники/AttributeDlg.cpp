	LRESULT OnInitDialog(HWND /*wParam*/, LPARAM /*lParam*/)
	{
		CWaitCursor cursor;
		CenterWindow(GetParent());

		if ( !m_prompt.IsEmpty() )
		{
			SetWindowText(m_prompt);
		}

		CWindow wndPlaceholder = GetDlgItem(IDC_STATIC_PLACEHOLDER);
		CRect rc;
		wndPlaceholder.GetWindowRect(rc);
		ScreenToClient(rc);
		wndPlaceholder.DestroyWindow();
		m_view.Create(*this, rc);
		m_view.SetDlgCtrlID(IDC_STATIC_PLACEHOLDER);
		m_view.SetWindowPos(HWND_TOP, rc, 0);
		m_view.SendMessage(CWM_RESET);
		m_view.Select(m_attr);
		m_view.Invalidate();
		m_view.SetFocus();

		return TRUE;
	}