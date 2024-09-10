//**************************************************************************************
void CBCGPTearOffManager::SetupTearOffMenus (HMENU hMenu)
{
	ASSERT (hMenu != NULL);

	CMenu* pMenu = CMenu::FromHandle (hMenu);
	if (pMenu == NULL)
	{
		return;
	}

	int iCount = (int) pMenu->GetMenuItemCount ();
	for (int i = 0; i < iCount; i ++)
	{
		UINT uiID = pMenu->GetMenuItemID (i);
		if (uiID != (UINT) -1)
		{
			continue;
		}

		UINT uiState = pMenu->GetMenuState (i, MF_BYPOSITION);
		if (uiState & MF_MENUBARBREAK)
		{
			CString str;
			pMenu->GetMenuString (i, str, MF_BYPOSITION);

			if (str [0] != cIDChar)
			{
				UINT uiCtrlBarId = GetFreeTearOffID ();
				if (uiCtrlBarId == 0)	// No more free IDs!
				{						// Reserve more IDs in Initialize!!!
					ASSERT (FALSE);
					return;
				}

				Build (uiCtrlBarId, str);
				pMenu->ModifyMenu (i, MF_BYPOSITION, i, str);
			}
		}

		CMenu* pPopupMenu = pMenu->GetSubMenu (i);
		if (pPopupMenu != NULL)
		{
			SetupTearOffMenus (pPopupMenu->GetSafeHmenu ());
		}
	}
}