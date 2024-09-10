ITSMenu& WebPane::GetInternalMenu(MenusEnum mnu)
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
				(INT)pMM->GetMenu(MenuManager::MNU_ArtistServices).GetInternalHandler(), (LPTSTR)pAPI->GetString(IDS_ARTIST));

			curMenu.AppendMenu(ITSMenu::MIT_Menu, 
				(INT)pMM->GetMenu(MenuManager::MNU_AlbumServices).GetInternalHandler(), (LPTSTR)pAPI->GetString(IDS_ALBUM));

			curMenu.AppendMenu(ITSMenu::MIT_Menu, 
				(INT)pMM->GetMenu(MenuManager::MNU_TrackServices).GetInternalHandler(), (LPTSTR)pAPI->GetString(IDS_TITLE));
			
			curMenu.AppendMenu(ITSMenu::MIT_Separator, NULL, NULL);
			
			curMenu.AppendMenu(ITSMenu::MIT_String, MI_SyncWithSectionChanger, (LPTSTR)pAPI->GetString(IDS_SYNCWITHSECTIONS));
			curMenu.AppendMenu(ITSMenu::MIT_String, MI_SyncWithTracksChanger, (LPTSTR)pAPI->GetString(IDS_SYNCWITHTRACKS));
			curMenu.AppendMenu(ITSMenu::MIT_String, MI_SyncWithPlayer, (LPTSTR)pAPI->GetString(IDS_SYNCWITHPLAYER));
			
			curMenu.AppendMenu(ITSMenu::MIT_Separator, NULL, NULL);
			
			curMenu.AppendMenu(ITSMenu::MIT_String, MI_UseAsWebViewer, (LPTSTR)pAPI->GetString(IDS_WEBVIEWER));
		}
		break;
	default:
		ASSERT(0);
	}
	return curMenu;
}