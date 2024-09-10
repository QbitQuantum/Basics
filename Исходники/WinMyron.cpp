    WinWindow::WinWindow(int width, int height)
    {
        hInstance = GetModuleHandle(NULL);
        registerClass();
        createWindow(width, height);
		initGL();
        showWindow();
		setRenderRate(30);
    }