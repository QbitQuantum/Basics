BOOL UnSetShellHook(HWND hwndHook)
{
    if (DeregisterShellHookWindow(hwndHook)) {
	return TRUE;
    } else {
	return FALSE;
    }
}