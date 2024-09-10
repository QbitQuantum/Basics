LRESULT CALLBACK AlphaTrackBarWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (!IsWindowEnabled(hwnd))
		return mir_callNextSubclass(hwnd, AlphaTrackBarWndProc, msg, wParam, lParam);

	static int oldVal = -1;
	switch (msg) {
	case WM_MOUSEWHEEL:
	case WM_KEYDOWN:
	case WM_KEYUP:
		if (!IsWindowVisible(hwndBox))
			break;

	case WM_MOUSEMOVE:
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = HOVER_DEFAULT;
			tme.hwndTrack = hwnd;
			_TrackMouseEvent(&tme);

			int newVal = (BYTE)SendMessage(hwnd, TBM_GETPOS, 0, 0);
			if (oldVal != newVal)
			{

				if (oldVal < 0)
				{
					SetWindowLongPtr(hwndBox, GWLP_USERDATA, 1);
					RECT rc; GetWindowRect(hwnd, &rc);
					SetWindowPos(hwndBox, NULL,
						(rc.left+rc.right-170)/2, rc.bottom+2, 170, 50,
						SWP_NOACTIVATE|SWP_DEFERERASE|SWP_NOSENDCHANGING|SWP_SHOWWINDOW);
					SetWindowRgn(hwndBox, NULL, TRUE);
				}
				SetWindowLongPtr(hwndBox, GWL_EXSTYLE, GetWindowLongPtr(hwndBox, GWL_EXSTYLE) | WS_EX_LAYERED);
				SetLayeredWindowAttributes(hwndBox, NULL, newVal, LWA_ALPHA);

				oldVal = newVal;
			}
		}
		break;

	case WM_MOUSELEAVE:
		SetWindowLongPtr(hwndBox, GWL_EXSTYLE, GetWindowLongPtr(hwndBox, GWL_EXSTYLE) & ~WS_EX_LAYERED);
		SetLayeredWindowAttributes(hwndBox, NULL, 255, LWA_ALPHA);

		ShowWindow(hwndBox, SW_HIDE);
		oldVal = -1;
		break;
	}
	return mir_callNextSubclass(hwnd, AlphaTrackBarWndProc, msg, wParam, lParam);
}