INT_PTR CALLBACK CFileGroups::DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
// 	OutputDebugString("%s(%08X, %s, %08X, %08X)", __FUNCTION__, hwndDlg,
// 		GetMessageName(uMsg), wParam, lParam);
	static filegroups_t *pfile_groups(0);
	static HWND hwndTVCtrl, hwndEditCtrl;
	OPENFILENAME ofn;
	TVINSERTSTRUCT tvis;
	TVITEMEX tvi;
	HTREEITEM hti, hParent, hGroup, hChild, hSel;
	char text[MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR], path[QMAXPATH], ext[_MAX_EXT];
	BOOL hasSelection;
	switch (uMsg) {
		case WM_INITDIALOG: {
			_ASSERTE(lParam != 0);
			if (lParam == 0) {
				EndDialog(hwndDlg, IDCANCEL);
				return FALSE;
			}
			pfile_groups = reinterpret_cast<filegroups_t *>(lParam);
			hwndTVCtrl = GetDlgItem(hwndDlg, IDC_GROUPVWR);
			_ASSERTE(hwndTVCtrl != 0);
			if (hwndTVCtrl == NULL) {
				EndDialog(hwndDlg, IDCANCEL);
				return FALSE;
			}
			hwndEditCtrl = NULL;
			for (filegroups_t::const_iterator i = pfile_groups->begin(); i != pfile_groups->end(); ++i) {
				tvis.hParent = TVI_ROOT;
				tvis.hInsertAfter = TVI_SORT;
				tvis.itemex.mask = TVIF_STATE | TVIF_TEXT;
				tvis.itemex.state = 0; //TVIS_EXPANDED;
				tvis.itemex.stateMask = 0;
				tvis.itemex.pszText = const_cast<LPTSTR>(i->first.c_str());
				hParent = TreeView_InsertItem(hwndTVCtrl, &tvis);
				_ASSERTE(hParent != NULL);
				if (hParent == NULL) continue;
				for (filegroups_t::mapped_type::const_iterator j = i->second.begin(); j != i->second.end(); ++j) {
					tvis.hParent = hParent;
					tvis.hInsertAfter = TVI_SORT;
					tvis.itemex.mask = TVIF_TEXT;
					tvis.itemex.pszText = const_cast<LPTSTR>(j->c_str());
					hti = TreeView_InsertItem(hwndTVCtrl, &tvis);
					_ASSERTE(hti != NULL);
				}
				EnableDlgItem(hwndDlg, IDADD, TreeView_GetCount(hwndTVCtrl) > 0);
				EnableDlgItem(hwndDlg, IDREMOVE, TreeView_GetSelection(hwndTVCtrl) != 0);
			}
			static const tooltip_item_t tooltips[] = {
				IDC_GROUPVWR, "You can edit group names or filenames inplace by left clicking or pressing F2 on selected item",
			};
			HWND hwndTT(CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
				WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP | TTS_BALLOON, CW_USEDEFAULT, CW_USEDEFAULT,
				CW_USEDEFAULT, CW_USEDEFAULT, hwndDlg, NULL, hInstance, NULL));
			SetWindowPos(hwndTT, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			SendMessage(hwndTT, TTM_SETMAXTIPWIDTH, 0, static_cast<LPARAM>(400));
			SendMessage(hwndTT, TTM_SETDELAYTIME, static_cast<WPARAM>(TTDT_AUTOPOP), static_cast<LPARAM>(20000));
			TOOLINFO tt;
			memset(&tt, 0, sizeof tt);
			tt.cbSize = sizeof tt;
			tt.uFlags = TTF_SUBCLASS | TTF_IDISHWND | TTF_TRANSPARENT;
			tt.hwnd = hwndDlg;
			tt.hinst = hInstance;
			for (UINT j = 0; j < qnumber(tooltips); ++j) {
				tt.uId = reinterpret_cast<UINT_PTR>(GetDlgItem(hwndDlg, tooltips[j].uID));
				tt.lpszText = const_cast<LPTSTR>(tooltips[j].lpText);
				SendMessage(hwndTT, TTM_ADDTOOL, 0, reinterpret_cast<LPARAM>(&tt));
			}
			return TRUE;
		}
		case WM_CLOSE:
			EndDialog(hwndDlg, LOWORD(wParam));
			return TRUE;
		case WM_COMMAND:
			//if (hwndEditCtrl != NULL) return FALSE;
			switch (HIWORD(wParam)) {
				case BN_CLICKED:
					switch (LOWORD(wParam)) {
						case IDOK:
							if (hwndEditCtrl != NULL) {
								TreeView_EndEditLabelNow(hwndTVCtrl, FALSE);
								SetWindowLong(hwndDlg, DWL_MSGRESULT, TRUE);
								return TRUE;
							}
							_ASSERTE(pfile_groups != 0);
							pfile_groups->clear();
							for (hGroup = TreeView_GetRoot(hwndTVCtrl);
								hGroup != NULL; hGroup = TreeView_GetNextSibling(hwndTVCtrl, hGroup)) {
								tvi.mask = TVIF_HANDLE | TVIF_TEXT;
								tvi.hItem = hGroup;
								tvi.pszText = text;
								tvi.cchTextMax = sizeof text;
								if (TreeView_GetItem(hwndTVCtrl, &tvi)) {
									filegroups_t::iterator i(pfile_groups->insert(pfile_groups->begin(),
										filegroups_t::value_type(text, filegroups_t::mapped_type())));
									_ASSERTE(i != pfile_groups->end());
									filegroups_t::mapped_type *
										pcurrentset(i != pfile_groups->end() ? &i->second : 0);
									if (pcurrentset != 0)
										for (hChild = TreeView_GetChild(hwndTVCtrl, hGroup);
											hChild != NULL; hChild = TreeView_GetNextSibling(hwndTVCtrl, hChild)) {
											tvi.mask = TVIF_HANDLE | TVIF_TEXT;
											tvi.hItem = hChild;
											tvi.pszText = text;
											tvi.cchTextMax = sizeof text;
											if (TreeView_GetItem(hwndTVCtrl, &tvi)) {
												/*if (qfileexist(text)) */pcurrentset->insert(text);
											}
#ifdef _DEBUG
											else
												_RPTF3(_CRT_ERROR, "%s(%08X, WM_COMMAND, ...): TreeView_GetItem(%08X, ...) returned NULL\n",
													__FUNCTION__, hwndDlg, hwndTVCtrl);
#endif // _DEBUG
										}
								}
#ifdef _DEBUG
								else
									_RPTF3(_CRT_ERROR, "%s(%08X, WM_COMMAND, ...): TreeView_GetItem(%08X, ...) returned NULL\n",
										__FUNCTION__, hwndDlg, hwndTVCtrl);
#endif // _DEBUG
							}
						case IDCANCEL:
							if (hwndEditCtrl != NULL)
								TreeView_EndEditLabelNow(hwndTVCtrl, TRUE);
							else
								EndDialog(hwndDlg, LOWORD(wParam));
							SetWindowLong(hwndDlg, DWL_MSGRESULT, 0);
							return TRUE;
						case IDADD: {
							hSel = TreeView_GetSelection(hwndTVCtrl);
							if (hSel == NULL) hSel = TreeView_GetRoot(hwndTVCtrl);
							if (hSel != NULL) {
								hGroup = TreeView_GetParent(hwndTVCtrl, hSel);
								if (hGroup == NULL) hGroup = hSel;
								memset(&ofn, 0, sizeof ofn);
								ofn.lStructSize = sizeof ofn;
								ofn.hInstance = hInstance;
								ofn.hwndOwner = hwndDlg;
								ofn.lpstrTitle = CFileGroups::lpstrTitle;
								boost::scoped_array<char> FileName(new char[0x10000]);
								if (!FileName) {
									_RPTF2(_CRT_ERROR, "%s(...): failed to allocate new string of size 0x%X\n",
										__FUNCTION__, 0x10000);
									SetWindowLong(hwndDlg, DWL_MSGRESULT, 0);
									throw std::bad_alloc(); //break;
								}
								FileName[0] = 0;
								ofn.lpstrFile = FileName.get();
								ofn.nMaxFile = 0x10000;
								ofn.Flags = OFN_ENABLESIZING | OFN_EXPLORER | OFN_FORCESHOWHIDDEN |
									OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |
									OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT;
								ofn.lpstrFilter = CFileGroups::lpstrFilter;
								ofn.nFilterIndex = CFileGroups::nFilterIndex;
								ofn.lpstrDefExt = CFileGroups::lpstrDefExt;
								get_input_file_path(CPY(path));
								_splitpath(path, drive, dir, 0, 0);
								_makepath(path, drive, dir, 0, 0);
								ofn.lpstrInitialDir = path;
								ofn.nMaxFile = 0x10000;
								if (GetOpenFileName(&ofn))
									if (ofn.nFileOffset > strlen(ofn.lpstrFile))
										while (*(ofn.lpstrFile + ofn.nFileOffset)) {
											AddFile(hwndTVCtrl, hGroup, _sprintf("%s\\%s",
												ofn.lpstrFile, ofn.lpstrFile + ofn.nFileOffset).c_str());
											ofn.nFileOffset += strlen(ofn.lpstrFile + ofn.nFileOffset) + 1;
										}
									else
										AddFile(hwndTVCtrl, hGroup, ofn.lpstrFile);
								EnableDlgItem(hwndDlg, IDADD, TRUE);
								EnableDlgItem(hwndDlg, IDREMOVE, TreeView_GetSelection(hwndTVCtrl) != 0);
							}
							SetWindowLong(hwndDlg, DWL_MSGRESULT, 0);
							return TRUE;
						}
						case IDADDGROUP: {
							char *newgroup(askstr(HIST_IDENT, NULL, "New group name"));
							if (newgroup != 0 && strlen(newgroup) > 0) {
								if (strlen(newgroup) >= MAX_PATH) newgroup[MAX_PATH - 1] = 0;
								for (hGroup = TreeView_GetRoot(hwndTVCtrl);
									hGroup != NULL; hGroup = TreeView_GetNextSibling(hwndTVCtrl, hGroup)) {
									tvi.mask = TVIF_HANDLE | TVIF_TEXT;
									tvi.hItem = hGroup;
									tvi.pszText = text;
									tvi.cchTextMax = sizeof text;
									if (TreeView_GetItem(hwndTVCtrl, &tvi)) {
										if (strcmp(newgroup, text) == 0) {
											warning("Group with this name already exists");
											SetWindowLong(hwndDlg, DWL_MSGRESULT, 0);
											return FALSE;
										}
									}
#ifdef _DEBUG
									else
										_RPTF3(_CRT_ERROR, "%s(%08X, WM_COMMAND, ...): TreeView_GetItem(%08X, ...) returned NULL\n",
											__FUNCTION__, hwndDlg, hwndTVCtrl);
#endif // _DEBUG
								}
								tvis.hParent = TVI_ROOT;
								tvis.hInsertAfter = TVI_SORT;
								tvis.itemex.mask = TVIF_STATE | TVIF_TEXT;
								tvis.itemex.state = TVIS_EXPANDED;
								tvis.itemex.stateMask = 0;
								tvis.itemex.pszText = newgroup;
								hti = TreeView_InsertItem(hwndTVCtrl, &tvis);
								_ASSERTE(hti != NULL);
								if (hti != NULL) {
									TreeView_SelectItem(hwndTVCtrl, hti);
									TreeView_Expand(hwndTVCtrl, hti, TVE_EXPAND);
									EnableDlgItem(hwndDlg, IDADD, TRUE);
									EnableDlgItem(hwndDlg, IDREMOVE, TRUE);
								}
							}
							SetWindowLong(hwndDlg, DWL_MSGRESULT, 0);
							return TRUE;
						}
						case IDREMOVE:
							if ((hSel = TreeView_GetSelection(hwndTVCtrl)) != NULL) {
								if ((hParent = TreeView_GetParent(hwndTVCtrl, hSel)) == NULL
									&& TreeView_GetChild(hwndTVCtrl, hSel) != NULL) { // is group
									std::string msg("Are you sure to delete group '");
									tvi.mask = TVIF_HANDLE | TVIF_TEXT;
									tvi.hItem = hSel;
									tvi.pszText = text;
									tvi.cchTextMax = sizeof text;
									if (TreeView_GetItem(hwndTVCtrl, &tvi)) msg.append(text);
									msg.append("' and all it's files?");
									if (MessageBox(hwndDlg, msg.c_str(), "libnames matching",
										MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1) == IDYES)
										TreeView_DeleteItem(hwndTVCtrl, hSel);
								} else  // is file or group has no files - delete without confirmation
									TreeView_DeleteItem(hwndTVCtrl, hSel);
								if (TreeView_GetCount(hwndTVCtrl) <= 0)
									EnableDlgItem(hwndDlg, IDADD, FALSE);
								EnableDlgItem(hwndDlg, IDREMOVE, TreeView_GetSelection(hwndTVCtrl) != NULL);
							}
							SetWindowLong(hwndDlg, DWL_MSGRESULT, 0);
							return TRUE;
					}
					break;
			}
			break;
		case WM_NOTIFY:
			_ASSERTE(lParam != NULL);
			if (lParam != NULL) {
//  				OutputDebugString("%s(%08X, WM_NOTIFY, ...): hwndFrom=%08X idFrom=%u code=0x%X",
//  					__FUNCTION__, hwndDlg, reinterpret_cast<LPNMHDR>(lParam)->hwndFrom, reinterpret_cast<LPNMHDR>(lParam)->idFrom,
// 					reinterpret_cast<LPNMHDR>(lParam)->code);
				switch (reinterpret_cast<LPNMHDR>(lParam)->idFrom) {
					case IDC_GROUPVWR:
						switch (reinterpret_cast<LPNMHDR>(lParam)->code) {
							case TVN_KEYDOWN:
								switch (reinterpret_cast<LPNMTVKEYDOWN>(lParam)->wVKey) {
									case VK_F2:
										if ((hSel = TreeView_GetSelection(hwndTVCtrl)) != NULL)
											TreeView_EditLabel(hwndTVCtrl, hSel);
										SetWindowLong(hwndDlg, DWL_MSGRESULT, TRUE);
										return TRUE;
									case VK_INSERT:
										SendMessage(hwndDlg, WM_COMMAND,
											(hSel = TreeView_GetSelection(hwndTVCtrl)) != NULL
											&& TreeView_GetParent(hwndTVCtrl, hSel) != NULL ?
											MAKELONG(IDADD, BN_CLICKED) : MAKELONG(IDADDGROUP, BN_CLICKED),
											reinterpret_cast<LPARAM>(hwndTVCtrl));
										SetWindowLong(hwndDlg, DWL_MSGRESULT, TRUE);
										return TRUE;
									case VK_DELETE:
										SendMessage(hwndDlg, WM_COMMAND, MAKELONG(IDREMOVE, BN_CLICKED),
											reinterpret_cast<LPARAM>(hwndTVCtrl));
										SetWindowLong(hwndDlg, DWL_MSGRESULT, TRUE);
										return TRUE;
								}
								break;
							case TVN_BEGINLABELEDIT: {
								if ((hSel = TreeView_GetSelection(hwndTVCtrl)) != NULL
									&& TreeView_GetParent(hwndTVCtrl, hSel) != NULL) {
									tvi.mask = TVIF_HANDLE | TVIF_TEXT;
									tvi.hItem = hSel;
									tvi.pszText = text;
									tvi.cchTextMax = sizeof text;
									if (TreeView_GetItem(hwndTVCtrl, &tvi)) {
										memset(&ofn, 0, sizeof ofn);
										ofn.lStructSize = sizeof ofn;
										ofn.lpstrFile = text;
										ofn.nMaxFile = sizeof text;
										_splitpath(text, drive, dir, 0, ext);
										_makepath(path, drive, dir, 0, 0);
										ofn.lpstrInitialDir = path;
										ofn.hwndOwner = hwndDlg;
										ofn.hInstance = hInstance;
										ofn.Flags = OFN_ENABLESIZING | OFN_EXPLORER | OFN_FORCESHOWHIDDEN |
											OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST |
											OFN_HIDEREADONLY;
										ofn.lpstrTitle = "Change file's location";
										ofn.lpstrFilter = "all files\0*.*\0";
										ofn.nFilterIndex = 1;
										ofn.lpstrDefExt = ext;
										if (GetOpenFileName(&ofn)) {
											tvi.mask = TVIF_HANDLE | TVIF_TEXT;
											TreeView_SetItem(hwndTVCtrl, &tvi);
										}
										SetWindowLong(hwndDlg, DWL_MSGRESULT, TRUE);
										return TRUE;
									}
#ifdef _DEBUG
									else
										_RPTF2(_CRT_WARN, "%s(...): TreeView_GetItem(%08X, ...) returned NULL",
											__FUNCTION__, hwndTVCtrl);
#endif // _DEBUG
								}
								hwndEditCtrl = TreeView_GetEditControl(hwndTVCtrl);
								_ASSERTE(hwndEditCtrl != NULL);
								SendMessage(hwndEditCtrl, EM_LIMITTEXT, MAX_PATH - 1, 0);
								SetWindowLong(hwndDlg, DWL_MSGRESULT, FALSE);
								return TRUE;
							}
							case TVN_ENDLABELEDIT:
								hwndEditCtrl = NULL;
								SetWindowLong(hwndDlg, DWL_MSGRESULT,
									reinterpret_cast<LPNMTVDISPINFO>(lParam)->item.pszText != NULL
									&& strlen(reinterpret_cast<LPNMTVDISPINFO>(lParam)->item.pszText) > 0
									&& strlen(reinterpret_cast<LPNMTVDISPINFO>(lParam)->item.pszText) < MAX_PATH);
								return TRUE;
							case TVN_SELCHANGED:
								EnableDlgItem(hwndDlg, IDREMOVE, TreeView_GetSelection(hwndTVCtrl) != 0);
								return TRUE;
							//case WM_LBUTTONDBLCLCK:
							//	break;
						} // switch code
						break;
				} // switch idFrom
			} // lParam != NULL
			break;
	} // main switch
	return 0;
}