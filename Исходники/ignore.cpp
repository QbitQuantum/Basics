INT_PTR CALLBACK DlgProcIgnoreOptions(HWND hwndDlg, UINT msg, WPARAM, LPARAM lParam)
{
	static HICON hIcons[IGNOREEVENT_MAX+2];
	static HANDLE hItemAll, hItemUnknown;

	switch (msg)
	{
		case WM_INITDIALOG:
			TranslateDialogDefault(hwndDlg);
			{
				HIMAGELIST hIml=ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), ILC_COLOR32 | ILC_MASK, 3+IGNOREEVENT_MAX, 3+IGNOREEVENT_MAX);
				ImageList_AddIcon(hIml, Skin_LoadIcon(SKINICON_OTHER_SMALLDOT));
				ImageList_AddIcon(hIml, Skin_LoadIcon(SKINICON_OTHER_FILLEDBLOB));
				ImageList_AddIcon(hIml, Skin_LoadIcon(SKINICON_OTHER_EMPTYBLOB));
				ImageList_AddIcon(hIml, Skin_LoadIcon(SKINICON_EVENT_MESSAGE));
				ImageList_AddIcon(hIml, Skin_LoadIcon(SKINICON_EVENT_URL));
				ImageList_AddIcon(hIml, Skin_LoadIcon(SKINICON_EVENT_FILE));
				ImageList_AddIcon(hIml, Skin_LoadIcon(SKINICON_OTHER_MIRANDA));
				SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_SETEXTRAIMAGELIST, 0, (LPARAM)hIml);
				for (int i=0; i < _countof(hIcons); i++)
					hIcons[i] = ImageList_GetIcon(hIml, 1+i, ILD_NORMAL);
			}
			SendDlgItemMessage(hwndDlg, IDC_ALLICON, STM_SETICON, (WPARAM)hIcons[0], 0);
			SendDlgItemMessage(hwndDlg, IDC_NONEICON, STM_SETICON, (WPARAM)hIcons[1], 0);
			SendDlgItemMessage(hwndDlg, IDC_MSGICON, STM_SETICON, (WPARAM)hIcons[2], 0);
			SendDlgItemMessage(hwndDlg, IDC_URLICON, STM_SETICON, (WPARAM)hIcons[3], 0);
			SendDlgItemMessage(hwndDlg, IDC_FILEICON, STM_SETICON, (WPARAM)hIcons[4], 0);
			SendDlgItemMessage(hwndDlg, IDC_OTHERICON, STM_SETICON, (WPARAM)hIcons[5], 0);

			SetWindowLongPtr(GetDlgItem(hwndDlg, IDC_LIST), GWL_STYLE, GetWindowLongPtr(GetDlgItem(hwndDlg, IDC_LIST), GWL_STYLE) &~ (CLS_CHECKBOXES|CLS_GROUPCHECKBOXES));
			SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_AUTOREBUILD, 0, 0);

			ResetListOptions(GetDlgItem(hwndDlg, IDC_LIST));
			SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_SETEXTRACOLUMNS, IGNOREEVENT_MAX+2, 0);

			{	CLCINFOITEM cii = {0};
				cii.cbSize = sizeof(cii);
				cii.flags = CLCIIF_GROUPFONT;
				cii.pszText = TranslateT("** All contacts **");
				hItemAll=(HANDLE)SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_ADDINFOITEM, 0, (LPARAM)&cii);

				cii.pszText = TranslateT("** Unknown contacts **");
				hItemUnknown=(HANDLE)SendDlgItemMessage(hwndDlg, IDC_LIST,CLM_ADDINFOITEM, 0, (LPARAM)&cii);
				InitialiseItem(GetDlgItem(hwndDlg, IDC_LIST), NULL, hItemUnknown, 0xFFFFFFFF);
			}

			SetAllContactIcons(GetDlgItem(hwndDlg, IDC_LIST));
			SetListGroupIcons(GetDlgItem(hwndDlg, IDC_LIST),(HANDLE)SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_GETNEXTITEM, CLGN_ROOT, 0), hItemAll, NULL);
			return TRUE;
		case WM_SETFOCUS:
			SetFocus(GetDlgItem(hwndDlg, IDC_LIST));
			break;
		case WM_NOTIFY:
			switch(((LPNMHDR)lParam)->idFrom) {
				case IDC_LIST:
					switch (((LPNMHDR)lParam)->code)
					{
						case CLN_NEWCONTACT:
						case CLN_LISTREBUILT:
							SetAllContactIcons(GetDlgItem(hwndDlg, IDC_LIST));
							//fall through
						case CLN_CONTACTMOVED:
							SetListGroupIcons(GetDlgItem(hwndDlg, IDC_LIST), (HANDLE)SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_GETNEXTITEM, CLGN_ROOT, 0), hItemAll, NULL);
							break;
						case CLN_OPTIONSCHANGED:
							ResetListOptions(GetDlgItem(hwndDlg, IDC_LIST));
							break;
						case CLN_CHECKCHANGED:
							SendMessage(GetParent(GetParent(hwndDlg)), PSM_CHANGED, 0, 0);
							break;
						case NM_CLICK:
						{	int iImage;
							HANDLE hItem;
							DWORD hitFlags;
							NMCLISTCONTROL *nm = (NMCLISTCONTROL*)lParam;

							if(nm->iColumn == -1)
								break;
							hItem = (HANDLE)SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_HITTEST, (WPARAM)&hitFlags, MAKELPARAM(nm->pt.x, nm->pt.y));
							if(hItem == NULL)
								break;
							if (!(hitFlags & CLCHT_ONITEMEXTRA))
								break;
							if(nm->iColumn == IGNOREEVENT_MAX) {   //ignore all
								for (iImage=0; iImage < IGNOREEVENT_MAX; iImage++)
									SetIconsForColumn(GetDlgItem(hwndDlg, IDC_LIST), hItem, hItemAll, iImage, iImage+3);
							}
							else if(nm->iColumn == IGNOREEVENT_MAX+1) {	//ignore none
								for (iImage=0; iImage < IGNOREEVENT_MAX; iImage++)
									SetIconsForColumn(GetDlgItem(hwndDlg, IDC_LIST), hItem, hItemAll, iImage, 0);
							}
							else {
								iImage = SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_GETEXTRAIMAGE, (WPARAM)hItem, MAKELPARAM(nm->iColumn, 0));
								if(iImage == 0)
									iImage = nm->iColumn + 3;
								else if(iImage != EMPTY_EXTRA_ICON)
									iImage = 0;
								SetIconsForColumn(GetDlgItem(hwndDlg, IDC_LIST), hItem, hItemAll, nm->iColumn, iImage);
							}
							SetListGroupIcons(GetDlgItem(hwndDlg, IDC_LIST),(HANDLE)SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_GETNEXTITEM, CLGN_ROOT, 0), hItemAll, NULL);
							SendMessage(GetParent(GetParent(hwndDlg)), PSM_CHANGED, 0, 0);
							break;
						}
					}
					break;
				case 0:
					switch (((LPNMHDR)lParam)->code)
					{
						case PSN_APPLY:
						{
							for (MCONTACT hContact = db_find_first(); hContact; hContact = db_find_next(hContact)) {
								HANDLE hItem = (HANDLE)SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_FINDCONTACT, hContact, 0);
								if(hItem)
									SaveItemMask(GetDlgItem(hwndDlg, IDC_LIST), hContact, hItem, "Mask1");
							}
							SaveItemMask(GetDlgItem(hwndDlg, IDC_LIST), NULL, hItemAll, "Default1");
							SaveItemMask(GetDlgItem(hwndDlg, IDC_LIST), NULL, hItemUnknown, "Mask1");
							return TRUE;
						}
					}
					break;
			}
			break;
		case WM_DESTROY:
		{	int i;
			HIMAGELIST hIml;
			for (i=0; i < _countof(hIcons); i++)
				DestroyIcon(hIcons[i]);
			hIml = (HIMAGELIST)SendDlgItemMessage(hwndDlg, IDC_LIST, CLM_GETEXTRAIMAGELIST, 0, 0);
			ImageList_Destroy(hIml);
			break;
		}
	}
	return FALSE;
}