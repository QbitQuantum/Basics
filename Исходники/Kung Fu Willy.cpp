			//////////////////////////////////////
			// Handle WM_CREATE
			//////////////////////////////////////
BOOL Main_Create(HWND hwnd, CREATESTRUCT FAR* lpCreateStruct)
{
	fight = TRUE;
	joySetCapture(hwnd, JOYSTICKID1, TimeRate, FALSE);
	Reset((HWNDdll)hwnd);
	ButtonUpdate((HWNDdll)hwnd, (HINST)hInst);
	return TRUE;
}