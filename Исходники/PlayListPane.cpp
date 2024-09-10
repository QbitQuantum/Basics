ITSMenu& PlayListPane::GetInternalMenu(MenusEnum mnu)
{
	TRACEST(_T("PlayListPane::GetMenu."), mnu);
	ASSERT(mnu < M_Last);
	PrgAPI* pAPI = PRGAPI();
	if (m_pMenu[mnu] == NULL)
		m_pMenu[mnu] = pAPI->CreatePopupMenu();
	ITSMenu& curMenu = *m_pMenu[mnu];
	if (curMenu.GetInternalHandler() != NULL)
		return curMenu;
	curMenu.Create();
	switch (mnu)
	{
	case M_Main:
		{
			MenuManager* pMM = pAPI->GetMenuManager();
			curMenu.AppendMenu(ITSMenu::MIT_Menu, 
				(INT)pMM->GetMenu(MenuManager::MNU_PlayListModes).GetInternalHandler(), (LPTSTR)pAPI->GetString(IDS_MODE));
			
			curMenu.AppendMenu(ITSMenu::MIT_Menu, 
				(INT)pMM->GetMenu(MenuManager::MNU_PlayListSerialization).GetInternalHandler(), (LPTSTR)pAPI->GetString(IDS_PLAYLIST));

			curMenu.AppendMenu(ITSMenu::MIT_Separator, NULL, NULL);
			curMenu.AppendMenu(ITSMenu::MIT_String, MI_ShowNumbers, (LPTSTR)pAPI->GetString(IDS_SHOWNUMBERS));
		}
		break;
	default:
		ASSERT(0);
	}
	return curMenu;
}