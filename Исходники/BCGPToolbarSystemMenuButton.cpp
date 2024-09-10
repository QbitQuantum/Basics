//****************************************************************************************
HMENU CBCGPToolbarSystemMenuButton::CreateMenu () const
{
	ASSERT (m_hSystemMenu != NULL);

	HMENU hMenu = CBCGPToolbarMenuButton::CreateMenu ();
	if (hMenu == NULL)
	{
		return NULL;
	}

	//---------------------------------------------------------------------
	// System menu don't produce updating command statuses via the
	// standard MFC idle command targeting. So, we should enable/disable
	// system menu items according to the standard system menu status:
	//---------------------------------------------------------------------
	CMenu* pMenu = CMenu::FromHandle (hMenu);
	ASSERT_VALID (pMenu);

	CMenu* pSysMenu = CMenu::FromHandle (m_hSystemMenu);
	ASSERT_VALID (pSysMenu);

	int iCount = (int) pSysMenu->GetMenuItemCount ();
	for (int i = 0; i < iCount; i ++)
	{
		UINT uiState = pSysMenu->GetMenuState (i, MF_BYPOSITION);
		UINT uiCmd = pSysMenu->GetMenuItemID (i);

		if (uiState & MF_CHECKED)
		{
			pMenu->CheckMenuItem (uiCmd, MF_CHECKED);
		}

		if (uiState & MF_DISABLED)
		{
			pMenu->EnableMenuItem (uiCmd, MF_DISABLED);
		}

		if (uiState & MF_GRAYED)
		{
			pMenu->EnableMenuItem (uiCmd, MF_GRAYED);
		}
	}

	return hMenu;
}