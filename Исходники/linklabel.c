static void LLabel_OnDestroy(HWND hwnd)
{
	if(IsWindowUnicode(hwnd)){
		free((void *)GetWindowLongPtrW(hwnd, 0));
		free((void *)GetWindowLongPtrW(hwnd, 4));
		EnumPropsW(hwnd, PropEnumProcW);
	}
	else{
		free((void *)GetWindowLongPtr(hwnd, 0));
		free((void *)GetWindowLongPtr(hwnd, 4));
		EnumProps(hwnd, PropEnumProc);
	}
}