BYTE GetWindowAlpha(HWND hWnd)
{
	BYTE alpha = 255;

	if ( GetWindowLong(hWnd, GWL_EXSTYLE) & WS_EX_LAYERED )
	{
		DWORD dwFlags = 0;
		if ( !GetLayeredWindowAttributes(hWnd, NULL, &alpha, &dwFlags) || !(dwFlags & LWA_ALPHA) )
			alpha = 255;		
	}

	return alpha;
}