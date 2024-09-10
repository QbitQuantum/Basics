void CloseRawInputProxyWnd( HANDLE hHandle )
{
	if ( hHandle != NULL )
	{
		RAWINPUTDEVICE rid[3]={0};
		UINT num=3;

		rid[0].usUsagePage = 0xFFBC;      // adds HID remote control
		rid[0].usUsage = 0x88;
		rid[0].dwFlags = RIDEV_REMOVE;
		rid[0].hwndTarget = 0;

		rid[1].usUsagePage = 0x0C;      // adds HID remote control
		rid[1].usUsage = 0x01;
		rid[1].dwFlags = RIDEV_REMOVE;
		rid[1].hwndTarget = 0;

		rid[2].usUsagePage = 0x0C;      // adds HID remote control
		rid[2].usUsage = 0x80;
		rid[2].dwFlags = RIDEV_REMOVE;
		rid[2].hwndTarget = 0;
		RegisterRawInputDevices(rid, 3, sizeof(RAWINPUTDEVICE) ); 
		SendMessage((HWND)hHandle, WM_DESTROY, NULL, NULL );
#ifdef FUJITSU_BUILD
		if (hEvtKiller)
			CloseHandle(hEvtKiller);
#endif
	}
}