LONG_PTR CALLBACK HotkeyHandlerDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINT ptLast;
	static int iMousedown;

	if (msg == WM_TASKBARCREATED) {
		CreateSystrayIcon(FALSE);
		if (nen_options.bTraySupport)
			CreateSystrayIcon(TRUE);
		return 0;
	}
	switch (msg) {
		case WM_CREATE:
			int i;

			for(i = 0; i < safe_sizeof(_hotkeydescs); i++) {
				_hotkeydescs[i].cbSize = sizeof(HOTKEYDESC);
				CallService(MS_HOTKEY_REGISTER, 0, (LPARAM)&_hotkeydescs[i]);
			}

			WM_TASKBARCREATED = RegisterWindowMessageA("TaskbarCreated");
			ShowWindow(hwndDlg, SW_HIDE);
			hSvcHotkeyProcessor = CreateServiceFunction(MS_TABMSG_HOTKEYPROCESS, HotkeyProcessor);
			SetTimer(hwndDlg, TIMERID_SENDLATER, TIMEOUT_SENDLATER, NULL);
			break;
		case WM_HOTKEY: {
			CLISTEVENT *cli = 0;

			cli = (CLISTEVENT *)CallService(MS_CLIST_GETEVENT, (WPARAM)INVALID_HANDLE_VALUE, (LPARAM)0);
			if (cli != NULL) {
				if (strncmp(cli->pszService, "SRMsg/TypingMessage", strlen(cli->pszService))) {
					CallService(cli->pszService, 0, (LPARAM)cli);
					break;
				}
			}
			if (wParam == 0xc001)
				SendMessage(hwndDlg, DM_TRAYICONNOTIFY, 101, WM_MBUTTONDOWN);

			break;
		}
		/*
		 * handle the popup menus (session list, favorites, recents...
		 * just draw some icons, nothing more :)
		 */
		case WM_MEASUREITEM: {
			LPMEASUREITEMSTRUCT lpmi = (LPMEASUREITEMSTRUCT) lParam;
			lpmi->itemHeight = 0;
			lpmi->itemWidth = 6;
			return TRUE;
		}
		case WM_DRAWITEM: {
			LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT) lParam;
			struct TWindowData *dat = 0;
			if (dis->CtlType == ODT_MENU && (dis->hwndItem == (HWND)PluginConfig.g_hMenuFavorites || dis->hwndItem == (HWND)PluginConfig.g_hMenuRecent)) {
				HICON hIcon = (HICON)dis->itemData;

				DrawMenuItem(dis, hIcon, 0);
				return TRUE;
			} else if (dis->CtlType == ODT_MENU) {
				HWND hWnd = M->FindWindow((HANDLE)dis->itemID);
				DWORD idle = 0;

				if (hWnd == NULL) {
					SESSION_INFO *si = SM_FindSessionByHCONTACT((HANDLE)dis->itemID);

					hWnd = si ? si->hWnd : 0;
				}

				if (hWnd)
					dat = (struct TWindowData *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

				if (dis->itemData >= 0) {
					HICON hIcon;
					BOOL fNeedFree = FALSE;

					if (dis->itemData > 0)
						hIcon = dis->itemData & 0x10000000 ? hIcons[ICON_HIGHLIGHT] : PluginConfig.g_IconMsgEvent;
					else if (dat != NULL) {
						hIcon = MY_GetContactIcon(dat);
						idle = dat->idle;
					} else
						hIcon = PluginConfig.g_iconContainer;

					DrawMenuItem(dis, hIcon, idle);
					if (fNeedFree)
						DestroyIcon(hIcon);

					return TRUE;
				}
			}
		}
		break;
		case DM_TRAYICONNOTIFY: {
			int iSelection;

			if (wParam == 100 || wParam == 101) {
				switch (lParam) {
					case WM_LBUTTONUP: {
						POINT pt;
						GetCursorPos(&pt);
						if (wParam == 100)
							SetForegroundWindow(hwndDlg);
						if (GetMenuItemCount(PluginConfig.g_hMenuTrayUnread) > 0) {
							iSelection = TrackPopupMenu(PluginConfig.g_hMenuTrayUnread, TPM_RETURNCMD, pt.x, pt.y, 0, hwndDlg, NULL);
							HandleMenuEntryFromhContact(iSelection);
						} else
							TrackPopupMenu(GetSubMenu(PluginConfig.g_hMenuContext, 8), TPM_RETURNCMD, pt.x, pt.y, 0, hwndDlg, NULL);
						if (wParam == 100)
							PostMessage(hwndDlg, WM_NULL, 0, 0);
						break;
					}
					case WM_MBUTTONDOWN: {
						MENUITEMINFOA mii = {0};
						int i, iCount = GetMenuItemCount(PluginConfig.g_hMenuTrayUnread);

						if (wParam == 100)
							SetForegroundWindow(hwndDlg);

						if (iCount > 0) {
							UINT uid = 0;
							mii.fMask = MIIM_DATA;
							mii.cbSize = sizeof(mii);
							i = iCount - 1;
							do {
								GetMenuItemInfoA(PluginConfig.g_hMenuTrayUnread, i, TRUE, &mii);
								if (mii.dwItemData > 0) {
									uid = GetMenuItemID(PluginConfig.g_hMenuTrayUnread, i);
									HandleMenuEntryFromhContact(uid);
									break;
								}
							} while (--i >= 0);
							if (uid == 0 && pLastActiveContainer != NULL) {                // no session found, restore last active container
								if (IsIconic(pLastActiveContainer->hwnd) || !IsWindowVisible(pLastActiveContainer->hwnd)) {
									SendMessage(pLastActiveContainer->hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
									SetForegroundWindow(pLastActiveContainer->hwnd);
								} else {
									if(PluginConfig.m_HideOnClose)
										ShowWindow(pLastActiveContainer->hwnd, SW_HIDE);
									else
										SendMessage(pLastActiveContainer->hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
								}
							}
						}
						if (wParam == 100)
							PostMessage(hwndDlg, WM_NULL, 0, 0);
						break;
					}
					case WM_RBUTTONUP: {
						HMENU submenu = PluginConfig.g_hMenuTrayContext;
						POINT pt;

						if (wParam == 100)
							SetForegroundWindow(hwndDlg);
						GetCursorPos(&pt);
						CheckMenuItem(submenu, ID_TRAYCONTEXT_DISABLEALLPOPUPS, MF_BYCOMMAND | (nen_options.iDisable ? MF_CHECKED : MF_UNCHECKED));
						CheckMenuItem(submenu, ID_TRAYCONTEXT_DON40223, MF_BYCOMMAND | (nen_options.iNoSounds ? MF_CHECKED : MF_UNCHECKED));
						CheckMenuItem(submenu, ID_TRAYCONTEXT_DON, MF_BYCOMMAND | (nen_options.iNoAutoPopup ? MF_CHECKED : MF_UNCHECKED));
						EnableMenuItem(submenu, ID_TRAYCONTEXT_HIDEALLMESSAGECONTAINERS, MF_BYCOMMAND | (nen_options.bTraySupport) ? MF_ENABLED : MF_GRAYED);
						CheckMenuItem(submenu, ID_TRAYCONTEXT_SHOWTHETRAYICON, MF_BYCOMMAND | (nen_options.bTraySupport ? MF_CHECKED : MF_UNCHECKED));
						iSelection = TrackPopupMenu(submenu, TPM_RETURNCMD, pt.x, pt.y, 0, hwndDlg, NULL);

						if (iSelection) {
							MENUITEMINFO mii = {0};

							mii.cbSize = sizeof(mii);
							mii.fMask = MIIM_DATA | MIIM_ID;
							GetMenuItemInfo(submenu, (UINT_PTR)iSelection, FALSE, &mii);
							if (mii.dwItemData != 0) {                      // this must be an itm of the fav or recent menu
								HandleMenuEntryFromhContact(iSelection);
							} else {
								switch (iSelection) {
									case ID_TRAYCONTEXT_SHOWTHETRAYICON:
										nen_options.bTraySupport = !nen_options.bTraySupport;
										CreateSystrayIcon(nen_options.bTraySupport ? TRUE : FALSE);
										break;
									case ID_TRAYCONTEXT_DISABLEALLPOPUPS:
										nen_options.iDisable ^= 1;
										break;
									case ID_TRAYCONTEXT_DON40223:
										nen_options.iNoSounds ^= 1;
										break;
									case ID_TRAYCONTEXT_DON:
										nen_options.iNoAutoPopup ^= 1;
										break;
									case ID_TRAYCONTEXT_HIDEALLMESSAGECONTAINERS: {
										struct TContainerData *pContainer = pFirstContainer;

										while (pContainer) {
											ShowWindow(pContainer->hwnd, SW_HIDE);
											pContainer = pContainer->pNextContainer;
										}
										break;
									}
									case ID_TRAYCONTEXT_RESTOREALLMESSAGECONTAINERS: {
										struct TContainerData *pContainer = pFirstContainer;

										while (pContainer) {
											ShowWindow(pContainer->hwnd, SW_SHOW);
											pContainer = pContainer->pNextContainer;
										}
										break;
									}
									case ID_TRAYCONTEXT_BE: {
										struct TContainerData *pContainer = pFirstContainer;

										nen_options.iDisable = 1;
										nen_options.iNoSounds = 1;
										nen_options.iNoAutoPopup = 1;

										while (pContainer) {
											SendMessage(pContainer->hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 1);
											pContainer = pContainer->pNextContainer;
										}
										break;
									}
								}
							}
						}
						if (wParam == 100)
							PostMessage(hwndDlg, WM_NULL, 0, 0);
						break;
					}
					default:
						break;
				}
			}
			break;
		}
		/*
		 * handle an event from the popup module (mostly window activation). Since popups may run in different threads, the message
		 * is posted to our invisible hotkey handler which does always run within the main thread.
		 * wParam is the hContact
		 * lParam the event handle
		 */
		case DM_HANDLECLISTEVENT: {
			CLISTEVENT *cle = (CLISTEVENT *)CallService(MS_CLIST_GETEVENT, wParam, 0);

			/*
			 * if lParam == NULL, don't consider clist events, just open the message tab
			 */

			if(lParam == 0) {
				HandleMenuEntryFromhContact((int)wParam);
				break;
			}

			/*
			 * first try, if the clist returned an event...
			 */
			if (cle) {
				if (ServiceExists(cle->pszService)) {
					CallService(cle->pszService, (WPARAM)NULL, (LPARAM)cle);
					CallService(MS_CLIST_REMOVEEVENT, (WPARAM)cle->hContact, (LPARAM)cle->hDbEvent);
				}
			} else {             // still, we got that message posted.. the event may be waiting in tabSRMMs tray...
				HandleMenuEntryFromhContact((int)wParam);
			}
			break;
		}
		case DM_DOCREATETAB: {
			HWND hWnd = M->FindWindow((HANDLE)lParam);
			if (hWnd && IsWindow(hWnd)) {
				struct TContainerData *pContainer = 0;

				SendMessage(hWnd, DM_QUERYCONTAINER, 0, (LPARAM)&pContainer);
				if (pContainer) {
					int iTabs = TabCtrl_GetItemCount(GetDlgItem(pContainer->hwnd, IDC_MSGTABS));
					if (iTabs == 1)
						SendMessage(pContainer->hwnd, WM_CLOSE, 0, 1);
					else
						SendMessage(hWnd, WM_CLOSE, 0, 1);

					CreateNewTabForContact((struct TContainerData *)wParam, (HANDLE)lParam, 0, NULL, TRUE, TRUE, FALSE, 0);
				}
			}
			break;
		}
		case DM_DOCREATETAB_CHAT: {
			SESSION_INFO *si = SM_FindSessionByHWND((HWND)lParam);

			if (si && IsWindow(si->hWnd)) {
				struct TContainerData *pContainer = 0;

				SendMessage(si->hWnd, DM_QUERYCONTAINER, 0, (LPARAM)&pContainer);
				if (pContainer) {
					int iTabs = TabCtrl_GetItemCount(GetDlgItem(pContainer->hwnd, 1159));
					if (iTabs == 1)
						SendMessage(pContainer->hwnd, WM_CLOSE, 0, 1);
					else
						SendMessage(si->hWnd, WM_CLOSE, 0, 1);

					si->hWnd = CreateNewRoom((struct TContainerData *)wParam, si, TRUE, 0, 0);
				}
			}
			break;
		}
		case DM_SENDMESSAGECOMMANDW:
			SendMessageCommand_W(wParam, lParam);
			if (lParam)
				free((void *)lParam);
			return(0);

		case DM_SENDMESSAGECOMMAND:
			SendMessageCommand(wParam, lParam);
			if (lParam)
				free((void *)lParam);
			return(0);
			/*
			* sent from the popup to "dismiss" the event. we should do this in the main thread
			*/
		case DM_REMOVECLISTEVENT:
			CallService(MS_CLIST_REMOVEEVENT, wParam, lParam);
			CallService(MS_DB_EVENT_MARKREAD, wParam, lParam);
			return(0);

		case DM_SETLOCALE: {
			HKL 	hkl = (HKL)lParam;
			HANDLE 	hContact = (HANDLE)wParam;

			HWND	hWnd = M->FindWindow(hContact);

			if(hWnd) {
				TWindowData *dat = (TWindowData *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
				if(dat) {
					DBVARIANT  dbv;

					if(hkl) {
						dat->hkl = hkl;
						PostMessage(dat->hwnd, DM_SETLOCALE, 0, 0);
					}
					if(0 == M->GetTString(hContact, SRMSGMOD_T, "locale", &dbv)) {
						GetLocaleID(dat, dbv.ptszVal);
						DBFreeVariant(&dbv);
						UpdateReadChars(dat);
					}
				}
			}
			return(0);
		}
		/*
		 * react to changes in the desktop composition state
		 * (enable/disable DWM, change to a non-aero visual style
		 * or classic Windows theme
		 */
		case WM_DWMCOMPOSITIONCHANGED: {
			bool fNewAero = M->getAeroState();					// refresh dwm state
			SendMessage(hwndDlg, WM_THEMECHANGED, 0, 0);
			TContainerData *pContainer = pFirstContainer;

			while (pContainer) {
				if(fNewAero)
					SetAeroMargins(pContainer);
				else {
					MARGINS m = {0};

					if(M->m_pfnDwmExtendFrameIntoClientArea)
						M->m_pfnDwmExtendFrameIntoClientArea(pContainer->hwnd, &m);
				}
				if(pContainer->SideBar->isActive())
					RedrawWindow(GetDlgItem(pContainer->hwnd, 5000), NULL, NULL, RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW);			// the container for the sidebar buttons
				RedrawWindow(pContainer->hwnd, NULL, NULL, RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ALLCHILDREN);
				pContainer = pContainer->pNextContainer;
			}
			M->BroadcastMessage(WM_DWMCOMPOSITIONCHANGED, 0, 0);
			break;
		}

		/*
		 * this message is fired when the user changes desktop color
		 * settings (Desktop->personalize)
		 * the handler reconfigures the aero-related skin images for
		 * tabs and buttons to match the new desktop color theme.
		 */
		case WM_DWMCOLORIZATIONCOLORCHANGED: {
			M->getAeroState();
			Skin->setupAeroSkins();
			CSkin::initAeroEffect();
			break;
		}
		
		/*
		 * user has changed the visual style or switched to/from
		 * classic Windows theme
		 */
		case WM_THEMECHANGED: {
			struct TContainerData *pContainer = pFirstContainer;

			M->getAeroState();
			Skin->setupTabCloseBitmap();
			CSkin::initAeroEffect();
			PluginConfig.m_ncm.cbSize = sizeof(NONCLIENTMETRICS);
			SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &PluginConfig.m_ncm, 0);
			FreeTabConfig();
			ReloadTabConfig();
			while (pContainer) {
				SendMessage(GetDlgItem(pContainer->hwnd, IDC_MSGTABS), EM_THEMECHANGED, 0, 0);
				BroadCastContainer(pContainer, EM_THEMECHANGED, 0, 0);
				pContainer = pContainer->pNextContainer;
			}
			break;
		}

		case DM_SPLITSENDACK: {
			ACKDATA ack = {0};
			struct SendJob *job = sendQueue->getJobByIndex((int)wParam);

			ack.hContact = job->hOwner;
			ack.hProcess = job->hSendId;
			ack.type = ACKTYPE_MESSAGE;
			ack.result = ACKRESULT_SUCCESS;

			if (job->hOwner && job->iAcksNeeded && job->hOwner && job->iStatus == SendQueue::SQ_INPROGRESS) {
				if (IsWindow(job->hwndOwner))
					::SendMessage(job->hwndOwner, HM_EVENTSENT, (WPARAM)MAKELONG(wParam, 0), (LPARAM)&ack);
				else
					sendQueue->ackMessage(0, (WPARAM)MAKELONG(wParam, 0), (LPARAM)&ack);
			}
			return 0;
		}

		case DM_LOGSTATUSCHANGE:
			CGlobals::logStatusChange(wParam, reinterpret_cast<CContactCache *>(lParam));
			return(0);

		case DM_MUCFLASHWORKER: {
			FLASH_PARAMS *p = reinterpret_cast<FLASH_PARAMS*>(lParam);

			if(1 == wParam) {
				CallService(MS_CLIST_CONTACTDOUBLECLICKED, (WPARAM)p->hContact, 1);
				p->bActiveTab = TRUE;
				p->bInactive = FALSE;
				p->bMustAutoswitch = p->bMustFlash = FALSE;
			}

			if(2 == wParam) {
				p->bActiveTab = TRUE;
				p->bInactive = FALSE;
				p->bMustAutoswitch = p->bMustFlash = FALSE;
				SendMessage(p->hWnd, DM_ACTIVATEME, 0, 0);
			}
			DoFlashAndSoundWorker(p);
			return(0);
		}

		case WM_POWERBROADCAST:
		case WM_DISPLAYCHANGE: {
			struct TContainerData *pContainer = pFirstContainer;

			while (pContainer) {
				if (CSkin::m_skinEnabled) {             // invalidate cached background DCs for skinned containers
					pContainer->oldDCSize.cx = pContainer->oldDCSize.cy = 0;
					SelectObject(pContainer->cachedDC, pContainer->oldHBM);
					DeleteObject(pContainer->cachedHBM);
					DeleteDC(pContainer->cachedDC);
					pContainer->cachedDC = 0;
					RedrawWindow(pContainer->hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME);
				}
				pContainer = pContainer->pNextContainer;
			}
			break;
		}

		case WM_ACTIVATE:
			if (LOWORD(wParam) != WA_ACTIVE)
				SetWindowPos(hwndDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE);
			return 0;

		case WM_CLOSE:
			return 0;

		case WM_TIMER:
			if(wParam == TIMERID_SENDLATER) {
				/*
				 * send heartbeat to each open container (to manage autoclose
				 * feature)
				 */
				TContainerData *pContainer = pFirstContainer;
				/*
				 * send heartbeat to each container, they use this to update
				 * dynamic content (i.e. local time in the info panel).
				 */
				while(pContainer) {
					SendMessage(pContainer->hwnd, WM_TIMER, TIMERID_HEARTBEAT, 0);
					pContainer = pContainer->pNextContainer;
				}
				/*
				 * process send later contacts and jobs, if enough time has elapsed
				 */
				if(sendLater->isAvail() && !sendLater->isInteractive() && (time(0) - sendLater->lastProcessed()) > CSendLater::SENDLATER_PROCESS_INTERVAL) {
					sendLater->setLastProcessed(time(0));

					/*
					 * check the list of contacts that may have new send later jobs
					 * (added on user's request)
					 */
					sendLater->processContacts();

					/*
					 * start processing the job list
					 */
					if(!sendLater->isJobListEmpty()) {
						KillTimer(hwndDlg, wParam);
						sendLater->startJobListProcess();
						SetTimer(hwndDlg, TIMERID_SENDLATER_TICK, TIMEOUT_SENDLATER_TICK, 0);
					}
				}
			}
			/*
			 * process one entry per tick (default: 200ms)
			 * TODO better timings, possibly slow down when many jobs are in the
			 * queue.
			 */
			else if(wParam == TIMERID_SENDLATER_TICK) {
				if(!sendLater->haveJobs()) {
					KillTimer(hwndDlg, wParam);
					SetTimer(hwndDlg, TIMERID_SENDLATER, TIMEOUT_SENDLATER, 0);
					sendLater->qMgrUpdate(true);
				}
				else
					sendLater->processCurrentJob();
			}
			break;

		case WM_DESTROY: {
			KillTimer(hwndDlg, TIMERID_SENDLATER_TICK);
			KillTimer(hwndDlg, TIMERID_SENDLATER);
			DestroyServiceFunction(hSvcHotkeyProcessor);
			break;
		}
	}
	return(DefWindowProc(hwndDlg, msg, wParam, lParam));
}