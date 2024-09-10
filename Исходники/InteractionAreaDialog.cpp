void CInteractionAreaDialog::CreateSlidePopup(int nAction, int nButtonId, int nEditId)
{
	CRect rcButton;
	CWnd *pWndButton = GetDlgItem(nButtonId);

	pWndButton->GetClientRect(rcButton);
	pWndButton->ClientToScreen(&rcButton);

	m_wndMenu.CreatePopupMenu();

	CArray<CPage *, CPage *> caPages;
	m_pEditorDoc->project.GetPages(caPages, 0, m_pEditorDoc->m_docLengthMs);
	for (int i = 0; i < caPages.GetSize(); ++i)
	{
		CString csPageTitle;
		csPageTitle = caPages[i]->GetTitle();
		m_wndMenu.AppendMenu(MF_STRING, i+1, csPageTitle);
	}
   
	BOOL bRet = m_wndMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, rcButton.left, rcButton.bottom, this);

	CWnd *pEdit = GetDlgItem(nEditId);
	// if bRet is zero the menu was cancelled 
	// or an error occured
	if (bRet != 0)
	{
		CString csItem;
		m_wndMenu.GetMenuString(bRet, csItem, MF_BYCOMMAND);
		pEdit->SetWindowText(csItem);
		m_nMarkOrPageId[nAction] = caPages[bRet-1]->GetJumpId();
	}

	caPages.RemoveAll();
	m_wndMenu.DestroyMenu();
}