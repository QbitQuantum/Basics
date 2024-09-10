// List INI Information for all loaded INI files
void INIInfo(HWND hwndDlg) 
{
	char str[16]; 
	size_t memused = 0;
	LVITEM   lvi = {0};
	WIDATALIST *Item = WIHead;

	HWND hIniList = GetDlgItem(hwndDlg, IDC_INFOLIST);

	ListView_DeleteAllItems(hIniList);

	lvi.mask = LVIF_TEXT;
	lvi.iItem = 0;
	while (Item != NULL) 
	{
		// get the data for the ini file
		lvi.iSubItem = 0;
		lvi.pszText = Item->Data.InternalName;
		ListView_InsertItem(hIniList, &lvi); 
		lvi.iSubItem = 1;
		lvi.pszText = Item->Data.Author;
		ListView_SetItem(hIniList, &lvi); 
		lvi.iSubItem = 2;
		lvi.pszText = Item->Data.Version;
		ListView_SetItem(hIniList, &lvi); 
		lvi.iSubItem = 3;
		switch (Item->Data.InternalVer) 
		{
		case 1:  lvi.pszText = "1.0";  break;
		case 2:  lvi.pszText = "1.1";  break;
		case 3:  lvi.pszText = "1.1a"; break;
		case 4:  lvi.pszText = "1.2";  break;
		case 5:  lvi.pszText = "1.3";  break;
		case 6:  lvi.pszText = "1.4";  break;
		default: lvi.pszText = "";     break;
		}
		ListView_SetItem(hIniList, &lvi); 
		lvi.iSubItem = 4;
		lvi.pszText = _ltoa(Item->Data.UpdateDataCount, str, 10);
		ListView_SetItem(hIniList, &lvi); 
		lvi.iSubItem = 5;
		lvi.pszText = Item->Data.DisplayName;
		ListView_SetItem(hIniList, &lvi); 
		lvi.iSubItem = 6;
		lvi.pszText = Item->Data.ShortFileName;
		ListView_SetItem(hIniList, &lvi); 

		memused += Item->Data.MemUsed;

		Item = Item->next;
		++lvi.iItem;
	}
	SetDlgItemText(hwndDlg, IDC_INICOUNT, _itoa(lvi.iItem, str, 10));
	SetDlgItemText(hwndDlg, IDC_MEMUSED, _ltoa((long)memused, str, 10));
}