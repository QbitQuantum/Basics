void CBuddyManager::NotifyBuddyIsOnline(BUDDY_INFO *pBI, SERVER_INFO *pServerInfo)
{
	if(pBI==NULL)
		return;
	if(pServerInfo==NULL)
		return;

	vecBI::iterator it = FindBuddyInfoByID(pBI->dwID);
	if(it==BuddyList.end())
		return;

	if(pServerInfo->szServerName!=NULL)
		strncpy_s(it->szServerName,sizeof(pBI->szServerName),pServerInfo->szServerName,_TRUNCATE);

	it->cGAMEINDEX = pServerInfo->cGAMEINDEX;
	it->sIndex = (int) pServerInfo->dwIndex;  //have to change the Buddy index to a new var that can hold bigger numbers such as DWORD

	HWND hwndLV = g_hwndListBuddy;

	LV_FINDINFO lvfi;
	char szText[250];
	memset(&lvfi,0,sizeof(LV_FINDINFO));
	lvfi.flags = LVFI_PARAM;
	lvfi.lParam = (LPARAM)pBI->dwID;
	int index = ListView_FindItem(hwndLV , -1,  &lvfi); 

	if(index!=-1)
	{
		LVITEM item;
		item.mask = LVIF_TEXT | LVIF_IMAGE;
		item.iItem = index;
		memset(szText,0,sizeof(szText));
	
		if(gm.GamesInfo[it->cGAMEINDEX].colorfilter!=NULL)
		{					
			gm.GamesInfo[it->cGAMEINDEX].colorfilter(it->szServerName,szText,249);
			item.pszText = szText;
			item.cchTextMax = (int)strlen(szText);
		}
		else
		{
			item.pszText = it->szServerName;
			item.cchTextMax = (int)strlen(it->szServerName);
		}

		item.iSubItem = 1;
		item.iImage = gm.Get_GameIcon(it->cGAMEINDEX);
		ListView_SetItem(g_hwndListBuddy,&item);

		sprintf_s(szText,"%s:%d",pServerInfo->szIPaddress,pServerInfo->usPort);
		strcpy_s(it->szIPaddress,szText);
		ListView_SetItemText(g_hwndListBuddy,index ,2,szText);

	}

	if(gm.GamesInfo[it->cGAMEINDEX].colorfilter!=NULL)
		gm.GamesInfo[it->cGAMEINDEX].colorfilter(it->szServerName,szText,249);
	else
		strcpy_s(szText,it->szPlayerName);

	if(g_bRunningQueryServerList && g_bPlayedNotify==false)
		PlayNotifySound(0 );

	if(AppCFG.bBuddyNotify)
		ShowBalloonTip("A buddy is online!",szText);		
}