LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message,
					 WPARAM wParam, LPARAM lParam)
{
	static HGLRC hRC;
	static DWORD timer = 1;
	HDC hDC;
    RECT WindowRect;
	int width;
	int height;

	switch (message)
	{
	case WM_CREATE:
		ReadRegistry();
		hRC = InitOGLWindow(hWnd);
		GetClientRect (hWnd, &WindowRect);
		width = WindowRect.right - WindowRect.left;
		height = WindowRect.bottom - WindowRect.top;
		InitOpenGL(width,height);
		SetTimer(hWnd, timer, 5, NULL);
		break;
	case WM_TIMER:
		hDC = GetDC(hWnd);
		Display();
		SwapBuffers(hDC);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_DESTROY:
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);
		break;
	}

	return DefScreenSaverProc(hWnd, message, wParam, lParam);
}