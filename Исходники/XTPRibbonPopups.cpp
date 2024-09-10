	virtual void OnClick(BOOL /*bKeyboard  = FALSE */, CPoint /*pt  = CPoint */)
	{
		if (GetKeyState(VK_LBUTTON) >= 0)
			return;

		m_bPressed = TRUE;

		CXTPRibbonScrollableBar* pScrollableBar = GetScrollableBar(m_pParent);

		pScrollableBar->OnGroupsScroll(m_bScrollLeft);

		int cmsTimer = GetDoubleClickTime() * 4 / 5;
		m_pParent->SetTimer(IDSYS_SCROLL, cmsTimer, NULL);
		BOOL bFirst = TRUE;

		m_pParent->SetCapture();

		while (::GetCapture() == m_pParent->GetSafeHwnd() && IsVisible())
		{
			MSG msg;

			if (!::GetMessage(&msg, NULL, 0, 0))
			{
				AfxPostQuitMessage((int)msg.wParam);
				break;
			}

			if (msg.message == WM_TIMER && msg.wParam == IDSYS_SCROLL)
			{
				pScrollableBar->OnGroupsScroll(m_bScrollLeft);

				if (bFirst)
				{
					cmsTimer = GetDoubleClickTime() / 10;
					m_pParent->SetTimer(IDSYS_SCROLL, cmsTimer, NULL);
				}
				bFirst = FALSE;
			}
			else if (msg.message == WM_LBUTTONUP)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		ReleaseCapture();
		m_pParent->KillTimer(IDSYS_SCROLL);

		m_bPressed = FALSE;
		if (!IsVisible()) m_bSelected = FALSE;
		RedrawParent(FALSE);
	}