INT_PTR CALLBACK DlgPluginOpt(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
		timerID = 0;
		{
			HWND hwndList = GetDlgItem(hwndDlg, IDC_PLUGLIST);
			mir_subclassWindow(hwndList, PluginListWndProc);

			HIMAGELIST hIml = ImageList_Create(16, 16, ILC_MASK | ILC_COLOR32, 4, 0);
			ImageList_AddIcon_IconLibLoaded(hIml, SKINICON_OTHER_UNICODE);
			ImageList_AddIcon_IconLibLoaded(hIml, SKINICON_OTHER_ANSI);
			ImageList_AddIcon_IconLibLoaded(hIml, SKINICON_OTHER_LOADED);
			ImageList_AddIcon_IconLibLoaded(hIml, SKINICON_OTHER_NOTLOADED);
			ImageList_AddIcon_IconLibLoaded(hIml, SKINICON_OTHER_LOADEDGRAY);
			ImageList_AddIcon_IconLibLoaded(hIml, SKINICON_OTHER_NOTLOADEDGRAY);
			ListView_SetImageList(hwndList, hIml, LVSIL_SMALL);

			LVCOLUMN col;
			col.mask = LVCF_TEXT | LVCF_WIDTH;
			col.pszText = _T("");
			col.cx = 40;
			ListView_InsertColumn(hwndList, 0, &col);

			col.pszText = TranslateT("Plugin");
			col.cx = 180;
			ListView_InsertColumn(hwndList, 1, &col);

			col.pszText = TranslateT("Name");
			col.cx = 180;//max = 220;
			ListView_InsertColumn(hwndList, 2, &col);

			col.pszText = TranslateT("Version");
			col.cx = 75;
			ListView_InsertColumn(hwndList, 3, &col);

			ListView_SetExtendedListViewStyleEx(hwndList, 0, LVS_EX_SUBITEMIMAGES | LVS_EX_CHECKBOXES | LVS_EX_LABELTIP | LVS_EX_FULLROWSELECT);
			// scan the plugin dir for plugins, cos
			arPluginList.destroy();
			szFilter.Empty();
			enumPlugins(dialogListPlugins, (WPARAM)hwndDlg, (LPARAM)hwndList);
			// sort out the headers

			ListView_SetColumnWidth(hwndList, 1, LVSCW_AUTOSIZE); // dll name
			int w = ListView_GetColumnWidth(hwndList, 1);
			if (w > 110) {
				ListView_SetColumnWidth(hwndList, 1, w = 110);
			}
			int max = w < 110 ? 189 + 110 - w : 189;
			ListView_SetColumnWidth(hwndList, 3, LVSCW_AUTOSIZE); // short name
			w = ListView_GetColumnWidth(hwndList, 2);
			if (w > max)
				ListView_SetColumnWidth(hwndList, 2, max);

			ListView_SortItems(hwndList, SortPlugins, (LPARAM)hwndDlg);
		}
		return TRUE;

	case WM_NOTIFY:
		if (lParam) {
			NMLISTVIEW *hdr = (NMLISTVIEW *)lParam;
			if (hdr->hdr.code == LVN_ITEMCHANGED && IsWindowVisible(hdr->hdr.hwndFrom)) {
				if (hdr->uOldState != 0 && (hdr->uNewState == 0x1000 || hdr->uNewState == 0x2000)) {
					HWND hwndList = GetDlgItem(hwndDlg, IDC_PLUGLIST);

					LVITEM it;
					it.mask = LVIF_PARAM | LVIF_STATE;
					it.iItem = hdr->iItem;
					if (!ListView_GetItem(hwndList, &it))
						break;

					PluginListItemData *dat = (PluginListItemData*)it.lParam;
					if (dat->flags & STATIC_PLUGIN) {
						ListView_SetItemState(hwndList, hdr->iItem, 0x3000, LVIS_STATEIMAGEMASK);
						return FALSE;
					}
					// find all another standard plugins by mask and disable them
					if ((hdr->uNewState == 0x2000) && dat->stdPlugin != 0) {
						for (int iRow = 0; iRow != -1; iRow = ListView_GetNextItem(hwndList, iRow, LVNI_ALL)) {
							if (iRow != hdr->iItem) { // skip the plugin we're standing on
								LVITEM dt;
								dt.mask = LVIF_PARAM;
								dt.iItem = iRow;
								if (ListView_GetItem(hwndList, &dt)) {
									PluginListItemData *dat2 = (PluginListItemData*)dt.lParam;
									if (dat2->stdPlugin & dat->stdPlugin) {// mask differs
										// the lParam is unset, so when the check is unset the clist block doesnt trigger
										int iSave = dat2->stdPlugin;
										dat2->stdPlugin = 0;
										ListView_SetItemState(hwndList, iRow, 0x1000, LVIS_STATEIMAGEMASK);
										dat2->stdPlugin = iSave;
									}
								}
							}
						}
					}

					if (bOldMode)
						ShowWindow(GetDlgItem(hwndDlg, IDC_RESTART), TRUE); // this here only in "ghazan mode"
					SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
					break;
				}

				if (hdr->iItem != -1) {
					int sel = hdr->uNewState & LVIS_SELECTED;
					HWND hwndList = GetDlgItem(hwndDlg, IDC_PLUGLIST);
					LVITEM lvi = { 0 };
					lvi.mask = LVIF_PARAM;
					lvi.iItem = hdr->iItem;
					if (ListView_GetItem(hwndList, &lvi)) {
						PluginListItemData *dat = (PluginListItemData*)lvi.lParam;

						TCHAR buf[1024];
						ListView_GetItemText(hwndList, hdr->iItem, 2, buf, _countof(buf));
						SetDlgItemText(hwndDlg, IDC_PLUGININFOFRAME, sel ? buf : _T(""));

						ptrT tszAuthor(latin2t(sel ? dat->author : NULL));
						SetDlgItemText(hwndDlg, IDC_PLUGINAUTHOR, tszAuthor);

						ptrT tszEmail(latin2t(sel ? dat->authorEmail : NULL));
						SetDlgItemText(hwndDlg, IDC_PLUGINEMAIL, tszEmail);

						ptrT p(Langpack_PcharToTchar(dat->description));
						SetDlgItemText(hwndDlg, IDC_PLUGINLONGINFO, sel ? p : _T(""));

						ptrT tszCopyright(latin2t(sel ? dat->copyright : NULL));
						SetDlgItemText(hwndDlg, IDC_PLUGINCPYR, tszCopyright);

						ptrT tszUrl(latin2t(sel ? dat->homepage : NULL));
						SetDlgItemText(hwndDlg, IDC_PLUGINURL, tszUrl);

						if (!equalUUID(miid_last, dat->uuid)) {
							char szUID[128];
							uuidToString(dat->uuid, szUID, sizeof(szUID));
							SetDlgItemTextA(hwndDlg, IDC_PLUGINPID, sel ? szUID : "");
						}
						else SetDlgItemText(hwndDlg, IDC_PLUGINPID, sel ? TranslateT("<none>") : _T(""));
					}
				}
			}

			if (hdr->hdr.code == PSN_APPLY) {
				bool needRestart = false;
				TCHAR bufRestart[1024];
				int bufLen = mir_sntprintf(bufRestart, _T("%s\n"), TranslateT("Miranda NG must be restarted to apply changes for these plugins:"));

				HWND hwndList = GetDlgItem(hwndDlg, IDC_PLUGLIST);
				for (int iRow = 0; iRow != -1;) {
					TCHAR buf[1024];
					ListView_GetItemText(hwndList, iRow, 1, buf, _countof(buf));
					int iState = ListView_GetItemState(hwndList, iRow, LVIS_STATEIMAGEMASK);
					SetPluginOnWhiteList(buf, (iState & 0x2000) ? 1 : 0);

					if (!bOldMode && iState != 0x3000) {
						LVITEM lvi = { 0 };
						lvi.mask = LVIF_IMAGE | LVIF_PARAM;
						lvi.stateMask = -1;
						lvi.iItem = iRow;
						lvi.iSubItem = 0;
						if (ListView_GetItem(hwndList, &lvi)) {
							lvi.mask = LVIF_IMAGE;

							PluginListItemData *dat = (PluginListItemData*)lvi.lParam;
							if (iState == 0x2000) {
								// enabling plugin
								if (lvi.iImage == 3 || lvi.iImage == 5) {
									if (lvi.iImage == 3 && LoadPluginDynamically(dat)) {
										lvi.iImage = 2;
										ListView_SetItem(hwndList, &lvi);
									}
									else {
										bufLen += mir_sntprintf(bufRestart + bufLen, _countof(bufRestart) - bufLen, _T(" - %s\n"), buf);
										needRestart = true;
									}
								}
							}
							else {
								// disabling plugin
								if (lvi.iImage == 2 || lvi.iImage == 4) {
									if (lvi.iImage == 2 && UnloadPluginDynamically(dat)) {
										lvi.iImage = 3;
										ListView_SetItem(hwndList, &lvi);
									}
									else {
										bufLen += mir_sntprintf(bufRestart + bufLen, _countof(bufRestart) - bufLen, _T(" - %s\n"), buf);
										needRestart = true;
									}
								}
							}
						}
					}

					iRow = ListView_GetNextItem(hwndList, iRow, LVNI_ALL);
				}
				LoadStdPlugins();

				ShowWindow(GetDlgItem(hwndDlg, IDC_RESTART), needRestart);
				if (needRestart) {
					mir_sntprintf(bufRestart + bufLen, _countof(bufRestart) - bufLen, _T("\n%s"), TranslateT("Do you want to restart it now?"));
					if (MessageBox(NULL, bufRestart, _T("Miranda NG"), MB_ICONWARNING | MB_YESNO) == IDYES)
						CallService(MS_SYSTEM_RESTART, 1, 0);
				}
			}
		}
		break;

	case WM_COMMAND:
		if (HIWORD(wParam) == STN_CLICKED) {
			switch (LOWORD(wParam)) {
			case IDC_GETMOREPLUGINS:
				Utils_OpenUrl("http://miranda-ng.org/downloads/");
				break;

			case IDC_PLUGINEMAIL:
			case IDC_PLUGINURL:
				char buf[512];
				char *p = &buf[7];
				mir_strcpy(buf, "mailto:");
				if (GetDlgItemTextA(hwndDlg, LOWORD(wParam), p, _countof(buf) - 7))
					Utils_OpenUrl(LOWORD(wParam) == IDC_PLUGINEMAIL ? buf : p);
				break;
			}
		}
		break;

	case WM_DESTROY:
		arPluginList.destroy();
		RemoveAllItems(GetDlgItem(hwndDlg, IDC_PLUGLIST));
		break;
	}
	return FALSE;
}