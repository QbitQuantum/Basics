void CSearchInfo::OnRclickListResults(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMHDR Control = (LPNMHDR) pNMHDR;		// stay compatable with IE 3.0!
	
	int nItem = m_lstResults.GetSelectionMark();
	if (0 > nItem || nItem > m_lstResults.GetItemCount() - 1)
		return;

    CMenu menu;
    menu.LoadMenu(IDR_SEARCHEX_RCLICK);
    CMenu *pMenu = menu.GetSubMenu(0);
    ASSERT(pMenu != NULL);

    // Display and track the popup menu
    CPoint point;
    GetCursorPos(&point);

	int res = pMenu->TrackPopupMenu( (TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD),
                 point.x, point.y, this);

	POSITION pos = m_lstResults.GetFirstSelectedItemPosition();
	
	switch(res)
	{
	case ID_LSTSEARCHEX_BLOCK:
		if(pos)
		{
			pos   = m_lstResults.GetFirstSelectedItemPosition();
			nItem = m_lstResults.GetNextSelectedItem(pos);

			ResultHost* p = (ResultHost*) m_lstResults.GetItemData(nItem);


			// Dispaly Preferences, sharing tab
			m_pDoc->m_nLastPref = PREF_SEARCHBLOCK;
			
			CPrefDialog PrefDlg("Preferences");
		
			PrefDlg.m_TabSearchBlock->m_SearchExInit = IPtoStr(p->Host);
			PrefDlg.DoModal();

			m_pView->OnChecksScreen();
		}

		break;
	}
		
	*pResult = 0;
}