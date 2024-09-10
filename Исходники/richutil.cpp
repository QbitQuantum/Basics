static LRESULT CALLBACK RichUtil_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TRichUtil *ru = NULL, tru;
	int idx;
	LRESULT ret;

	tru.hwnd = hwnd;
	{
		mir_cslock lck(csRich);
		if (List_GetIndex(&sListInt, &tru, &idx))
			ru = (TRichUtil *)sListInt.items[idx];
	}

	switch (msg) {
	case WM_THEMECHANGED:
	case WM_STYLECHANGED:
		RichUtil_ClearUglyBorder(ru);
		break;

	case WM_NCPAINT:
		ret = mir_callNextSubclass(hwnd, RichUtil_Proc, msg, wParam, lParam);
		if (ru->hasUglyBorder && IsThemeActive())
		{
			HANDLE hTheme = OpenThemeData(ru->hwnd, L"EDIT");

			if (hTheme) {
				RECT rcBorder;
				RECT rcClient;
				int nState;
				HDC hdc = GetWindowDC(ru->hwnd);

				GetWindowRect(hwnd, &rcBorder);
				rcBorder.right -= rcBorder.left; rcBorder.bottom -= rcBorder.top;
				rcBorder.left = rcBorder.top = 0;
				CopyRect(&rcClient, &rcBorder);
				rcClient.left += ru->rect.left;
				rcClient.top += ru->rect.top;
				rcClient.right -= ru->rect.right;
				rcClient.bottom -= ru->rect.bottom;
				ExcludeClipRect(hdc, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);

				if (IsThemeBackgroundPartiallyTransparent(hTheme, EP_EDITTEXT, ETS_NORMAL))
					DrawThemeParentBackground(hwnd, hdc, &rcBorder);

				if (!IsWindowEnabled(hwnd))
					nState = ETS_DISABLED;
				else if (SendMessage(hwnd, EM_GETOPTIONS, 0, 0) & ECO_READONLY)
					nState = ETS_READONLY;
				else nState = ETS_NORMAL;

				DrawThemeBackground(hTheme, hdc, EP_EDITTEXT, nState, &rcBorder, NULL);
				CloseThemeData(hTheme);
				ReleaseDC(hwnd, hdc);
				return 0;
			}
		}
		return ret;

	case WM_NCCALCSIZE:
		{
			ret = mir_callNextSubclass(hwnd, RichUtil_Proc, msg, wParam, lParam);
			NCCALCSIZE_PARAMS *ncsParam = (NCCALCSIZE_PARAMS *)lParam;

			if (ru->hasUglyBorder && IsThemeActive()) {
				HANDLE hTheme = OpenThemeData(hwnd, L"EDIT");
				if (hTheme) {
					RECT rcClient = {0};
					HDC hdc = GetDC(GetParent(hwnd));

					if (GetThemeBackgroundContentRect(hTheme, hdc, EP_EDITTEXT, ETS_NORMAL, &ncsParam->rgrc[0], &rcClient) == S_OK) {
						ru->rect.left = rcClient.left - ncsParam->rgrc[0].left;
						ru->rect.top = rcClient.top - ncsParam->rgrc[0].top;
						ru->rect.right = ncsParam->rgrc[0].right - rcClient.right;
						ru->rect.bottom = ncsParam->rgrc[0].bottom - rcClient.bottom;
						ncsParam->rgrc[0] = rcClient;

						CloseThemeData(hTheme);
						ReleaseDC(GetParent(hwnd), hdc);
						return WVR_REDRAW;
					}
					ReleaseDC(GetParent(hwnd), hdc);
					CloseThemeData(hTheme);
				}
			}
		}
		return ret;

	case WM_ENABLE:
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_NOCHILDREN | RDW_UPDATENOW | RDW_FRAME);
		break;

	case WM_GETDLGCODE:
		return mir_callNextSubclass(hwnd, RichUtil_Proc, msg, wParam, lParam) & ~DLGC_HASSETSEL;

	case WM_NCDESTROY:
		ret = mir_callNextSubclass(hwnd, RichUtil_Proc, msg, wParam, lParam);
		{
			mir_cslock lck(csRich);
			List_Remove(&sListInt, idx);
		}
		mir_free(ru);
		return ret;
	}
	return mir_callNextSubclass(hwnd, RichUtil_Proc, msg, wParam, lParam);
}