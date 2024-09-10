static LRESULT CALLBACK FrameSubclass(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR dwRefData)
{
	HWND hwndTransfer = (HWND) dwRefData;
	switch (uMsg)
	{
	case WM_MOVE:
		{
			LPCALC lpCalc = (LPCALC) GetWindowLongPtr(hwndTransfer, GWLP_USERDATA);
			RECT wr;
			GetWindowRect(hwnd, &wr);

			DWORD dwSendWidth = (wr.right - wr.left) * 9 / 10;
			DWORD dwSendHeight = 90; //10 * HIWORD(GetDialogBaseUnits());

			LPSENDINFO lpsi = g_SendInfo[lpCalc];
			RECT rcLcd = { 0 };
			if (lpsi != NULL) {
				GetWindowRect(lpsi->hwndParent, &rcLcd);
			}

			SetWindowPos(hwndTransfer, NULL, 
				wr.left + ((wr.right - wr.left) - dwSendWidth) / 2,
				rcLcd.top + (rcLcd.bottom - rcLcd.top - dwSendHeight) / 2,
				dwSendWidth, dwSendHeight,
				SWP_NOSIZE | SWP_NOZORDER);
			break;
		}
	}
	return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}