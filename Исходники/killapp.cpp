LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		case WM_COMMAND:
			switch (wParam) {
				case IDC_KILL:
					if (MessageBox(hWnd, "Are you sure you want to terminate the application?", "Confirm", MB_YESNO | MB_ICONQUESTION) == IDYES) {
						terminateProcess();
					}
					break;
				case IDC_EXIT:
					if (MessageBox(hWnd, "Are you sure you want to remove this icon?  You will no longer be able to use it to terminate the application.", "Confirm", MB_YESNO | MB_ICONQUESTION) == IDYES) {
						DestroyWindow(hWnd);
						//PostQuitMessage(0); // Doesn't work under Windows Server 2008, does work under Win7
					}
					break;
			}
			break;
		case TRAY_MSG:
			switch (lParam) {
				case WM_RBUTTONDOWN: {
					HMENU popupMenu = CreatePopupMenu();
					AppendMenu(popupMenu, MF_ENABLED, IDC_KILL, "Terminate application");
					AppendMenu(popupMenu, MF_ENABLED, IDC_EXIT, "Remove this icon");
					POINT mp;
					GetCursorPos(&mp);
					SetForegroundWindow(hWnd);
					TrackPopupMenuEx(popupMenu, 0, mp.x, mp.y, hWnd, NULL);
					PostMessage(hWnd, WM_NULL, 0, 0);
					DestroyMenu(popupMenu);
					break;
				}
			}
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}