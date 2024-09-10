LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		InitSaver(hWnd);
		break;

	case WM_TIMER:
		OnTimer(hWnd, (UINT)wParam);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, IDT_TIMER);
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
#ifdef DEBUG_MODE // in debug mode, user can exit program by press "ESC"
		if(VK_ESCAPE == wParam)
			PostQuitMessage(0);
#endif
		if(IsMagicKey((char)wParam))
			return 0;
		break;
	}

#ifndef DEBUG_MODE
	return DefScreenSaverProc(hWnd, message, wParam, lParam);
#else
	return DefWindowProc(hWnd, message, wParam, lParam);
#endif
}