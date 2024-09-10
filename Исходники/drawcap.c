VOID CapTest(HWND hWnd,
	HDC hDc,
	LPRECT pR,
	WCHAR *Text,
	DWORD Flags,
	WCHAR *AddonStr,
	DWORD Addon)
{
	WCHAR Buf[512];

	lstrcpy(Buf, AddonStr);
	if(lstrlen(Buf))lstrcat(Buf, L" | ");
	lstrcat(Buf, Text);

	DrawText( hDc, Buf, lstrlen(Buf), pR, DT_LEFT );

	pR->top+=20;
	pR->bottom+=20;

	if(!DrawCaption(hWnd, hDc, pR, Flags | Addon))
	{
		printf("PAINT: DrawCaption failed: %d\n", (int)GetLastError());
	}

	pR->top+=30;
	pR->bottom+=30;
}