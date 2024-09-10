static void get_window_size(HDC hdc, uint32_t *cx, uint32_t *cy)
{
	HWND hwnd = WindowFromDC(hdc);
        RECT rc = {0};

        GetClientRect(hwnd, &rc);
	*cx = rc.right;
	*cy = rc.bottom;
}