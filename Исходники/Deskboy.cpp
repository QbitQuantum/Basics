	LRESULT onDestroy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ChangeClipboardChain(hWnd, hwndNextViewer);
		PostQuitMessage(0);
		return 0;
	}