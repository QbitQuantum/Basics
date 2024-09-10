/**
 * 
 *  rct2: 0x00407E6E
 */
int osinterface_progressbar_create(char* title, int a2)
{
	DWORD style = WS_VISIBLE | WS_BORDER | WS_DLGFRAME;
	if (a2) {
		style = WS_VISIBLE | WS_BORDER | WS_DLGFRAME | PBS_SMOOTH;
	}
	int width = 340;
	int height = GetSystemMetrics(SM_CYCAPTION) + 24;
	HWND hwnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_DLGMODALFRAME, "msctls_progress32", title, style, (RCT2_GLOBAL(0x01423C08, sint32) - width) / 2, (RCT2_GLOBAL(0x01423C0C, sint32) - height) / 2, width, height, 0, 0, RCT2_GLOBAL(RCT2_ADDRESS_HINSTANCE, HINSTANCE), 0);
	RCT2_GLOBAL(RCT2_ADDRESS_PROGRESSBAR_HWND, HWND) = hwnd;
	if (hwnd) {
		RCT2_GLOBAL(0x009E2DFC, uint32) = 1;
		if (RCT2_GLOBAL(RCT2_ADDRESS_HFONT, HFONT)) {
			SendMessageA(hwnd, WM_SETFONT, (WPARAM)RCT2_GLOBAL(RCT2_ADDRESS_HFONT, HFONT), 1);
		}
		SetWindowTextA(hwnd, title);
		osinterface_progressbar_setmax(0xFF);
		osinterface_progressbar_setpos(0);
		return 1;
	} else {
		return 0;
	}
}