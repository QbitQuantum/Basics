void CDlgObjectManager::OnNMRclickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	if( m_pDoc == NULL)	return;

	CMyObject*	pObj;
	HTREEITEM	hI;
	CPoint		pt, ptMenu;
	UINT		uFlags;
	CRect		rc;

	GetCursorPos(&pt);
	ptMenu=pt;
	m_tree.GetWindowRect(&rc);
	pt.x -= rc.left;
	pt.y -= rc.top;
	hI = m_tree.HitTest( pt, &uFlags);
	pObj = FindObj(hI);
	if(pObj && (uFlags==TVHT_ONITEMLABEL) ){
		m_hI = hI;
		CMenu menu;
		CRect wndRect;
		this->GetWindowRect(wndRect);
		menu.LoadMenu(IDR_MENU_OBJMNG);
		CMenu* subMenu = menu.GetSubMenu(0);
		subMenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON , ptMenu.x, ptMenu.y, this);
	}

	CBody* pBd;
	pBd = (CBody*) FindBody(hI);
	if(pBd && (uFlags==TVHT_ONITEMLABEL) ) {
		m_hI = hI;
		CMenu menu;
		CRect wndRect;
		this->GetWindowRect(wndRect);
		menu.LoadMenu(IDR_MENU_OBJMNG);
		CMenu* subMenu = menu.GetSubMenu(0);
		subMenu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON , ptMenu.x, ptMenu.y, this);
	}

	*pResult = 0;
}