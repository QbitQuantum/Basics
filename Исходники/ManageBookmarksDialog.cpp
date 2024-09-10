void CManageBookmarksDialog::ShowViewMenu()
{
	DWORD dwButtonState = static_cast<DWORD>(SendMessage(m_hToolbar,TB_GETSTATE,TOOLBAR_ID_VIEWS,MAKEWORD(TBSTATE_PRESSED,0)));
	SendMessage(m_hToolbar,TB_SETSTATE,TOOLBAR_ID_VIEWS,MAKEWORD(dwButtonState|TBSTATE_PRESSED,0));

	HMENU hMenu = LoadMenu(GetInstance(),MAKEINTRESOURCE(IDR_MANAGEBOOKMARKS_VIEW_MENU));

	UINT uCheck;

	if(m_pmbdps->m_bSortAscending)
	{
		uCheck = IDM_MB_VIEW_SORTASCENDING;
	}
	else
	{
		uCheck = IDM_MB_VIEW_SORTDESCENDING;
	}

	CheckMenuRadioItem(hMenu,IDM_MB_VIEW_SORTASCENDING,IDM_MB_VIEW_SORTDESCENDING,uCheck,MF_BYCOMMAND);

	switch(m_pmbdps->m_SortMode)
	{
	case NBookmarkHelper::SM_NAME:
		uCheck = IDM_MB_VIEW_SORTBYNAME;
		break;

	case NBookmarkHelper::SM_LOCATION:
		uCheck = IDM_MB_VIEW_SORTBYLOCATION;
		break;

	case NBookmarkHelper::SM_VISIT_DATE:
		uCheck = IDM_MB_VIEW_SORTBYVISITDATE;
		break;

	case NBookmarkHelper::SM_VISIT_COUNT:
		uCheck = IDM_MB_VIEW_SORTBYVISITCOUNT;
		break;

	case NBookmarkHelper::SM_ADDED:
		uCheck = IDM_MB_VIEW_SORTBYADDED;
		break;

	case NBookmarkHelper::SM_LAST_MODIFIED:
		uCheck = IDM_MB_VIEW_SORTBYLASTMODIFIED;
		break;
	}

	CheckMenuRadioItem(hMenu,IDM_MB_VIEW_SORTBYNAME,IDM_MB_VIEW_SORTBYLASTMODIFIED,uCheck,MF_BYCOMMAND);

	RECT rcButton;
	SendMessage(m_hToolbar,TB_GETRECT,TOOLBAR_ID_VIEWS,reinterpret_cast<LPARAM>(&rcButton));

	POINT pt;
	pt.x = rcButton.left;
	pt.y = rcButton.bottom;
	ClientToScreen(m_hToolbar,&pt);

	TrackPopupMenu(GetSubMenu(hMenu,0),TPM_LEFTALIGN,pt.x,pt.y,0,m_hDlg,NULL);
	DestroyMenu(hMenu);

	SendMessage(m_hToolbar,TB_SETSTATE,TOOLBAR_ID_VIEWS,MAKEWORD(dwButtonState,0));
}