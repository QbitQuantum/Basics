/* フックプロシージャ */
static LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
#ifndef WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif
	if (nCode == HC_ACTION
			&& (wParam == WM_MOUSEWHEEL || wParam == WM_MOUSEHWHEEL)) {
		MSLLHOOKSTRUCT *pmhs = (MSLLHOOKSTRUCT*)lParam;
		POINT ptCursor = pmhs->pt;
		HWND hwnd = WindowFromPoint(ptCursor);

		if (hwnd != NULL) {
			HWND hwndTarget;
			TCHAR szClass[64];
			POINT ptClient;

			if (GetClassName(hwnd, szClass, sizeof(szClass) / sizeof(TCHAR)) > 0
					&& lstrcmpi(szClass, TEXT("tooltips_class32")) == 0) {
				/* Tooltipに重なる場合、下のウィンドウを探す */
				FindWindowInfo Info;

				Info.ptPos = ptCursor;
				Info.hwnd = hwnd;
				EnumWindows(FindWindowProc, (LPARAM)&Info);
				if (Info.hwnd == hwnd)
					goto Skip;
				hwndTarget = Info.hwnd;
				hwnd = Info.hwnd;
				for (;;) {
					ptClient = ptCursor;
					ScreenToClient(hwnd, &ptClient);
					hwnd = RealChildWindowFromPoint(hwnd, ptClient);
					if (hwnd == NULL || hwnd == hwndTarget)
						break;
					hwndTarget = hwnd;
				}
			} else {
				hwndTarget = hwnd;
				if ((GetWindowLong(hwnd, GWL_STYLE) & WS_CHILD) != 0) {
					HWND hwndParent = GetParent(hwnd);

					if (hwndParent != NULL) {
						ptClient = ptCursor;
						ScreenToClient(hwndParent, &ptClient);
						hwndTarget = RealChildWindowFromPoint(hwndParent, ptClient);
						if (hwndTarget == NULL)
							hwndTarget = hwnd;
					}
				}
			}
			{
				WORD KeyState = 0;
				if (GetAsyncKeyState(VK_LBUTTON) < 0)
					KeyState |= MK_LBUTTON;
				if (GetAsyncKeyState(VK_RBUTTON) < 0)
					KeyState |= MK_RBUTTON;
				if (GetAsyncKeyState(VK_MBUTTON) < 0)
					KeyState |= MK_MBUTTON;
				if (GetAsyncKeyState(VK_XBUTTON1) < 0)
					KeyState |= MK_XBUTTON1;
				if (GetAsyncKeyState(VK_XBUTTON2) < 0)
					KeyState |= MK_XBUTTON2;
				if (GetAsyncKeyState(VK_SHIFT) < 0)
					KeyState |= MK_SHIFT;
				if (GetAsyncKeyState(VK_CONTROL) < 0)
					KeyState |= MK_CONTROL;
#ifdef _DEBUG
				{
					TCHAR szLog[256];
					GetClassName(hwndTarget, szClass, sizeof(szClass) / sizeof(TCHAR));
					wsprintf(szLog, TEXT("%ld, %ld : %p \"%s\" %u\n"),
						ptCursor.x, ptCursor.y, hwndTarget, szClass, (UINT)wParam);
					OutputDebugString(szLog);
				}
#endif
				PostMessage(hwndTarget, (UINT)wParam,
							MAKEWPARAM(KeyState, HIWORD(pmhs->mouseData)),
							MAKELPARAM((SHORT)ptCursor.x, (SHORT)ptCursor.y));
				return 1;
			}
		}
	}

Skip:
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}