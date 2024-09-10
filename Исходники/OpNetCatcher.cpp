LRESULT WINAPI WndProc (HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	
	switch (uMsg)
	{
		case WM_PAINT:
			PAINTSTRUCT ps;
			HDC dc = BeginPaint (hWnd, &ps);
			
			SelectObject (dc, GetStockObject (WHITE_BRUSH));
			SelectObject (dc, GetStockObject (WHITE_PEN));
			RECT rc;
			GetClientRect (hWnd, &rc);
			Rectangle (dc, rc.left, rc.top, rc.right, rc.bottom);
			DrawIcon (dc, 5, 5, _Icon);
			LPCSTR pszMsg = "Download was transferred to Free Download Manager...\nPlease use \"Back\" button to go back";
			RECT rcT = rc;
			rcT.left = 40; rcT.top = 5;
			DrawText (dc, pszMsg, lstrlen (pszMsg), &rcT, DT_LEFT | DT_TOP);
			EndPaint (hWnd, &ps);
			return 0;
		
	}

	return DefWindowProc (hWnd, uMsg, wp, lp);
}