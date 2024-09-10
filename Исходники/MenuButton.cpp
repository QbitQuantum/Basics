void CMenuButton::OnShowMenu()
{
	m_bRealMenuIsActive = true;

	// Begin CMFCMenuButton::OnShowMenu()
	if (m_hMenu == NULL || m_bMenuIsActive)
	{
		return;
	}

	CRect rectWindow;
	GetWindowRect(rectWindow);

	int x, y;

	if (m_bRightArrow)
	{
		x = rectWindow.right;
		y = rectWindow.top;
	}
	else
	{
		x = rectWindow.left;
		y = rectWindow.bottom;
	}

	if (m_bStayPressed)
	{
		m_bPushed = TRUE;
		m_bHighlighted = TRUE;
	}

	m_bMenuIsActive = TRUE;
	Invalidate();

	TPMPARAMS params;
	params.cbSize = sizeof(TPMPARAMS);
	params.rcExclude = rectWindow;
	m_nMenuResult = ::TrackPopupMenuEx(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD | TPM_VERTICAL, x, y, GetSafeHwnd(), &params);

	CWnd* pParent = GetParent();

#ifdef _DEBUG
	if ((pParent->IsKindOf(RUNTIME_CLASS(CDialog))) && (!pParent->IsKindOf(RUNTIME_CLASS(CDialogEx))))
	{
		TRACE(_T("CMFCMenuButton parent is CDialog, should be CDialogEx for popup menu handling to work correctly.\n"));
	}
#endif

	if (m_nMenuResult != 0)
	{
		//-------------------------------------------------------
		// Trigger mouse up event(to button click notification):
		//-------------------------------------------------------
		if (pParent != NULL)
		{
			pParent->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
		}
	}

	m_bPushed = FALSE;
	m_bHighlighted = FALSE;
	m_bMenuIsActive = FALSE;

	Invalidate();
	UpdateWindow();

	if (m_bCaptured)
	{
		ReleaseCapture();
		m_bCaptured = FALSE;
	}
	// End CMFCMenuButton::OnShowMenu()

	m_bRealMenuIsActive = false;
}