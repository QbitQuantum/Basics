void CMenuSpawn::RemapMenu(HMENU hMenu)
{
	static int iRecurse = 0;
	iRecurse ++;

	CMenu pMenu;
	pMenu.Attach(hMenu);
	
	ASSERT(pMenu);
	int nItem = pMenu.GetMenuItemCount();
	while ((--nItem)>=0)
	{
		UINT itemId = pMenu.GetMenuItemID(nItem);
		if (itemId == (UINT) -1)
		{
			CMenu pops(pMenu.GetSubMenu(nItem));
			if (pops.GetHandleMenu()) RemapMenu(pops.GetHandleMenu());
			if (bIsPopup || iRecurse > 0)
			{
				TCHAR cs[128];
				memset(cs,0x00,128);
				pMenu.GetMenuString(nItem, cs, 128,MF_BYPOSITION);
				if (lstrlen(cs)>0)
				{
					SpawnItem * sp = AddSpawnItem(cs, (!bIsPopup && iRecurse == 1) ? -4 : -2);
					pMenu.ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW, (UINT) -1, (LPCTSTR)sp);
				}
			}
		}
		else
		{
			if (itemId != 0)
			{
				UINT oldState = pMenu.GetMenuState(nItem,MF_BYPOSITION);
				if (!(oldState&MF_OWNERDRAW) && !(oldState&MF_BITMAP))
				{
					ASSERT(oldState != (UINT)-1);
					TCHAR cs[128];
					memset(cs,0x00,128);
					pMenu.GetMenuString(nItem, cs, 128, MF_BYPOSITION);
					SpawnItem * sp = AddSpawnItem(cs, itemId);
					if (itemId!=SC_CLOSE)
					pMenu.ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW|oldState, (LPARAM)itemId, (LPCTSTR)sp);
				}
			}
			else
			{
				UINT oldState = pMenu.GetMenuState(nItem,MF_BYPOSITION);
				if (!(oldState&MF_OWNERDRAW) && !(oldState&MF_BITMAP))
				{
					ASSERT(oldState != (UINT)-1);
					SpawnItem * sp = AddSpawnItem("--", -3);
					pMenu.ModifyMenu(nItem,MF_BYPOSITION|MF_OWNERDRAW|oldState, (LPARAM)itemId, (LPCTSTR)sp);
				}
			}
		}
	}
	iRecurse --;
	pMenu.Detach();
}