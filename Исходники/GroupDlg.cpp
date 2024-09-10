void CGroupDlg::OnMacroses() 
{
	CMenu menu;
	menu.CreatePopupMenu ();

	CString str;
	str.Format ("%%server%%  - %s", LS (L_SERVER_MACROS_DESC));
	menu.InsertMenu (0, MF_BYPOSITION | MF_STRING, ID_FOLDER_MACROS_0, str);

	str.Format ("%%path_on_server%%  - %s", LS (L_PATHONSERVER_MACROS_DESC));
	menu.InsertMenu (1, MF_BYPOSITION | MF_STRING, ID_FOLDER_MACROS_0 + 1, str);

	str.Format ("%%year%%  - %s", LS (L_YEAR_MACROS_DESC));
	menu.InsertMenu (2, MF_BYPOSITION | MF_STRING, ID_FOLDER_MACROS_0 + 2, str);

	str.Format ("%%month%%  - %s", LS (L_MONTH_MACROS_DESC));
	menu.InsertMenu (3, MF_BYPOSITION | MF_STRING, ID_FOLDER_MACROS_0 + 3, str);

	str.Format ("%%day%%  - %s", LS (L_DAY_MACROS_DESC));
	menu.InsertMenu (4, MF_BYPOSITION | MF_STRING, ID_FOLDER_MACROS_0 + 4, str);

	str.Format ("%%date%%  - %s", LS (L_DATE_MACROS_DESC));
	menu.InsertMenu (5, MF_BYPOSITION | MF_STRING, ID_FOLDER_MACROS_0 + 5, str);

	str.Format ("%%sdrive%% - %s", LS (L_STARTDRIVELETTER));
	menu.InsertMenu (6, MF_BYPOSITION | MF_STRING, ID_FOLDER_MACROS_0 + 6, str);

	CPoint pt;
	GetCursorPos (&pt);
	menu.TrackPopupMenu (TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_RIGHTALIGN, pt.x, pt.y, this);
}