BOOL CALLBACK TabCtrlProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	struct TabCtrlData *dat;
	dat = (struct TabCtrlData *) GetWindowLong(hwnd, GWL_USERDATA);
    switch(msg) {
        case WM_MBUTTONDOWN:
		{
			TCITEM tci;
			int tabId;
			struct MessageWindowData *mwd;
			TCHITTESTINFO thinfo;
			thinfo.pt.x = (lParam<<16)>>16;
			thinfo.pt.y = lParam>>16;
			tabId = TabCtrl_HitTest(hwnd, &thinfo);
			if (tabId >= 0) {
				tci.mask = TCIF_PARAM;
				TabCtrl_GetItem(hwnd, tabId, &tci);
				mwd = (struct MessageWindowData *) tci.lParam;
				if (mwd != NULL) {
					SendMessage(mwd->hwnd, WM_CLOSE, 0, 0);
    			}
			}
	        return TRUE;
        }
		case WM_LBUTTONDBLCLK:
		{
			TCHITTESTINFO thinfo;
			int tabId;
			thinfo.pt.x = (lParam<<16)>>16;
			thinfo.pt.y = lParam>>16;
			tabId = TabCtrl_HitTest(hwnd, &thinfo);
			if (tabId >=0 ) {
				void * clickChild = GetChildFromTab(hwnd, tabId)->hwnd;
				if (clickChild == dat->lastClickChild) {
					SendMessage(clickChild, WM_CLOSE, 0, 0);
				}
			}
			dat->lastClickChild = NULL;
		}
		break;
		case WM_LBUTTONDOWN:
		{
			if (!dat->bDragging) {
				FILETIME ft;
				TCHITTESTINFO thinfo;
				GetSystemTimeAsFileTime(&ft);
				thinfo.pt.x = (lParam<<16)>>16;
				thinfo.pt.y = lParam>>16;
				dat->srcTab = dat->destTab = TabCtrl_HitTest(hwnd, &thinfo);
				if (dat->srcTab >=0 ) {
					dat->lastClickChild = GetChildFromTab(hwnd, dat->srcTab)->hwnd;
				} else {
					dat->lastClickChild = NULL;
				}
				dat->bDragging = TRUE;
				dat->bDragged = FALSE;
				dat->clickLParam = lParam;
				dat->clickWParam = wParam;
				dat->lastClickTime = ft.dwLowDateTime;
				dat->mouseLBDownPos.x = thinfo.pt.x;
				dat->mouseLBDownPos.y = thinfo.pt.y;
				SetCapture(hwnd);
				return 0;
			}
		}
		break;
		case WM_CAPTURECHANGED:
		case WM_LBUTTONUP:
			if (dat->bDragging) {
				TCHITTESTINFO thinfo;
				thinfo.pt.x = (lParam<<16)>>16;
				thinfo.pt.y = lParam>>16;
				if (dat->bDragged) {
					ImageList_DragLeave(GetDesktopWindow());
					ImageList_EndDrag();
					ImageList_Destroy(dat->hDragImageList);
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					dat->destTab = TabCtrl_HitTest(hwnd, &thinfo);
					if (thinfo.flags != TCHT_NOWHERE && dat->destTab != dat->srcTab)  {
						NMHDR nmh;
						TCHAR  sBuffer[501];
						TCITEM item;
						int curSel;
						curSel = TabCtrl_GetCurSel(hwnd);
						item.mask = TCIF_IMAGE | TCIF_PARAM | TCIF_TEXT;
						item.pszText = sBuffer;
						item.cchTextMax = sizeof(sBuffer)/sizeof(TCHAR);
						TabCtrl_GetItem(hwnd, dat->srcTab, &item);
						sBuffer[sizeof(sBuffer)/sizeof(TCHAR)-1] = '\0';
						if (curSel == dat->srcTab) {
							curSel = dat->destTab;
						} else {
							if (curSel > dat->srcTab && curSel <= dat->destTab) {
								curSel--;
							} else if (curSel < dat->srcTab && curSel >= dat->destTab) {
								curSel++;
							}
						}
						TabCtrl_DeleteItem(hwnd, dat->srcTab);
						TabCtrl_InsertItem(hwnd, dat->destTab, &item );
						TabCtrl_SetCurSel(hwnd, curSel);
						nmh.hwndFrom = hwnd;
						nmh.idFrom = GetDlgCtrlID(hwnd);
						nmh.code = TCN_SELCHANGE;
						SendMessage(GetParent(hwnd), WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh);
						UpdateWindow(hwnd);
					}
				} else {
					SendMessage(hwnd, WM_LBUTTONDOWN, dat->clickWParam, dat->clickLParam);
				}
				dat->bDragged = FALSE;
				dat->bDragging = FALSE;
				ReleaseCapture();
			}