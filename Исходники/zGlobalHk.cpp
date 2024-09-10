bool zGlobalHk::PlaceWndHook(HWND hwnd)
{
	GET_HOOK(zGlobalHk).m_AppWndProc = GetWindowLongPtrA(hwnd, GWL_WNDPROC);
	SetWindowLongPtrA(hwnd, GWL_WNDPROC, (LONG)AppWndProc);

	return true;
}