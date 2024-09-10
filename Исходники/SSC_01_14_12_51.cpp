void SendKey(HWND hWndTargetWindow, BYTE virtualKey)
{
	Sleep(100);
	keybd_event(virtualKey, 0, 0, 0);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
}