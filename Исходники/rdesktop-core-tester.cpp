static
DWORD
WINAPI
mstsc_ProtocolIOThread
(
	LPVOID lpArgument
)
{
	RDPCLIENT * This = static_cast<RDPCLIENT *>(lpArgument);

	WCHAR hostname[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD dw = ARRAYSIZE(hostname);
	GetComputerNameW(hostname, &dw);

	uint32 flags = RDP_LOGON_NORMAL | RDP_LOGON_COMPRESSION | RDP_LOGON_COMPRESSION2;

	rdp_connect(This, "10.0.0.3", flags, L"Administrator", L"", L"", L"", L"", hostname, "");
	//rdp_connect(This, "192.168.7.232", flags, "", "", "", "");

	hdcBuffer = CreateCompatibleDC(NULL);

	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = This->width;
	bmi.bmiHeader.biHeight = This->height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = This->server_depth;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed = 0; // TODO! palette displays
	bmi.bmiHeader.biClrImportant = 0; // TODO! palette displays

	hbmBuffer = CreateDIBSection(hdcBuffer, &bmi, DIB_RGB_COLORS, &pBuffer, NULL, 0);

	SelectObject(hdcBuffer, hbmBuffer);

#if 0
	rcClip.left = 0;
	rcClip.top = 0;
	rcClip.right = This->width + 1;
	rcClip.bottom = This->height + 1;
#endif

	BOOL deactivated;
	uint32 ext_disc_reason;

	rdp_main_loop(This, &deactivated, &ext_disc_reason);
	// TODO: handle redirection
	// EVENT: OnDisconnect

	SendMessage(hwnd, WM_CLOSE, 0, 0);

	return 0;
}