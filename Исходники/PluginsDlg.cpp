void CPluginsDlg::OnRClickPluginsList(NMHDR* pNMHDR, LRESULT* pResult)
{
	DWORD dwID = GetSelectedPluginID();
	KP_PLUGIN_INSTANCE *p = m_pPiMgr->GetPluginByID(dwID);

	UNREFERENCED_PARAMETER(pNMHDR);

	*pResult = 0;

	POINT pt;
	GetCursorPos(&pt);

	m_popmenu.LoadMenu(IDR_PLUGINS_MENU);

	m_popmenu.SetMenuDrawMode(BCMENU_DRAWMODE_XP); // <<<!=>>> BCMENU_DRAWMODE_ORIGINAL
	m_popmenu.SetSelectDisableMode(FALSE);
	m_popmenu.SetXPBitmap3D(TRUE);
	m_popmenu.SetBitmapBackground(RGB(255, 0, 255));
	m_popmenu.SetIconSize(16, 16);

	m_popmenu.LoadToolbar(IDR_INFOICONS, IDB_INFOICONS_EX);

	BCMenu* psub = NewGUI_GetBCMenu(m_popmenu.GetSubMenu(0));
	if(psub == NULL) { ASSERT(FALSE); psub = &m_popmenu; }

	// psub->ModifyODMenu(NULL, (UINT)ID_PLUGIN_ENABLE, m_pImgList, 2);
	// psub->ModifyODMenu(NULL, (UINT)ID_PLUGIN_DISABLE, m_pImgList, 45);
	psub->ModifyODMenu(NULL, (UINT)ID_PLUGIN_CONFIG, m_pImgList, 21);
	psub->ModifyODMenu(NULL, (UINT)ID_PLUGIN_ABOUT, m_pImgList, 22);

	CPwSafeDlg::_TranslateMenu(psub, FALSE, NULL);

	if(p != NULL)
	{
		// if(p->bEnabled == FALSE)
		// {
		//	psub->EnableMenuItem(ID_PLUGIN_DISABLE, MF_BYCOMMAND | MF_GRAYED);
		//	psub->EnableMenuItem(ID_PLUGIN_CONFIG, MF_BYCOMMAND | MF_GRAYED);
		//	psub->EnableMenuItem(ID_PLUGIN_ABOUT, MF_BYCOMMAND | MF_GRAYED);
		// }
		// else psub->EnableMenuItem(ID_PLUGIN_ENABLE, MF_BYCOMMAND | MF_GRAYED);

		if(p->hinstDLL == NULL)
		{
			psub->EnableMenuItem(ID_PLUGIN_CONFIG, MF_BYCOMMAND | MF_GRAYED);
			psub->EnableMenuItem(ID_PLUGIN_ABOUT, MF_BYCOMMAND | MF_GRAYED);
		}
	}
	else
	{
		// psub->EnableMenuItem(ID_PLUGIN_ENABLE, MF_BYCOMMAND | MF_GRAYED);
		// psub->EnableMenuItem(ID_PLUGIN_DISABLE, MF_BYCOMMAND | MF_GRAYED);
		psub->EnableMenuItem(ID_PLUGIN_CONFIG, MF_BYCOMMAND | MF_GRAYED);
		psub->EnableMenuItem(ID_PLUGIN_ABOUT, MF_BYCOMMAND | MF_GRAYED);
	}

	psub->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	m_popmenu.DestroyMenu();
}