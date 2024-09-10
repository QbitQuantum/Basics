//****************************************************************************************
BOOL CBCGPropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	BOOL bReposButtons = FALSE;

	const int nVertMargin = 5;
	const int nHorzMargin = 5;

	CWnd* pWndNavigator = InitNavigationControl ();

	CRect rectClient;
	GetClientRect (rectClient);

	if (m_wndTab.GetSafeHwnd () != NULL)
	{
		CTabCtrl* pTab = GetTabControl ();
		ASSERT_VALID (pTab);

		CRect rectTab;
		pTab->GetWindowRect (rectTab);
		ScreenToClient (rectTab);

		rectTab.InflateRect (2, 0);

		if (pTab->GetItemCount () > 0)
		{
			CRect rectTabsNew;
			m_wndTab.GetTabsRect (rectTabsNew);

			CRect rectTabsOld;
			pTab->GetItemRect (0, rectTabsOld);

			const int nOldHeight = rectTabsOld.Height ();
			const int nNewHeight = rectTabsNew.Height ();

			if (nNewHeight > nOldHeight)
			{
				rectClient.bottom += nNewHeight - nOldHeight + nVertMargin;
				rectTab.bottom += nNewHeight - nOldHeight;

				SetWindowPos (NULL, -1, -1,
					rectClient.Width (), rectClient.Height (),
					SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
			}
		}

		m_wndTab.MoveWindow (rectTab);

		pTab->ModifyStyle (WS_TABSTOP, 0);
		pTab->ShowWindow (SW_HIDE);

		if (pTab->GetItemCount () > 0)
		{
			m_wndTab.SetActiveTab (0);
		}

		bReposButtons = TRUE;
	}
	else if (pWndNavigator != NULL)
	{
		CTabCtrl* pTab = GetTabControl ();
		ASSERT_VALID (pTab);

		pTab->ModifyStyle (WS_TABSTOP, 0);

		CRect rectTabItem;
		pTab->GetItemRect (0, rectTabItem);
		pTab->MapWindowPoints (this, &rectTabItem);

		const int nTabsHeight = rectTabItem.Height () + nVertMargin;

		SetWindowPos (NULL, -1, -1, rectClient.Width () + m_nBarWidth,
			rectClient.Height () - nTabsHeight + 4 * nVertMargin,
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
		
		GetClientRect (rectClient);
		pTab->MoveWindow (m_nBarWidth, -nTabsHeight, rectClient.right, rectClient.bottom - 2 * nVertMargin);

		CRect rectTab;
		pTab->GetWindowRect (rectTab);
		ScreenToClient (rectTab);

		CRect rectNavigator = rectClient;
		rectNavigator.right = rectNavigator.left + m_nBarWidth;
		rectNavigator.bottom = rectTab.bottom;
		rectNavigator.DeflateRect (1, 1);

		pWndNavigator->SetWindowPos (&wndTop, 
							rectNavigator.left, rectNavigator.top,
							rectNavigator.Width (), 
							rectNavigator.Height (),
							SWP_NOACTIVATE);

		SetActivePage (GetActivePage ());

		bReposButtons = TRUE;
	}

	if (bReposButtons)
	{
		int ids[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP	};

		int nTotalButtonsWidth = 0;

		for (int iStep = 0; iStep < 2; iStep++)
		{
			for (int i = 0; i < sizeof (ids) / sizeof (ids [0]); i++)
			{
				CWnd* pButton = GetDlgItem (ids[i]);

				if (pButton != NULL)
				{
					if (ids [i] == IDHELP && (m_psh.dwFlags & PSH_HASHELP) == 0)
					{
						continue;
					}

					if (ids [i] == ID_APPLY_NOW && (m_psh.dwFlags & PSH_NOAPPLYNOW))
					{
						continue;
					}

					CRect rectButton;
					pButton->GetWindowRect (rectButton);
					ScreenToClient (rectButton);

					if (iStep == 0)
					{
						// Align buttons at the bottom
						pButton->SetWindowPos (&wndTop, rectButton.left, 
							rectClient.bottom - rectButton.Height () - nVertMargin, 
							-1, -1, SWP_NOSIZE | SWP_NOACTIVATE);

						nTotalButtonsWidth = rectButton.right;
					}
					else
					{
						// Right align the buttons
						pButton->SetWindowPos (&wndTop, 
							rectButton.left + rectClient.right - nTotalButtonsWidth - nHorzMargin,
							rectButton.top,
							-1, -1, SWP_NOSIZE | SWP_NOACTIVATE);
					}
				}
			}
		}
	}

	return bResult;
}