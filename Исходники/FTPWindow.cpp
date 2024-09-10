LRESULT FTPWindow::MessageProc(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	bool doDefaultProc = false;
	LRESULT result = 0;

	switch(uMsg) {
		case WM_SETFOCUS: {
			//Why restore focus here? This window should never be able to get focus in the first place
			HWND hPrev = (HWND)wParam;
			if (hPrev != NULL)
				::SetFocus(hPrev);
			break; }
		case WM_ERASEBKGND: {
			HDC hDC = (HDC) wParam;
			RECT rectClient;
			GetClientRect(m_hwnd, &rectClient);
			FillRect(hDC, &rectClient, m_backgroundBrush);
			result = TRUE;
			break; }
		case WM_SETCURSOR: {
			if (m_splitter.OnSetCursor()) {
				return TRUE;
			}
			return FALSE;
			break; }
		case WM_CAPTURECHANGED: {
			m_splitter.OnCaptureChanged((HWND)lParam);
			break; }
		case WM_LBUTTONDOWN: {
			m_splitter.OnButtonDown();
			break; }
		case WM_LBUTTONUP: {
			m_splitter.OnButtonUp();
			m_ftpSettings->SetSplitRatio(m_splitter.GetRatio());
			break; }
		case WM_MOUSEMOVE: {
			if (wParam & MK_LBUTTON) {
				m_splitter.OnMouseMove();
			}
			break; }
		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case IDM_POPUP_QUEUE_ABORT: {
					if (m_cancelOperation && m_cancelOperation->GetRunning()) {
						m_ftpSession->AbortTransfer();
					}
					m_cancelOperation = NULL;
					result = TRUE;
					break; }
				case IDM_POPUP_QUEUE_CANCEL: {
					if (m_cancelOperation && !m_cancelOperation->GetRunning()) {
						m_ftpSession->CancelOperation(m_cancelOperation);
					}
					m_cancelOperation = NULL;
					result = TRUE;
					break; }
				case IDM_POPUP_LINKTYPE: {
					m_currentSelection->SetDir(!m_currentSelection->isDir());
					m_currentSelection->GetParent()->Sort();
					m_treeview.UpdateFileObject(m_currentSelection);
					result = TRUE;
					break; }
				case IDB_BUTTON_TOOLBAR_CONNECT: {
					//Called by chevron popup: disconnect (ie no popup)
					//disconnect();
					result = TRUE;
					break;}

                case IDB_BUTTON_TOOLBAR_OPENDIR: {

                    // Show the dialog to get input directory name from the user.
                    InputDialog id;
                    int res = id.Create(m_hwnd, TEXT("Open Directory"), TEXT("Enter directory name:"), TEXT(""));
                    if (res != 1) {
                        return 0;
                    }

                    // Read the input directory name.
                    const TCHAR *dirName    = id.GetValue();
                    char *dirNameCP         = SU::TCharToCP(dirName, CP_ACP);

                    m_ftpSession->GetDirectoryHierarchy(dirNameCP);
                    break;
                }

				case IDM_POPUP_DOWNLOADFILE:
				case IDB_BUTTON_TOOLBAR_DOWNLOAD: {
					SHORT state = GetKeyState(VK_CONTROL);
					if (!(state & 0x8000)) {
						m_ftpSession->DownloadFileCache(m_currentSelection->GetPath());
						result = TRUE;
						break;
					}
					//else fallthrough
					}
				case IDM_POPUP_DLDTOLOCATION: {
					TCHAR target[MAX_PATH];
					lstrcpy(target, m_currentSelection->GetLocalName());
					int res = PU::GetSaveFilename(target, MAX_PATH, m_hwnd);
					if (res == 0) {
						m_ftpSession->DownloadFile(m_currentSelection->GetPath(), target, false);
					}
					result = TRUE;
					break; }
				case IDM_POPUP_UPLOADFILE:
				case IDB_BUTTON_TOOLBAR_UPLOAD: {
					//upload(TRUE, TRUE);		//upload to cached folder is present, else upload to last selected folder
					//m_ftpSession->UploadFile();
					TCHAR source[MAX_PATH];
					BOOL doUpload = FALSE;
					SHORT state = GetKeyState(VK_CONTROL);
					if ((state & 0x8000) && LOWORD(wParam) == IDB_BUTTON_TOOLBAR_UPLOAD) {
						source[0] = 0;
						int res = PU::GetOpenFilename(source, MAX_PATH, m_hParent);
						if (res == 0)
							doUpload = TRUE;
					} else {
						doUpload = ::SendMessage(m_hNpp, NPPM_GETFULLCURRENTPATH, (WPARAM)MAX_PATH, (LPARAM)source);
					}
					if (doUpload == TRUE) {
						if (m_currentSelection->isDir()) {
							m_ftpSession->UploadFile(source, m_currentSelection->GetPath(), true);
						} else {
							m_ftpSession->UploadFile(source, m_currentSelection->GetParent()->GetPath(), true);
						}
					}
					result = TRUE;
					break;}
				case IDM_POPUP_UPLOADOTHERFILE: {
					TCHAR source[MAX_PATH];
					source[0] = 0;
					int res = PU::GetOpenFilename(source, MAX_PATH, m_hwnd);
					if (res == 0) {
						m_ftpSession->UploadFile(source, m_currentSelection->GetPath(), true);
					}
					result = TRUE;
					break; }
				case IDM_POPUP_REFRESHDIR:
				case IDB_BUTTON_TOOLBAR_REFRESH: {
					m_ftpSession->GetDirectory(m_currentSelection->GetPath());
					result = TRUE;
					break; }
				case IDB_BUTTON_TOOLBAR_ABORT: {
					m_ftpSession->AbortTransfer();
					result = TRUE;
					break; }
				case IDB_BUTTON_TOOLBAR_RAWCMD: {
					//rawCommand();
					result = TRUE;
					break; }
				case IDB_BUTTON_TOOLBAR_SETTINGS: {
					//Should be handled by dropdown
					result = TRUE;
					break; }
				case IDB_BUTTON_TOOLBAR_MESSAGES: {
					m_outputShown = !m_outputWindow.IsVisible();
					m_outputWindow.Show(m_outputShown);
					result = TRUE;
					break; }
				case IDM_POPUP_NEWDIR: {
					this->CreateDirectory(m_currentSelection);
					result = TRUE;
					break; }
				case IDM_POPUP_DELETEDIR: {
					this->DeleteDirectory(m_currentSelection);
					result = TRUE;
					break; }
				case IDM_POPUP_NEWFILE: {
					this->CreateFile(m_currentSelection);
					result = TRUE;
					break; }
				case IDM_POPUP_DELETEFILE: {
					this->DeleteFile(m_currentSelection);
					result = TRUE;
					break; }
				case IDM_POPUP_RENAMEFILE:
				case IDM_POPUP_RENAMEDIR: {
					this->Rename(m_currentSelection);
					result = TRUE;
					break; }
				case IDM_POPUP_SETTINGSGENERAL: {
					m_settingsDialog.Create(m_hwnd, m_ftpSettings);
					result = TRUE;
					break; }
				case IDM_POPUP_SETTINGSPROFILE: {
					m_profilesDialog.Create(m_hwnd, this, m_vProfiles, m_ftpSettings->GetGlobalCache());
					result = TRUE;
					break; }
				default: {
					unsigned int value = LOWORD(wParam);
					if (!m_busy && value >= IDM_POPUP_PROFILE_FIRST && value <= IDM_POPUP_PROFILE_MAX) {
						FTPProfile * profile = m_vProfiles->at(value - IDM_POPUP_PROFILE_FIRST);
						int ret = m_ftpSession->StartSession(profile);
						if (ret == -1) {
							OutErr("[NppFTP] Cannot start FTP session");
							result = TRUE;
							break;
						}
						m_ftpSession->Connect();
						result = TRUE;
					} else {
						doDefaultProc = true;
					}
					break; }
			}
			break; }
		case WM_NOTIFY: {
			NMHDR nmh = (NMHDR) *((NMHDR*)lParam);
			if (nmh.hwndFrom == m_toolbar.GetHWND()) {
				switch(nmh.code) {
					case TBN_DROPDOWN: {
						NMTOOLBAR * pnmtb = (NMTOOLBAR*)lParam;
						switch(pnmtb->iItem) {
							case IDB_BUTTON_TOOLBAR_CONNECT: {
								if (m_ftpSession->IsConnected()) {	//only call disconnect routine to disconnect, else pick profile
									m_ftpSession->TerminateSession();
									return TBDDRET_DEFAULT;
								}
								result = m_toolbar.DoDropDown(IDB_BUTTON_TOOLBAR_CONNECT);
								break; }
							case IDB_BUTTON_TOOLBAR_SETTINGS: {
								result = m_toolbar.DoDropDown(IDB_BUTTON_TOOLBAR_SETTINGS);
								break; }
							default: {
								result = TBDDRET_NODEFAULT;
								break; }
						}
						break; }
					default: {
						doDefaultProc = true;
						break; }
				}
			} else if (nmh.hwndFrom == m_hNpp) {
				return DockableWindow::MessageProc(uMsg, wParam, lParam);
			} else if (nmh.hwndFrom == m_treeview.GetHWND()) {
				switch(nmh.code) {
					case TVN_SELCHANGED: {
						const NM_TREEVIEW & nmt = (NM_TREEVIEW) *(NM_TREEVIEW*)lParam;
						m_currentSelection = m_treeview.GetItemFileObject(nmt.itemNew.hItem);
						SetToolbarState();
						result = TRUE;
						break; }
					case TVN_ITEMEXPANDING: {
						const NM_TREEVIEW & nmt = (NM_TREEVIEW) *(NM_TREEVIEW*)lParam;
						int res = m_treeview.OnExpanding(&nmt);
						if (res == TRUE) {
							FileObject * fo = (FileObject*) nmt.itemNew.lParam;
							m_ftpSession->GetDirectory(fo->GetPath());
						}
						return res;
						break; }
					case TVN_GETDISPINFO: {
						TV_DISPINFO * ptvdi = (TV_DISPINFO*)lParam;
						m_treeview.GetDispInfo(ptvdi);
						result = TRUE;
						break; }
					case NM_RCLICK:
					case NM_DBLCLK:
					case NM_CLICK: {
						HTREEITEM res = m_treeview.OnClick();
						if (res) {
							m_currentSelection = m_treeview.GetItemFileObject(res);
							SetToolbarState();
							if (nmh.code == (UINT)NM_DBLCLK) {
								OnItemActivation();
								result = TRUE;
							}
						}
						break; }
					case NM_RETURN: {
						OnItemActivation();
						result = TRUE;	//handle message
						break; }
					case TVN_SELCHANGING: {
						result = FALSE;
						break; }
					case TVN_BEGINDRAG: {
						result = FALSE;
/*
						if (m_currentDropObject != NULL) {	//currently only one queued DnD op is supported
							result = FALSE;
							break;
						}
						NMTREEVIEW * pnmtv = (NMTREEVIEW*)lParam;
						HTREEITEM hti = pnmtv->itemNew.hItem;
						FileObject * fo = m_treeview.GetItemFileObject(hti);
						if (fo != NULL) {
							m_currentDropObject = fo;
							m_dndWindow.Create(m_hwnd);
							::PostMessage(m_dndWindow.GetHWND(), WM_DND, 0, 0);
							result = TRUE;
						}
*/
						break; }
					default: {
						doDefaultProc = true;
						break; }
				}
			} else if (nmh.hwndFrom == m_rebar.GetHWND()) {
				switch(nmh.code) {
					case RBN_CHEVRONPUSHED: {
						NMREBARCHEVRON * lpnm = (NMREBARCHEVRON*) lParam;
						POINT pt;
						pt.x = lpnm->rc.left;//right;
						pt.y = lpnm->rc.bottom;
						ClientToScreen(m_rebar.GetHWND(), &pt);
						m_toolbar.DoPopop(pt);
						result = TRUE;
						break; }
					default: {
						doDefaultProc = true;
						break; }
				}
			} else {
				switch(nmh.code) {
					case TTN_GETDISPINFO: {
						LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT) lParam;
						lpttt->hinst = NULL;
						lpttt->lpszText = (TCHAR*)m_toolbar.GetTooltip(lpttt->hdr.idFrom);
						result = TRUE;
						break; }
					default: {
						doDefaultProc = true;
						break; }
				}
			}
			break; }
		case WM_CONTEXTMENU: {
			HWND hWinContext = (HWND)wParam;
			HMENU hContext = NULL;

			POINT menuPos;
			menuPos.x = GET_X_LPARAM(lParam);
			menuPos.y = GET_Y_LPARAM(lParam);
			bool fromKeyboard = (menuPos.x == -1 && menuPos.y == -1);
			if (fromKeyboard) {	//keyboard activation
				DWORD pos = GetMessagePos();
				menuPos.x = GET_X_LPARAM(pos);
				menuPos.y = GET_Y_LPARAM(pos);

			}

			if (hWinContext == m_treeview.GetHWND()) {
				if (!m_currentSelection) {
					result = FALSE;
					break;
				}

				if (fromKeyboard) {
					RECT treerect;
					bool res = m_treeview.GetObjectItemRect(m_currentSelection, &treerect);
					if (res) {
						menuPos.x = treerect.left;
						menuPos.y = treerect.bottom;
						::ClientToScreen(m_treeview.GetHWND(), &menuPos);
					}
				}

				SHORT state = GetKeyState(VK_SHIFT);
				if ((state & 0x8000) && m_currentSelection->isLink() && !fromKeyboard) {
					hContext = m_popupLink;
				} else if (m_currentSelection->isDir()) {
					hContext = m_popupDir;
				} else {
					hContext = m_popupFile;
				}
			} else if (hWinContext == m_queueWindow.GetHWND()) {
				QueueOperation * op = m_queueWindow.GetSelectedQueueOperation();
				if (!op) {
					result = FALSE;
					break;
				}

				m_cancelOperation = op;
				bool run = op->GetRunning();

				if (fromKeyboard) {
					RECT queuerect;
					bool res = m_queueWindow.GetSelectedQueueRect(&queuerect);
					if (res) {
						menuPos.x = queuerect.left;
						menuPos.y = queuerect.bottom;
						::ClientToScreen(m_queueWindow.GetHWND(), &menuPos);
					}
				}

				if (run) {
					hContext = m_popupQueueActive;
				} else {
					hContext = m_popupQueueHold;
				}
			}

			if (!hContext) {
				result = FALSE;
				break;
			}

			::TrackPopupMenu(hContext, TPM_LEFTALIGN, menuPos.x, menuPos.y, 0, m_hwnd, NULL);
			result = TRUE;
			break; }
		case WM_OUTPUTSHOWN: {
			if (wParam == TRUE) {
				m_outputShown = true;
				m_toolbar.SetChecked(IDB_BUTTON_TOOLBAR_MESSAGES, TRUE);
				m_ftpSettings->SetOutputShown(true);
			} else {
				m_outputShown = false;
				m_toolbar.SetChecked(IDB_BUTTON_TOOLBAR_MESSAGES, FALSE);
				m_ftpSettings->SetOutputShown(false);
			}
			break; }
		case NotifyMessageStart:
		case NotifyMessageEnd: {
			bool isStart = (uMsg == (UINT)NotifyMessageStart);
			int code = (int)wParam;
			QueueOperation * queueOp = (QueueOperation*)lParam;
			void * notifyData = queueOp->GetNotifyData();
			int res = OnEvent(queueOp, code, notifyData, isStart);
			if (res != 1)	//if res == 1, then queueop becomes invalid
				queueOp->AckNotification();
			return TRUE;
			break;}
		case NotifyMessageAdd: {
			QueueOperation * queueOp = (QueueOperation*)lParam;
			m_queueWindow.PushQueueItem(queueOp);
			queueOp->AckNotification();
			return TRUE;
			break; }
		case NotifyMessageRemove: {
			QueueOperation * queueOp = (QueueOperation*)lParam;
			m_queueWindow.RemoveQueueItem(queueOp);
			queueOp->AckNotification();
			return TRUE;
			break; }
		case NotifyMessageProgress: {
			QueueOperation * queueOp = (QueueOperation*)lParam;
			m_queueWindow.ProgressQueueItem(queueOp);
			queueOp->AckNotification();
			break; }
		default:
			doDefaultProc = true;
			break;
	}

	if (doDefaultProc)
		result = DockableWindow::MessageProc(uMsg, wParam, lParam);

	return result;
}