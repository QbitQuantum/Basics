void CSearchBar::OnMenuDropDown(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTOOLBAR nmtb = (LPNMTOOLBAR)pNMHDR;
	RECT rc;
	SendMessage(TB_GETRECT, nmtb->iItem, (LPARAM)&rc);
	::MapWindowPoints(m_hWnd, NULL, LPPOINT(&rc), 2);
	if (nmtb->iItem == ID_WEB_SEARCH)
	{
		HMENU pop = SearchPluginCollection.CreateSearchMenu();
		if (AppConfig.search_engine >= 0)
		{
			SetMenuDefaultItem(pop, AppConfig.search_engine, MF_BYPOSITION);
			CheckMenuItem(pop, AppConfig.search_engine, MF_BYPOSITION | MF_CHECKED);
		}
		UINT cmd = TrackPopupMenu(pop, TPM_RETURNCMD | TPM_RIGHTALIGN | TPM_TOPALIGN, rc.right, rc.bottom, 0, m_hWnd, NULL);
		DestroyMenu(pop);
		if (cmd > 0)
		{
			int idx = (int)cmd - CSearchPluginCollection::ID_SEARCHPLUGIN00;
			if (AppConfig.search_engine != idx)
			{
				AppConfig.search_engine = idx;
				UpdateBtn();
			}
		}
	}

}