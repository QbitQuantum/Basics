LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent;
	LPMINMAXINFO minInfo;
	static SOCKET serverSocket;
	static SOCKET clientSocket;

	switch (message) {
	case WM_CREATE:
		serverSocket = CreateSocket(hWnd);
		connectionStatus = statusNotConnected;
		EnableMenuItem(GetMenu(hWnd), IDM_DISCONNECT, MF_BYCOMMAND | MF_GRAYED);
		ListAddresses();
		break;
	case WM_NETWORK:
		switch (WSAGETSELECTEVENT(lParam)) {
		case FD_ACCEPT:
			clientSocket = AcceptSocket(hWnd, serverSocket);
			break;
		case FD_CLOSE:
			if (connectionStatus == statusConnected)
				CloseSocket(hWnd, clientSocket);
			break;
		}
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId) {
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			Shell_NotifyIcon(NIM_DELETE, &trayIcon[trayIconNotConnected]);
			DestroyWindow(hWnd);
			break;
		case IDM_TRAY:
			HideInTray(hWnd, TRUE);
			break;
		case IDM_DISCONNECT:
			if (connectionStatus == statusConnected)
				CloseSocket(hWnd, clientSocket);
			break;
		case IDM_OPEN:
			HideInTray(hWnd, FALSE);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_GETMINMAXINFO:
		minInfo = (LPMINMAXINFO)lParam;
		minInfo->ptMinTrackSize.x = kWidthMin;
		minInfo->ptMinTrackSize.y = kHeightMin;
		break;
	case WM_PAINT:
		DisplayWindow(hWnd);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_MINIMIZE)
			HideInTray(hWnd, TRUE);
		else
			return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	case WM_CLOSE:
		HideInTray(hWnd, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TRAYMENU:
		if (wParam == kTrayId) {
			switch (lParam) {
			case WM_RBUTTONDOWN:
				DisplayTrayMenu(hWnd);
				break;
			case WM_LBUTTONDBLCLK:
				HideInTray(hWnd, !bInTray);
				break;
			default:
				break;
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}