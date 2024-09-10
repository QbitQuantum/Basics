LONG WINAPI ScreenSaverProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam){
    // Handles screen saver messages
    switch(message)
    {
    case WM_CREATE:
        // Creation of the screen saver window
		hWnd = hwnd;
		SetupOpenGL();
		// Set Timer (Target 60 fps ish (1000/60 = 16)
		uTimer = SetTimer(hwnd, 1, 16, NULL);
        return 0;

    case WM_ERASEBKGND:
        // Erases the screen saver background
		// Not needed with OpenGL
        return 0;

    case WM_TIMER:
        // Handles the timer
		DrawGLScene();
        return 0;

    case WM_DESTROY:
        // Cleans up the screen saver window
		KillTimer(hwnd, uTimer);
		KillGL();
        PostQuitMessage(0);
        return 0;
    }
    return DefScreenSaverProc(hwnd,message,wparam,lparam);
}