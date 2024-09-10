static LRESULT CALLBACK RichUtil_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	TRichUtil *ru;
	
	EnterCriticalSection(&csRich);
	ru = rlist_find(slist, hwnd);
	LeaveCriticalSection(&csRich);
	switch(msg) {
		case WM_THEMECHANGED:
		case WM_STYLECHANGED:
		{
			RichUtil_ClearUglyBorder(ru);
			break;
		}
		case WM_NCPAINT:
		{
			LRESULT ret = CallWindowProc(ru->origProc, hwnd, msg, wParam, lParam);
			if (ru->hasUglyBorder&&MyIsThemeActive()) {
				HANDLE hTheme = MyOpenThemeData(ru->hwnd, L"EDIT");

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
					if(MyIsThemeBackgroundPartiallyTransparent(hTheme, EP_EDITTEXT, ETS_NORMAL))
						MyDrawThemeParentBackground(hwnd, hdc, &rcBorder);
					if(!IsWindowEnabled(hwnd))
						nState = ETS_DISABLED;
					else if(SendMessage(hwnd, EM_GETOPTIONS, 0, 0) & ECO_READONLY)
						nState = ETS_READONLY;
					else nState = ETS_NORMAL;
					MyDrawThemeBackground(hTheme, hdc, EP_EDITTEXT, nState, &rcBorder, NULL);
					MyCloseThemeData(hTheme);
					ReleaseDC(hwnd, hdc);
					return 0;
				}
			}
			return ret;
		}
		case WM_NCCALCSIZE:
		{
			LRESULT ret = CallWindowProc(ru->origProc, hwnd, msg, wParam, lParam);
			NCCALCSIZE_PARAMS *ncsParam = (NCCALCSIZE_PARAMS*)lParam;
			
			if (ru->hasUglyBorder&&MyIsThemeActive()) {
				HANDLE hTheme = MyOpenThemeData(hwnd, L"EDIT");

				if (hTheme) {
					RECT rcClient; 
					HDC hdc = GetDC(GetParent(hwnd));

					ZeroMemory(&rcClient, sizeof(RECT));
					if(MyGetThemeBackgroundContentRect(hTheme, hdc, EP_EDITTEXT, ETS_NORMAL, &ncsParam->rgrc[0], &rcClient) == S_OK) {
						ru->rect.left = rcClient.left-ncsParam->rgrc[0].left;
						ru->rect.top = rcClient.top-ncsParam->rgrc[0].top;
						ru->rect.right = ncsParam->rgrc[0].right-rcClient.right;
						ru->rect.bottom = ncsParam->rgrc[0].bottom-rcClient.bottom;
						CopyRect(&ncsParam->rgrc[0], &rcClient);
						MyCloseThemeData(hTheme);
						ReleaseDC(GetParent(hwnd), hdc);
						return WVR_REDRAW;
					}
					ReleaseDC(GetParent(hwnd), hdc);
					MyCloseThemeData(hTheme);
				}
			}
			return ret;
		}
		case WM_ENABLE:
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE|RDW_NOCHILDREN|RDW_UPDATENOW|RDW_FRAME);
			break;
		case WM_DESTROY:
		{
			LRESULT ret = CallWindowProc(ru->origProc, hwnd, msg, wParam, lParam);

			if(IsWindow(hwnd)) {
				if((WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC) == &RichUtil_Proc)
					SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)ru->origProc);
			}
			EnterCriticalSection(&csRich);
			slist = rlist_remove(slist, ru);
			LeaveCriticalSection(&csRich);
			if (ru) free(ru);
			return ret;
		}
	}
	return CallWindowProc(ru->origProc, hwnd, msg, wParam, lParam);
}