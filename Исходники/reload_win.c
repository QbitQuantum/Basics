int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int showCmd) {

	EnumWindows(callback, 0);

	SetForegroundWindow(hTarget);
	if (!IeFlg) {
		keybd_event(VK_BROWSER_REFRESH, 0, 0, 0);
	} else {
		keybd_event(VK_F5, 0, 0, 0);
	}

	SetForegroundWindow(hMe[0]);
	SetWindowPos(hMe[0], HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

	return 0;
}