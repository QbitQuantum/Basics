ATOM WINAPI HookRegisterClassA(
    WNDCLASSA *lpWndClass 	// address of structure with class data
   )
{
	OldWndProc = lpWndClass->lpfnWndProc;
	lpWndClass->lpfnWndProc = HookWndProc;
	return RegisterClassA(lpWndClass);
}