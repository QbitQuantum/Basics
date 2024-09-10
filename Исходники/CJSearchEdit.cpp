BOOL CEditButton::Create(CWnd* pWnd, SEARCH_TYPE eType, UINT nMenu)
{
	ASSERT(eType != -1);
	ASSERT_VALID(pWnd);
	m_eType = eType;
	m_nMenu = nMenu;
	m_pWnd = pWnd;
	CWnd* pWndParent = m_pWnd->GetParent();
	ASSERT_VALID(pWndParent);
	
	CRect rc;
	m_pWnd->GetWindowRect(&rc);
	m_pWnd->SetWindowPos(NULL, 0, 0, rc.Width()-23,
		rc.Height(), SWP_NOZORDER|SWP_NOMOVE);
	pWndParent->ScreenToClient(&rc);
	rc.left = rc.right-18;

	DWORD dwStyle = WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_CENTER|BS_VCENTER;
	switch (m_eType)
	{
	case SEARCH_DIRECTORY:
	case SEARCH_FILE:
		{
			if (CButton::Create(_T("..."), dwStyle, rc,
				pWndParent, GetNextID(pWndParent)))
			{
				SetWindowPos(m_pWnd, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
				EnableWindow(m_pWnd->IsWindowEnabled());
				SetFont(&m_Font);
				return TRUE;
			}
		}

	case SEARCH_POPUP:
		{
			if (CButton::Create(_T("..."), dwStyle|BS_ICON, rc,
				pWndParent, GetNextID(pWndParent)))
			{
				SetWindowPos(m_pWnd, 0,0,0,0, SWP_NOSIZE|SWP_NOMOVE);
				EnableWindow(m_pWnd->IsWindowEnabled());
				SetFont(&m_Font);

				CImageList imageList;
				CBitmap    bitmap;

				bitmap.LoadBitmap(IDB_BTN_ARROW);
				imageList.Create(15, 17, ILC_COLORDDB|ILC_MASK, 1, 1);
				imageList.Add(&bitmap, RGB(255,0,255));

				SetIcon(imageList.ExtractIcon(0));

				imageList.Detach();
				bitmap.Detach();
				return TRUE;
			}
		}
	}

	return FALSE;
}