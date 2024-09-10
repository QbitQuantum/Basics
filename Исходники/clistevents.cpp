LRESULT CALLBACK EventAreaWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE:
		hwndEventFrame = hwnd;
		return FALSE;

	case WM_MEASUREITEM:
		{
			MEASUREITEMSTRUCT *lpi = (LPMEASUREITEMSTRUCT)lParam;
			MENUITEMINFOA mii = { 0 };

			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_DATA | MIIM_ID;
			if (GetMenuItemInfoA(cfg::dat.hMenuNotify, lpi->itemID, FALSE, &mii) != 0) {
				if (mii.dwItemData == lpi->itemData) {
					lpi->itemWidth = 8 + 16;
					lpi->itemHeight = 0;
					return TRUE;
				}
			}
			break;
		}
	case WM_NCCALCSIZE:
		return FrameNCCalcSize(hwnd, DefWindowProc, wParam, lParam,
			wndFrameEventArea ? wndFrameEventArea->TitleBar.ShowTitleBar : 0);
	case WM_NCPAINT:
		return FrameNCPaint(hwnd, DefWindowProc, wParam, lParam,
			wndFrameEventArea ? wndFrameEventArea->TitleBar.ShowTitleBar : 0);
	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lParam;

			if (dis->hwndItem == (HWND)cfg::dat.hMenuNotify) {
				MENUITEMINFOA mii = { 0 };

				struct NotifyMenuItemExData *nmi = 0;
				int iIcon;
				HICON hIcon;

				mii.cbSize = sizeof(mii);
				mii.fMask = MIIM_DATA;
				if (GetMenuItemInfoA(cfg::dat.hMenuNotify, (UINT)dis->itemID, FALSE, &mii) != 0) {
					nmi = (struct NotifyMenuItemExData *) mii.dwItemData;
					if (nmi) {
						iIcon = pcli->pfnGetContactIcon(nmi->hContact);
						hIcon = ImageList_GetIcon(hCListImages, iIcon, ILD_NORMAL);
						pcli->pfnDrawMenuItem(dis, hIcon, nmi->hIcon);
						return TRUE;
					}
				}
			}
			break;
		}
	case WM_LBUTTONUP:
		if (cfg::dat.bEventAreaEnabled)
			SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_NOTIFYBUTTON, 0), 0);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_NOTIFYBUTTON) {
			int iSelection;
			struct NotifyMenuItemExData *nmi = 0;
			int iCount = GetMenuItemCount(cfg::dat.hMenuNotify);

			POINT pt;
			GetCursorPos(&pt);

			MENUITEMINFO mii = { 0 };
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_DATA;
			if (iCount > 1)
				iSelection = TrackPopupMenu(cfg::dat.hMenuNotify, TPM_RETURNCMD, pt.x, pt.y, 0, hwnd, NULL);
			else
				iSelection = GetMenuItemID(cfg::dat.hMenuNotify, 0);
			
			BOOL result = GetMenuItemInfo(cfg::dat.hMenuNotify, (UINT)iSelection, FALSE, &mii);
			if (result != 0) {
				nmi = (struct NotifyMenuItemExData *) mii.dwItemData;
				if (nmi) {
					CLISTEVENT *cle = MyGetEvent(iSelection);
					if (cle) {
						CLISTEVENT *cle1 = NULL;
						CallService(cle->pszService, (WPARAM)NULL, (LPARAM)cle);
						// re-obtain the pointer, it may already be invalid/point to another event if the
						// event we're interested in was removed by the service (nasty one...)
						cle1 = MyGetEvent(iSelection);
						if (cle1 != NULL)
							CallService(MS_CLIST_REMOVEEVENT, (WPARAM)cle->hContact, (LPARAM)cle->hDbEvent);
					}
				}
			}
		}
		break;

	case WM_ERASEBKGND:
		return TRUE;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			RECT rc, rcClient;
			GetClientRect(hwnd, &rc);
			rcClient = rc;

			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbm = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
			HBITMAP hbmold = reinterpret_cast<HBITMAP>(SelectObject(hdcMem, hbm));
			SetBkMode(hdcMem, TRANSPARENT);

			HFONT hFontOld = 0;
			if (cfg::clcdat) {
				int height;
				hFontOld = ChangeToFont(hdcMem, cfg::clcdat, FONTID_EVENTAREA, &height);
			}

			if (cfg::dat.bWallpaperMode)
				SkinDrawBg(hwnd, hdcMem);

			StatusItems_t *item = arStatusItems[ID_EXTBKEVTAREA - ID_STATUS_OFFLINE];
			if (item->IGNORED)
				FillRect(hdcMem, &rc, GetSysColorBrush(COLOR_3DFACE));
			else {
				rc.top += item->MARGIN_TOP; rc.bottom -= item->MARGIN_BOTTOM;
				rc.left += item->MARGIN_LEFT; rc.right -= item->MARGIN_RIGHT;

				DrawAlpha(hdcMem, &rc, item->COLOR, item->ALPHA, item->COLOR2, item->COLOR2_TRANSPARENT,
					item->GRADIENT, item->CORNER, item->BORDERSTYLE, item->imageItem);
				SetTextColor(hdcMem, item->TEXTCOLOR);
			}

			LONG dwLeft = rc.left;

			PaintNotifyArea(hdcMem, &rc);
			if (cfg::dat.dwFlags & CLUI_FRAME_EVENTAREASUNKEN) {
				rc.left = dwLeft;
				InflateRect(&rc, -2, -2);
				DrawEdge(hdcMem, &rc, BDR_SUNKENOUTER, BF_RECT);
			}
			BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hbmold);
			if (hFontOld)
				SelectObject(hdcMem, hFontOld);
			DeleteObject(hbm);
			DeleteDC(hdcMem);
			ps.fErase = FALSE;
			EndPaint(hwnd, &ps);
		}
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return TRUE;
}