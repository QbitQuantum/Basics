void CXTPSkinObjectSpin::OnDraw(CDC* pDC)
{

	CRect rcClient;
	GetClientRect(&rcClient);

	CXTPBufferDC dcMem(*pDC, rcClient);

	DWORD dwStyle = GetStyle();

	int nLower = 0, nUpper = 0;
	SendMessage(UDM_GETRANGE32, (WPARAM) &nLower, (LPARAM) &nUpper);
	BOOL bEnabled = (nUpper != nLower) && IsWindowEnabled();
	HWND hWndBuddy = (HWND)SendMessage(UDM_GETBUDDY);

	if (hWndBuddy && bEnabled && !::IsWindowEnabled(hWndBuddy))
		bEnabled = FALSE;

	dcMem.FillSolidRect(rcClient, GetColor(COLOR_3DFACE));


	CRect rcBtn = rcClient;

	CXTPSkinManagerClass* pClassSpin = GetSkinClass();


	if (hWndBuddy && GetWindowLong(hWndBuddy, GWL_EXSTYLE) & WS_EX_CLIENTEDGE)
	{
		dcMem.FillSolidRect(rcClient, GetColor(COLOR_WINDOW));

		if (dwStyle & UDS_ALIGNRIGHT)
		{
			rcBtn.DeflateRect(0, 1, 1, 1);

			CXTPSkinManagerClass* pClassEdit = GetSkinManager()->GetSkinClass(this, _T("EDIT"));
			COLORREF clrBorderColor = pClassEdit->GetThemeColor(0, 0, TMT_BORDERCOLOR);
			dcMem.Draw3dRect(rcClient, clrBorderColor, clrBorderColor);
			dcMem.FillSolidRect(rcClient.left, rcClient.top + 1, 1, rcClient.Height() - 2, GetColor(COLOR_WINDOW));
		}
		else if (dwStyle & UDS_ALIGNLEFT)
		{
			rcBtn.DeflateRect(1, 1, 0, 1);

			CXTPSkinManagerClass* pClassEdit = GetSkinManager()->GetSkinClass(this, _T("EDIT"));
			COLORREF clrBorderColor = pClassEdit->GetThemeColor(0, 0, TMT_BORDERCOLOR);
			dcMem.Draw3dRect(rcClient, clrBorderColor, clrBorderColor);
			dcMem.FillSolidRect(rcClient.right - 1, rcClient.top + 1, 1, rcClient.Height() - 2, GetColor(COLOR_WINDOW));
		}
	}

	RECT rc = rcBtn;

	if (dwStyle & UDS_HORZ)
	{
		int nState = DNHZS_NORMAL;
		if (!bEnabled)
			nState = DNHZS_DISABLED;
		else if (m_nPressedButton == UD_HITDOWN && m_nHotButton == UD_HITDOWN)
			nState = DNHZS_PRESSED;
		else if ((m_nHotButton == UD_HITDOWN || m_nPressedButton == UD_HITDOWN)  && (m_nPressedButton != UD_HITUP))
			nState = DNHZS_HOT;

		rc.right = (rcBtn.right + rcBtn.left) / 2;
		pClassSpin->DrawThemeBackground(&dcMem, SPNP_DOWNHORZ, nState, &rc);


		nState = UPHZS_NORMAL;
		if (!bEnabled)
			nState = UPHZS_DISABLED;
		else if (m_nPressedButton == UD_HITUP && m_nHotButton == UD_HITUP)
			nState = UPHZS_PRESSED;
		else if ((m_nHotButton == UD_HITUP || m_nPressedButton == UD_HITUP) && (m_nPressedButton != UD_HITDOWN))
			nState = UPHZS_HOT;

		rc.left = rcBtn.right - (rc.right - rc.left); // handles odd-x case, too
		rc.right = rcBtn.right;
		pClassSpin->DrawThemeBackground(&dcMem, SPNP_UPHORZ, nState, &rc);

	}
	else
	{
		int nState = UPS_NORMAL;
		if (!bEnabled)
			nState = UPS_DISABLED;
		else if (m_nPressedButton == UD_HITUP && m_nHotButton == UD_HITUP)
			nState = UPS_PRESSED;
		else if ((m_nHotButton == UD_HITUP || m_nPressedButton == UD_HITUP) && (m_nPressedButton != UD_HITDOWN))
			nState = UPS_HOT;

		rc.bottom = (rcBtn.bottom + rcBtn.top) / 2;

		pClassSpin->DrawThemeBackground(&dcMem, SPNP_UP, nState, &rc);

		nState = DNS_NORMAL;
		if (!bEnabled)
			nState = DNS_DISABLED;
		else if (m_nPressedButton == UD_HITDOWN && m_nHotButton == UD_HITDOWN)
			nState = DNS_PRESSED;
		else if ((m_nHotButton == UD_HITDOWN || m_nPressedButton == UD_HITDOWN)  && (m_nPressedButton != UD_HITUP))
			nState = DNS_HOT;

		rc.top = rcBtn.bottom - (rc.bottom - rc.top); // handles odd-y case, too
		rc.bottom = rcBtn.bottom;
		pClassSpin->DrawThemeBackground(&dcMem, SPNP_DOWN, nState, &rc);
	}
}