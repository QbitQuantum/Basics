ITSMenu& TrackListCtrl::GetInternalMenu(MenusEnum mnu)
{
	TRACEST(_T("TrackListCtrl::GetInternalMenu."), mnu);
	ASSERT(mnu < M_Last);
	PrgAPI* pAPI = PRGAPI();
	MenuManager* pMM = pAPI->GetMenuManager();
	if (m_pMenu[mnu] == NULL)
		m_pMenu[mnu] = pAPI->CreatePopupMenu();
	ITSMenu& curMenu = *m_pMenu[mnu];
	if (curMenu.GetInternalHandler() != NULL)
		return curMenu;
	curMenu.Create();
	switch (mnu)
	{
	case M_Main:
		//================= CONTEXT MENU TEMPLATE
		TCHAR bf[1000];
		_sntprintf(bf, 1000, _T("%s\t%s"), pAPI->GetString(IDS_PLAY), pAPI->GetString(IDS_KEYENTER));
		curMenu.AppendMenu(ITSMenu::MIT_String, MI_Play, bf, pAPI->GetIcon(ICO_Play16));
		_sntprintf(bf, 1000, _T("%s\t%s + %s"), pAPI->GetString(IDS_ENQUEUE), pAPI->GetString(IDS_KEYSHIFT), pAPI->GetString(IDS_KEYENTER));
		curMenu.AppendMenu(ITSMenu::MIT_String, MI_Enqueue, bf, pAPI->GetIcon(ICO_Add16));
		_sntprintf(bf, 1000, _T("%s\t%s + %s"), pAPI->GetString(IDS_INSERTAFTER), pAPI->GetString(IDS_KEYCTRL), pAPI->GetString(IDS_KEYENTER));
		curMenu.AppendMenu(ITSMenu::MIT_String, MI_InsertAfter, bf);
		curMenu.AppendMenu(ITSMenu::MIT_Separator, 0, NULL);
		_sntprintf(bf, 1000, _T("%s\t%s"), pAPI->GetString(IDS_LOCATEALBUM), pAPI->GetString(IDS_KEYHOME));
		curMenu.AppendMenu(ITSMenu::MIT_String, MI_LocateAlbum, bf, pAPI->GetIcon(ICO_Album16));
		break;
	default:
		ASSERT(0);
	}
	return curMenu;
}