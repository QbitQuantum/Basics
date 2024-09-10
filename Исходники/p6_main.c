long FAR PASCAL WindowProc(HWND hWnd, UINT message, 
						   WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rect; 
 
	switch(message)
	{
	case WM_CREATE: 
		ghDC = GetDC(hWnd); 
		if (!bSetupPixelFormat(ghDC)) 
			PostQuitMessage (0); 
 
		ghRC = wglCreateContext(ghDC); 
		if (!ghRC)
		{
			MessageBox(NULL, "Could not initialize GL", "ERROR", MB_OK);
			PostQuitMessage (0); 
		}
		if (!wglMakeCurrent(ghDC, ghRC))
		{
			MessageBox(NULL, "wglMakeCurrent failed", "ERROR", MB_OK);
			PostQuitMessage (0); 
		}
		GetClientRect(hWnd, &rect); 
		initializeGL(rect.right, rect.bottom); 
		// Other Initialisation should go here
		initText();
		TimeInit();
		TerrainInit("hmap.raw");

		break; 
	case WM_PAINT:
		ghDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return TRUE;

	case WM_SIZE: 
		GetClientRect(hWnd, &rect); 
		resize(rect.right, rect.bottom); 
		break; 

	case WM_CLOSE: 
		if (ghRC) 
			wglDeleteContext(ghRC); 
		if (ghDC) 
			ReleaseDC(hWnd, ghDC); 
		ghRC = 0; 
		ghDC = 0; 
		DestroyWindow (hWnd); 
		break; 
 
	case WM_DESTROY: 
		if (ghRC) 
			wglDeleteContext(ghRC); 
		if (ghDC) 
			ReleaseDC(hWnd, ghDC); 
		PostQuitMessage (0); 
		break; 

	case WM_KEYDOWN: 
		KeyDown(wParam);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);

}