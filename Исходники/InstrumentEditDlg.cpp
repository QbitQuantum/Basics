void CInstrumentEditDlg::InsertPane(CInstrumentEditPanel *pPanel, bool Show)
{
	CRect Rect, ParentRect;
	CTabCtrl *pTabControl = static_cast<CTabCtrl*>(GetDlgItem(IDC_INST_TAB));

	pPanel->SetInstrumentManager(m_pInstManager);		// // //

	pTabControl->GetWindowRect(&ParentRect);
	pTabControl->InsertItem(m_iPanels, pPanel->GetTitle());

	pPanel->Create(pPanel->GetIDD(), this);
	pPanel->GetWindowRect(&Rect);
	Rect.MoveToXY(ParentRect.left - Rect.left + DPI::SX(1), ParentRect.top - Rect.top + DPI::SY(21));
	Rect.bottom -= DPI::SY(2);
	Rect.right += DPI::SX(1);
	pPanel->MoveWindow(Rect);
	pPanel->ShowWindow(Show ? SW_SHOW : SW_HIDE);

	if (Show) {
		pTabControl->SetCurSel(m_iPanels);
		pPanel->SetFocus();
		m_pFocusPanel = pPanel;
	}

	m_pPanels[m_iPanels++] = pPanel;
}