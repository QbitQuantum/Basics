void CHistTracksListCtrl::InitMainMenu(BCMenu& menu)
{
	int a = GetSelectedCount();
	menu.EnableMenuItem(ACMD_OpenFolder, a == 1 ? MF_ENABLED : MF_GRAYED);
	menu.EnableMenuItem(ACMD_History,  a == 1 ? MF_ENABLED : MF_GRAYED);

}