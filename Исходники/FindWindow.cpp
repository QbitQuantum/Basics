void __cdecl FindSettings(LPVOID param)
{
	FindInfo* fi = (FindInfo*)param;
	HWND hwndParent = GetParent(fi->hwnd);

	ModuleSettingLL ModuleList, SettingList;
	ModSetLinkLinkItem *module, *setting;

	MCONTACT hContact;
	DBVARIANT dbv = { 0 };

	int foundCount = 0,	 replaceCount = 0, deleteCount = 0;

	DWORD numsearch = 0, numreplace = 0;
	int NULLContactDone = 0;

	if (!fi->search || !EnumModules(&ModuleList)) {
		fi_free(fi);
		return;
	}

	_T2A search(fi->search);
	_T2A replace(fi->replace);

    // skip modules and setting names on unicode search or replace
   	if (IsRealUnicode(fi->search) || IsRealUnicode(fi->replace)) {
   		fi->options &= ~(F_SETNAME | F_MODNAME); 
   		fi->options |= F_UNICODE;
   	}

    if (!(fi->options & F_UNICODE) && (fi->options & F_SETVAL)) {
		char val[16];
		numsearch = strtoul(search, NULL, 10);
		_ultoa(numsearch, val, 10);
		if (!mir_strcmp(search, val)) {
			fi->options |= F_NUMSRCH;
			// replace numeric values only entirely
			if (replace && (fi->options & F_ENTIRE)) {
				numreplace = strtoul(replace, NULL, 10);
				_ultoa(numreplace, val, 10);
				if (!replace[0] || !mir_strcmp(replace, val))
					fi->options |= F_NUMREPL;
			}
		}
	}

	SendDlgItemMessage(hwndParent, IDC_SBAR, SB_SETTEXT, 0, (LPARAM)TranslateT("Searching..."));

	hContact = 0;

	while (GetWindowLongPtr(GetDlgItem(hwndParent, IDC_SEARCH), GWLP_USERDATA)) {

		if (!hContact) {
			if (NULLContactDone) 
				break;
			else {
				NULLContactDone = 1;
				hContact = db_find_first();
			}
		}
		else 
			hContact = db_find_next(hContact);

		for (module = ModuleList.first; module; module = module->next) {

			if (IsModuleEmpty(hContact, module->name))
				continue;

			if (fi->options & (F_SETVAL | F_SETNAME)) {

				if (!EnumSettings(hContact, module->name, &SettingList)) {
					fi_free(fi);
					FreeModuleSettingLL(&ModuleList);
					return;
				}

				for (setting = SettingList.first; setting; setting = setting->next) {

					dbv.type = 0;
					if (db_get_s(hContact, module->name, setting->name, &dbv, 0))
						continue;

					// check in settings value				
					if (fi->options & F_SETVAL) {

						TCHAR *value = NULL;

					    switch(dbv.type) {

						case DBVT_BYTE: 
						case DBVT_WORD: 
						case DBVT_DWORD:
							if ((fi->options & F_NUMSRCH) && numsearch == getNumericValue(&dbv)) {
								TCHAR *val = fi->search;
								int flag = F_SETVAL;

								if (fi->options & F_NUMREPL) {
								    if (replace[0]) {
										db_unset(hContact, module->name, setting->name);
										flag |= F_DELETED;
										deleteCount++;
									} 
									else
									if (setNumericValue(hContact, module->name, setting->name, numreplace, dbv.type)) {
										val = fi->replace;
										flag |= F_REPLACED;
										replaceCount++;
									}
								}

								ItemFound(fi->hwnd, hContact, module->name, setting->name, val, flag);
							}
							break;

						case DBVT_WCHAR:
							if (!value) value = mir_u2t(dbv.pwszVal);
						case DBVT_UTF8:
							if (!value) value = mir_utf8decodeT(dbv.pszVal);
						case DBVT_ASCIIZ:
							if (!value) value = mir_a2t(dbv.pszVal);

							if (FindMatchT(value, fi->search, fi->options)) {
								foundCount++;
								ptrT ptr;
								TCHAR *newValue = value;
								int flag = F_SETVAL;

								if (fi->replace) {
									newValue = (fi->options & F_ENTIRE) ? fi->replace : ptr = multiReplaceT(value, fi->search, fi->replace, fi->options & F_CASE);
									// !!!! delete or make empty ?
									if (!newValue[0]) {
										db_unset(hContact, module->name, setting->name);
										flag |= F_DELETED;
										newValue = value;
										deleteCount++;
									} else {
#ifdef _UNICODE
                                        // save as unicode if needed
										if (dbv.type != DBVT_ASCIIZ || IsRealUnicode(newValue))
											db_set_ws(hContact, module->name, setting->name, newValue);
										else												
#endif
											db_set_s(hContact, module->name, setting->name, _T2A(newValue)); 
										flag |= F_REPLACED;
										replaceCount++;
									}
								}

								ItemFound(fi->hwnd, hContact, module->name, setting->name, newValue, flag);
							}
							mir_free(value);
							break;
						} // switch
					}

					// check in setting name
					if ((fi->options & F_SETNAME) && FindMatchA(setting->name, search, fi->options)) {
						foundCount++;
						ptrA ptr;
						char *newSetting = setting->name;
						int flag = F_SETNAME;

						if (replace) {
							newSetting = (fi->options & F_ENTIRE) ? replace : ptr = multiReplaceA(setting->name, search, replace, fi->options & F_CASE);

							if (!newSetting[0]) {
								db_unset(hContact, module->name, setting->name);
								flag |= F_DELETED;
								newSetting = setting->name;
								deleteCount++;
							} else {
								DBVARIANT dbv2;
								// skip if exist
								if (!db_get_s(hContact, module->name, newSetting, &dbv2, 0)) 
									db_free(&dbv2);
								else if (!db_set(hContact, module->name, newSetting, &dbv)) {
									db_unset(hContact, module->name, setting->name);
									flag |= F_REPLACED;
							 		replaceCount++;
								}
							}
						}

						ItemFound(fi->hwnd, hContact, module->name, newSetting, NULL, flag);
					}

					db_free(&dbv);

				} // for(setting)

				FreeModuleSettingLL(&SettingList);
			}

			// check in module name
			if ((fi->options & F_MODNAME) && FindMatchA(module->name, search, fi->options)) {
				foundCount++;
				char *newModule = module->name;
				int flag = F_MODNAME;
				ptrA ptr;

				if (replace) {
					newModule = (fi->options & F_ENTIRE) ? replace : ptr = multiReplaceA(module->name, search, replace, fi->options & F_CASE);
								
					if (!newModule[0]) {
						deleteModule(hContact, module->name, 0);
						replaceTreeItem(hContact, module->name, NULL);
						flag |= F_DELETED;
						newModule = module->name;
						deleteCount++;
					} 
					else if (renameModule(hContact, module->name, newModule)) {
   						replaceTreeItem(hContact, module->name, NULL);
						flag |= F_REPLACED;
						replaceCount++;
					}
				}

				ItemFound(fi->hwnd, hContact, newModule, 0, 0, flag);
			}

		} // for(module)
	}

	TCHAR msg[MSG_SIZE];	
	mir_sntprintf(msg, TranslateT("Finished. Items found: %d / replaced: %d / deleted: %d"), foundCount, replaceCount, deleteCount);
	SendDlgItemMessage(hwndParent, IDC_SBAR, SB_SETTEXT, 0, (LPARAM)msg);

	if (fi->replace) {
		EnableWindow(GetDlgItem(hwndParent, IDC_SEARCH), 1);
		SetDlgItemText(hwndParent, IDOK, TranslateT("&Replace"));
	}
	else {
		SetDlgItemText(hwndParent, IDC_SEARCH, TranslateT("&Search"));
		EnableWindow(GetDlgItem(hwndParent, IDOK), 1);
	}

	fi_free(fi);
	FreeModuleSettingLL(&ModuleList);

	SetWindowLongPtr(GetDlgItem(hwndParent, IDC_SEARCH), GWLP_USERDATA, 0);
	EnableWindow(GetDlgItem(hwndParent, IDCANCEL), 1);
}