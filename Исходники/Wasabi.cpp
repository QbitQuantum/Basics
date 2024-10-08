Wasabi::Wasabi() {
	engineParams = {
		{ "appName", (void*)"Wasabi" }, // LPCSTR
		{ "classStyle", (void*)(CS_HREDRAW | CS_VREDRAW) }, // DWORD
		{ "classIcon", (void*)(NULL) }, // HICON
		{ "classCursor", (void*)(LoadCursorA(NULL, MAKEINTRESOURCEA(32512))) }, // HCURSOR
		{ "menuName", (void*)(NULL) }, // LPCSTR
		{ "menuProc", (void*)(NULL) }, // void (*) (HMENU, UINT)
		{ "classIcon_sm", (void*)(NULL) }, // HICON
		{ "windowMenu", (void*)(NULL) }, // HMENU
		{ "windowParent", (void*)(NULL) }, // HWND
		{ "windowStyle", (void*)(WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_VISIBLE) }, // DWORD
		{ "windowStyleEx", (void*)(WS_EX_OVERLAPPEDWINDOW) }, // DWORD
		{ "defAdapter", (void*)(0) }, // int
		{ "defWndX", (void*)(-1) }, // int
		{ "defWndY", (void*)(-1) }, //int
	};
}