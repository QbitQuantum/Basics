static LRESULT CALLBACK TSButtonWndProc(HWND hwndDlg, UINT msg,  WPARAM wParam, LPARAM lParam)
{
	MButtonCtrl* bct = (MButtonCtrl *)GetWindowLongPtr(hwndDlg, 0);
	switch (msg) {
		case WM_NCCREATE: {
			SetWindowLongPtr(hwndDlg, GWL_STYLE, GetWindowLongPtr(hwndDlg, GWL_STYLE) | BS_OWNERDRAW);
			bct = (MButtonCtrl *)malloc(sizeof(MButtonCtrl));
			if (bct == NULL)
				return FALSE;
			ZeroMemory(bct, sizeof(MButtonCtrl));
			bct->hwnd = hwndDlg;
			bct->stateId = PBS_NORMAL;
			bct->hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			LoadTheme(bct);
			SetWindowLongPtr(hwndDlg, 0, (LONG_PTR)bct);
			if (((CREATESTRUCT *)lParam)->lpszName)
				SetWindowText(hwndDlg, ((CREATESTRUCT *)lParam)->lpszName);
			return TRUE;
		}
		case WM_DESTROY: {
			if (bct) {
				EnterCriticalSection(&csTips);
				if (hwndToolTips) {
					TOOLINFO ti;

					ZeroMemory(&ti, sizeof(ti));
					ti.cbSize = sizeof(ti);
					ti.uFlags = TTF_IDISHWND;
					ti.hwnd = bct->hwnd;
					ti.uId = (UINT_PTR)bct->hwnd;
					if (SendMessage(hwndToolTips, TTM_GETTOOLINFO, 0, (LPARAM)&ti)) {
						SendMessage(hwndToolTips, TTM_DELTOOL, 0, (LPARAM)&ti);
					}
					if (SendMessage(hwndToolTips, TTM_GETTOOLCOUNT, 0, (LPARAM)&ti) == 0) {
						DestroyWindow(hwndToolTips);
						hwndToolTips = NULL;
					}
				}
				if (bct->hIconPrivate)
					DestroyIcon(bct->hIconPrivate);
				LeaveCriticalSection(&csTips);
				DestroyTheme(bct);
			}
			break;	// DONT! fall thru
		}

		case WM_NCDESTROY:
			free(bct);
			SetWindowLongPtr(hwndDlg, 0, (LONG_PTR)NULL);
			break;

		case WM_SETTEXT: {
			bct->cHot = 0;
			if ((TCHAR *)lParam) {
				TCHAR *tmp = (TCHAR *)lParam;
				while (*tmp) {
					if (*tmp == (TCHAR)'&' && *(tmp + 1)) {
						bct->cHot = _totlower(*(tmp + 1));
						break;
					}
					tmp++;
				}
				InvalidateRect(bct->hwnd, NULL, TRUE);
			}
			break;
		}
		case WM_KEYUP:
			if (bct->stateId != PBS_DISABLED && wParam == VK_SPACE && !(GetKeyState(VK_CONTROL) & 0x8000) && !(GetKeyState(VK_SHIFT) & 0x8000)) {
				if (bct->pushBtn) {
					if (bct->pbState) bct->pbState = 0;
					else bct->pbState = 1;
					InvalidateRect(bct->hwnd, NULL, TRUE);
				}
				SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM)hwndDlg);
				return 0;
			}
			break;
		case WM_SYSKEYUP:
			if (bct->stateId != PBS_DISABLED && bct->cHot && bct->cHot == tolower((int)wParam)) {
				if (bct->pushBtn) {
					if (bct->pbState) bct->pbState = 0;
					else bct->pbState = 1;
					InvalidateRect(bct->hwnd, NULL, TRUE);
				}
				SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM)hwndDlg);
				return 0;
			}
			break;
		case WM_THEMECHANGED: {
			// themed changed, reload theme object
			if (bct->bThemed)
				LoadTheme(bct);
			InvalidateRect(bct->hwnd, NULL, TRUE); // repaint it
			break;
		}
		case WM_SETFONT: { // remember the font so we can use it later
			bct->hFont = (HFONT)wParam; // maybe we should redraw?
			break;
		}
		case WM_NCPAINT:
			return(0);

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdcPaint;

			hdcPaint = BeginPaint(hwndDlg, &ps);
			if (hdcPaint) {
				if(bct->sitem)
					bct->sitem->RenderThis(hdcPaint);
				else
					PaintWorker(bct, hdcPaint);
				EndPaint(hwndDlg, &ps);
			}
			return(0);
		}
		case BM_SETIMAGE:
			if (wParam == IMAGE_ICON) {
				ICONINFO ii;
				BITMAP bm;

				if (bct->hIconPrivate)
					DestroyIcon(bct->hIconPrivate);

				GetIconInfo((HICON)lParam, &ii);
				GetObject(ii.hbmColor, sizeof(bm), &bm);
				if (bm.bmWidth != PluginConfig.m_smcxicon || bm.bmHeight != PluginConfig.m_smcyicon) {
					HIMAGELIST hImageList;
					hImageList = ImageList_Create(PluginConfig.m_smcxicon, PluginConfig.m_smcyicon, PluginConfig.m_bIsXP ? ILC_COLOR32 | ILC_MASK : ILC_COLOR16 | ILC_MASK, 1, 0);
					ImageList_AddIcon(hImageList, (HICON)lParam);
					bct->hIconPrivate = ImageList_GetIcon(hImageList, 0, ILD_NORMAL);
					ImageList_RemoveAll(hImageList);
					ImageList_Destroy(hImageList);
					bct->hIcon = 0;
				} else {
					bct->hIcon = (HICON)lParam;
					bct->hIconPrivate = 0;
				}

				DeleteObject(ii.hbmMask);
				DeleteObject(ii.hbmColor);
				bct->hBitmap = NULL;
				InvalidateRect(bct->hwnd, NULL, TRUE);
			} else if (wParam == IMAGE_BITMAP) {
				bct->hBitmap = (HBITMAP)lParam;
				if (bct->hIconPrivate)
					DestroyIcon(bct->hIconPrivate);
				bct->hIcon = bct->hIconPrivate = NULL;
				InvalidateRect(bct->hwnd, NULL, TRUE);
			}
			break;
		case BM_SETCHECK:
			if (!bct->pushBtn) break;
			if (wParam == BST_CHECKED) {
				bct->pbState = 1;
				bct->stateId = PBS_PRESSED;
			} else if (wParam == BST_UNCHECKED) {
				bct->pbState = 0;
				bct->stateId = PBS_NORMAL;
			}
			InvalidateRect(bct->hwnd, NULL, TRUE);
			break;
		case BM_GETCHECK:
			if (bct->pushBtn) {
				return bct->pbState ? BST_CHECKED : BST_UNCHECKED;
			}
			return 0;
		case BUTTONSETARROW: // turn arrow on/off
			bct->arrow = (HICON)wParam;
			InvalidateRect(bct->hwnd, NULL, TRUE);
			break;
		case BUTTONSETDEFAULT:
			bct->defbutton = wParam ? 1 : 0;
			InvalidateRect(bct->hwnd, NULL, TRUE);
			break;
		case BUTTONSETASPUSHBTN:
			bct->pushBtn = 1;
			InvalidateRect(bct->hwnd, NULL, TRUE);
			break;
		case BUTTONSETASFLATBTN:
			bct->flatBtn = lParam == 0 ? 1 : 0;
			InvalidateRect(bct->hwnd, NULL, TRUE);
			break;
		case BUTTONSETASFLATBTN + 10:
			bct->bThemed = lParam ? TRUE : FALSE;
			break;
		case BUTTONSETASFLATBTN + 11:
			bct->dimmed = lParam ? TRUE : FALSE;
			break;
		case BUTTONSETASFLATBTN + 12:
			bct->pContainer = (struct TContainerData *)lParam;
			break;
		case BUTTONSETASFLATBTN + 13:
			bct->bTitleButton = TRUE;
			break;
		case BUTTONSETASFLATBTN + 14:
			bct->stateId = (wParam) ? PBS_NORMAL : PBS_DISABLED;
			InvalidateRect(bct->hwnd, NULL, FALSE);
			break;
		case BUTTONSETASFLATBTN + 15:
			return bct->stateId;
		case BUTTONSETASTOOLBARBUTTON:
			bct->bToolbarButton = lParam;
			break;
		case BUTTONSETASSIDEBARBUTTON:
			bct->sitem = reinterpret_cast<CSideBarButton *>(lParam);
			break;
		case BUTTONSETOVERLAYICON:
			bct->overlay = (HICON)lParam;
			break;
		case BUTTONADDTOOLTIP: {
			TOOLINFO ti;

			if (!(char*)wParam)
				break;
			EnterCriticalSection(&csTips);
			if (!hwndToolTips) {
				hwndToolTips = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, _T(""), WS_POPUP, 0, 0, 0, 0, NULL, NULL, GetModuleHandle(NULL), NULL);
			}
			ZeroMemory(&ti, sizeof(ti));
			ti.cbSize = sizeof(ti);
			ti.uFlags = TTF_IDISHWND;
			ti.hwnd = bct->hwnd;
			ti.uId = (UINT_PTR)bct->hwnd;
			if (SendMessage(hwndToolTips, TTM_GETTOOLINFO, 0, (LPARAM)&ti)) {
				SendMessage(hwndToolTips, TTM_DELTOOL, 0, (LPARAM)&ti);
			}
			ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
			ti.uId = (UINT_PTR)bct->hwnd;
			ti.lpszText = (TCHAR *)wParam;
			SendMessage(hwndToolTips, TTM_ADDTOOL, 0, (LPARAM)&ti);
			SendMessage(hwndToolTips, TTM_SETMAXTIPWIDTH, 0, 300);
			LeaveCriticalSection(&csTips);
			break;
		}
		case WM_SETFOCUS: // set keybord focus and redraw
			bct->focus = 1;
			InvalidateRect(bct->hwnd, NULL, TRUE);
			break;
		case WM_KILLFOCUS: // kill focus and redraw
			bct->focus = 0;
			InvalidateRect(bct->hwnd, NULL, TRUE);
			break;
		case WM_ENABLE: { // windows tells us to enable/disable
			bct->stateId = wParam ? PBS_NORMAL : PBS_DISABLED;
			InvalidateRect(bct->hwnd, NULL, TRUE);
			break;
		}
		case WM_MOUSELEAVE: { // faked by the WM_TIMER
			if (bct->stateId != PBS_DISABLED) { // don't change states if disabled
				bct->stateId = PBS_NORMAL;
				InvalidateRect(bct->hwnd, NULL, TRUE);
			}
			break;
		}

		case WM_CONTEXTMENU:
			if(bct->sitem)
				bct->sitem->invokeContextMenu();
			break;

		case WM_MBUTTONUP:
			if(bct->sitem) {
				if(bct->sitem->getDat())
					SendMessage(bct->sitem->getDat()->hwnd, WM_CLOSE, 1, 0);
			}
			break;

		case WM_LBUTTONDOWN: {
			RECT rc;

			if(bct->sitem) {
				if(bct->sitem->testCloseButton() != -1)
					return(TRUE);
				bct->stateId = PBS_PRESSED;
				InvalidateRect(bct->hwnd, NULL, TRUE);
				bct->sitem->activateSession();
			}

			if (bct->arrow) {
				GetClientRect(bct->hwnd, &rc);
				if (LOWORD(lParam) < rc.right - 12 && bct->stateId != PBS_DISABLED)
					bct->stateId = PBS_PRESSED;
				else if(LOWORD(lParam) > rc.right - 12) {
					if(GetDlgCtrlID(hwndDlg) == IDOK || bct->stateId != PBS_DISABLED) {
						WORD w = (WORD)((int)bct->arrow & 0x0000ffff);
						SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(w, BN_CLICKED), (LPARAM)hwndDlg);
					}
				}
				InvalidateRect(bct->hwnd, NULL, TRUE);
			} else if (bct->stateId != PBS_DISABLED) {
				bct->stateId = PBS_PRESSED;
				InvalidateRect(bct->hwnd, NULL, TRUE);
			}
			break;
		}
		case WM_LBUTTONUP: {
			int  showClick = 0;

			if (bct->sitem) {
				if(bct->sitem->testCloseButton() != -1) {
					SendMessage(bct->sitem->getDat()->hwnd, WM_CLOSE, 1, 0);
					return(TRUE);
				}
			}
			if (bct->pushBtn) {
				if (bct->pbState) bct->pbState = 0;
				else bct->pbState = 1;
			}
			if (bct->stateId != PBS_DISABLED) { // don't change states if disabled
				if(bct->stateId == PBS_PRESSED)
					showClick = 1;
				if (msg == WM_LBUTTONUP)
					bct->stateId = PBS_HOT;
				else
					bct->stateId = PBS_NORMAL;
				InvalidateRect(bct->hwnd, NULL, TRUE);
			}
			if(showClick)
		          SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM)hwndDlg);
			break;
		}
		case WM_MOUSEMOVE:
			if (bct->stateId == PBS_NORMAL) {
				bct->stateId = PBS_HOT;
				InvalidateRect(bct->hwnd, NULL, TRUE);
			} else if (bct->arrow && bct->stateId == PBS_HOT) {
				InvalidateRect(bct->hwnd, NULL, TRUE);
			}
			// Call timer, used to start cheesy TrackMouseEvent faker
			SetTimer(hwndDlg, BUTTON_POLLID, BUTTON_POLLDELAY, NULL);
			if(bct->sitem) {
				if(bct->sitem->testCloseButton() != -1) {
					if(bct->sitem->m_sideBar->getHoveredClose() != bct->sitem) {
						bct->sitem->m_sideBar->setHoveredClose(bct->sitem);
						InvalidateRect(hwndDlg, 0, FALSE);
					}
				}
				else {
					bct->sitem->m_sideBar->setHoveredClose(0);
					InvalidateRect(hwndDlg, 0, FALSE);
				}
			}
			break;
		case WM_TIMER: { // use a timer to check if they have did a mouseout
			if (wParam == BUTTON_POLLID) {
				RECT rc;
				POINT pt;
				GetWindowRect(hwndDlg, &rc);
				GetCursorPos(&pt);
				if (!PtInRect(&rc, pt)) { // mouse must be gone, trigger mouse leave
					PostMessage(hwndDlg, WM_MOUSELEAVE, 0, 0L);
					KillTimer(hwndDlg, BUTTON_POLLID);
					if(bct->sitem) {
						bct->sitem->m_sideBar->setHoveredClose(0);
						InvalidateRect(hwndDlg, 0, FALSE);
					}
				}
			}
			break;
		}
		case WM_ERASEBKGND:
			return(1);
	}
	return DefWindowProc(hwndDlg, msg, wParam, lParam);
}