void moduleListRightClick(HWND hwnd, WPARAM wParam, LPARAM lParam) // hwnd here is to the main window, NOT the treview
{
	TVHITTESTINFO hti;
	hti.pt.x = (short)LOWORD(GetMessagePos());
	hti.pt.y = (short)HIWORD(GetMessagePos());
	ScreenToClient(((LPNMHDR)lParam)->hwndFrom, &hti.pt);

	if (TreeView_HitTest(((LPNMHDR)lParam)->hwndFrom, &hti)) {
		if (hti.flags & TVHT_ONITEM) {
			TVITEM tvi = {0};
			HMENU hMenu, hSubMenu;
			int menuNumber;
			char module[256];
			tvi.mask = TVIF_HANDLE | TVIF_PARAM | TVIF_TEXT;
			tvi.hItem = hti.hItem;
			tvi.pszText = module;
			tvi.cchTextMax = 255;
			TreeView_GetItem(((LPNMHDR)lParam)->hwndFrom, &tvi);
			if (tvi.lParam) {
				ModuleTreeInfoStruct *mtis = (ModuleTreeInfoStruct *)tvi.lParam;
				MCONTACT hContact = mtis->hContact;
				GetCursorPos(&hti.pt);
				hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_CONTEXTMENU));
				TranslateMenu(hMenu);
				if (mtis->type == CONTACT && hContact)
					menuNumber = 2;
				else if ((mtis->type == MODULE) && !hContact)
					menuNumber = 1;
				else if (mtis->type == CONTACT && !hContact)
					menuNumber = 3;
				else if (mtis->type == CONTACT_ROOT_ITEM && !hContact)
					menuNumber = 4;
				else if ((mtis->type == MODULE) && hContact)
					menuNumber = 5;
				else return;
				hSubMenu = GetSubMenu(hMenu, menuNumber);

				TranslateMenu(hSubMenu);
				switch (menuNumber) {
				case 1: // null module
				case 5: // contact module
					{
						// check if we r already watching the module
						int i, watching = 0;
						// check if the setting is being watched and if it is then check the menu item
						if (WatchListArray.item)
							for (i = 0; i < WatchListArray.count; i++)
								if (WatchListArray.item[i].module && (hContact == WatchListArray.item[i].hContact)) {
									if (!mir_strcmp(module, WatchListArray.item[i].module) && !WatchListArray.item[i].setting) {
										// yes so uncheck it
										CheckMenuItem(hSubMenu, MENU_WATCH_ITEM, MF_CHECKED | MF_BYCOMMAND);
										watching = 1;
										break;
									}
								}

						switch (TrackPopupMenu(hSubMenu, TPM_RETURNCMD, hti.pt.x, hti.pt.y, 0, hwnd, NULL)) {
						case MENU_RENAME_MOD:
							TreeView_EditLabel(GetDlgItem(hwnd, IDC_MODULES), tvi.hItem);
							break;

						case MENU_DELETE_MOD:
							if (deleteModule(module, hContact, 0)) {
								TreeView_DeleteItem(((LPNMHDR)lParam)->hwndFrom, hti.hItem);
								mir_free(mtis);
							}
							break;

						case MENU_COPY_MOD:
							copyModuleMenuItem(module, hContact);
							break;

							////////////////////////////////////////////////////////////////////// divider
						case MENU_WATCH_ITEM:
							if (!watching)
								addSettingToWatchList(hContact, module, 0);
							else
								freeWatchListItem(i);
							if (hwnd2watchedVarsWindow)
								PopulateWatchedWindow(GetDlgItem(hwnd2watchedVarsWindow, IDC_VARS));
							break;

						case MENU_EXPORTMODULE:
							exportDB(hContact, module);
							break;

						case MENU_EXPORTDB:
							exportDB(INVALID_CONTACT_ID, module);
							break;
						}
					}
					break;

				case 2: // contact
					switch (TrackPopupMenu(hSubMenu, TPM_RETURNCMD, hti.pt.x, hti.pt.y, 0, hwnd, NULL)) {
					case MENU_CLONE_CONTACT:
						if (CloneContact(hContact))
							refreshTree(1);
						break;

					case MENU_DELETE_CONTACT:
						if (db_get_b(NULL, "CList", "ConfirmDelete", 1)) {
							char msg[1024];
							mir_snprintf(msg, SIZEOF(msg), Translate("Are you sure you want to delete contact \"%s\"?"), module);
							if (MessageBox(0, msg, Translate("Confirm contact delete"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
								CallService(MS_DB_CONTACT_DELETE, hContact, 0);
								freeTree(((LPNMHDR)lParam)->hwndFrom, hContact);
								TreeView_DeleteItem(((LPNMHDR)lParam)->hwndFrom, tvi.hItem);
							}
						}
						else {
							CallService(MS_DB_CONTACT_DELETE, hContact, 0);
							freeTree(((LPNMHDR)lParam)->hwndFrom, hContact);
							TreeView_DeleteItem(((LPNMHDR)lParam)->hwndFrom, tvi.hItem);
						}
						break;

					////////////////////////////////////////////////////////////////////// divider
					case MENU_EXPORTCONTACT:
						exportDB(hContact, 0);
						break;
					case MENU_IMPORTFROMTEXT:
						ImportSettingsMenuItem(hContact);
						break;
					case MENU_IMPORTFROMFILE:
						ImportSettingsFromFileMenuItem(hContact, "");
						break;

					////////////////////////////////////////////////////////////////////// divider
					case MENU_ADD_MODULE:
						{
							HWND AddModhwnd = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_ADD_MODULE), hwnd, AddModDlgProc, hContact);
							char msg[1024];
							mir_snprintf(msg, SIZEOF(msg), Translate("Add module to contact \"%s\""), module);
							SetWindowText(AddModhwnd, module);
						}
						break;
					}
					break;

				case 3: // NULL contact
					switch (TrackPopupMenu(hSubMenu, TPM_RETURNCMD, hti.pt.x, hti.pt.y, 0, hwnd, NULL)) {
					case MENU_ADD_MODULE:
						{
							HWND AddModhwnd = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_ADD_MODULE), hwnd, AddModDlgProc, hContact);
							char msg[1024];
							mir_snprintf(msg, SIZEOF(msg), Translate("Add module to contact \"%s\""), module);
							SetWindowText(AddModhwnd, module);
						}
						break;
					case MENU_EXPORTCONTACT:
						exportDB(NULL, 0);
						break;
					case MENU_IMPORTFROMTEXT:
						ImportSettingsMenuItem(NULL);
						break;
					case MENU_IMPORTFROMFILE:
						ImportSettingsFromFileMenuItem(NULL, "");
						break;
					}
					break;

				case 4: // Contacts root
					switch (TrackPopupMenu(hSubMenu, TPM_RETURNCMD, hti.pt.x, hti.pt.y, 0, hwnd, NULL)) {
					case MENU_EXPORTCONTACT:
						exportDB(INVALID_CONTACT_ID, "");
						break;
					case MENU_IMPORTFROMTEXT:
						ImportSettingsMenuItem(NULL);
						break;
					case MENU_IMPORTFROMFILE:
						ImportSettingsFromFileMenuItem(NULL, "");
						break;
					}
					break;
				}
				DestroyMenu(hMenu);
			}
		}
	}
}