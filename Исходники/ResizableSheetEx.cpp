void CResizableSheetEx::PresetLayout()
{
	if (IsWizard() || IsWizard97())	// wizard mode
	{
		// hide tab control
		GetTabControl()->ShowWindow(SW_HIDE);

		AddAnchor(ID_WIZLINE, BOTTOM_LEFT, BOTTOM_RIGHT);

		if (IsWizard97())	// add header line for wizard97 dialogs
			AddAnchor(ID_WIZLINEHDR, TOP_LEFT, TOP_RIGHT);
	}
	else	// tab mode
	{
		AddAnchor(AFX_IDC_TAB_CONTROL, TOP_LEFT, BOTTOM_RIGHT);
	}

	// add a callback for active page (which can change at run-time)
	m_nCallbackID = AddAnchorCallback();

	// use *total* parent size to have correct margins
	CRect rectPage, rectSheet;
	GetTotalClientRect(&rectSheet);

	GetActivePage()->GetWindowRect(&rectPage);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rectPage, 2);

	// pre-calculate margins
	m_sizePageTL = rectPage.TopLeft() - rectSheet.TopLeft();
	m_sizePageBR = rectPage.BottomRight() - rectSheet.BottomRight();

	// add all possible buttons, if they exist
	for (int i = 0; i < _propButtonsCount; i++)
	{
		CButton* dlgBtn = reinterpret_cast<CButton*>(GetDlgItem(_propButtons[i]));
		if (dlgBtn != NULL)
		{
			CRect rcBtn;
			CString sBtn;

			dlgBtn->GetWindowRect(rcBtn);
			ScreenToClient(rcBtn);

			HBITMAP hBmp = NULL;
			switch(_propButtons[i])
			{
			case ID_WIZBACK:
				dlgBtn->SetWindowPos(NULL, rcBtn.left - 16, rcBtn.top - 8, rcBtn.Width(), rcBtn.Height() + 4, SWP_NOZORDER | SWP_NOREDRAW);
				sBtn.LoadString(IDS_BACK);
				//sBtn.Insert(0, _T("  "));
				dlgBtn->SetWindowText(sBtn);
				m_BtnNavBack.SubclassDlgItem(_propButtons[i], this);
				m_BtnNavBack.SetIcon(IDI_ICON_NAV_BACK);

				rcBtn.right = rcBtn.Width() * 2 + 10;
				rcBtn.left = 5;
				rcBtn.top -= 10;
				rcBtn.bottom -= 3;

				m_BtnDonate.Create(_T("Help keep us strong!"), WS_CHILD | WS_VISIBLE | WS_GROUP, rcBtn, this, ID_WIZDONATE);
				m_BtnDonate.SetIcon(IDI_ICON_DONATE);
				m_BtnDonate.SetAlign(CButtonST::ST_ALIGN_HORIZ);
				m_BtnDonate.SetDisplayStyle(CButtonST::DISP_FLAT);
				m_BtnDonate.SetFont(GetFont(), FALSE);

				AddAnchor(ID_WIZDONATE, BOTTOM_LEFT);
				AddAnchor(_propButtons[i], BOTTOM_RIGHT);
				break;
			case ID_WIZNEXT:
				dlgBtn->SetWindowPos(NULL, rcBtn.left - 14, rcBtn.top - 8, rcBtn.Width(), rcBtn.Height() + 4, SWP_NOZORDER | SWP_NOREDRAW);
				sBtn.LoadString(IDS_NEXT);
				//sBtn.Append(_T("  "));
				dlgBtn->SetWindowText(sBtn);
				m_BtnNavNext.SubclassDlgItem(_propButtons[i], this);
				m_BtnNavNext.SetIcon(IDI_ICON_NAV_NEXT);
				m_BtnNavNext.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
				AddAnchor(_propButtons[i], BOTTOM_RIGHT);
				break;
			case IDCANCEL:
				dlgBtn->SetWindowPos(NULL, rcBtn.left - 14, rcBtn.top - 8, rcBtn.Width(), rcBtn.Height() + 4, SWP_NOZORDER | SWP_NOREDRAW);
				sBtn.LoadString(IDS_CANCEL);
				//sBtn.Append(_T("  "));
				dlgBtn->SetWindowText(sBtn);
				m_BtnNavCancel.SubclassDlgItem(_propButtons[i], this);
				m_BtnNavCancel.SetIcon(IDI_ICON_NAV_CANCEL);
				m_BtnNavCancel.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
				AddAnchor(_propButtons[i], BOTTOM_RIGHT);
				break;
			case ID_WIZFINISH:
				dlgBtn->SetWindowPos(NULL, rcBtn.left - 14, rcBtn.top - 8, rcBtn.Width(), rcBtn.Height() + 4, SWP_NOZORDER | SWP_NOREDRAW);
				sBtn.LoadString(IDS_FINISH);
				//sBtn.Append(_T("  "));
				dlgBtn->SetWindowText(sBtn);
				m_BtnNavFinish.SubclassDlgItem(_propButtons[i], this);
				m_BtnNavFinish.SetIcon(IDI_ICON_NAV_FINISH);
				m_BtnNavFinish.SetAlign(CButtonST::ST_ALIGN_HORIZ_RIGHT);
				AddAnchor(_propButtons[i], BOTTOM_RIGHT);
				break;
			}
		}
	}
}