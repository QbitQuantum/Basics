void SDLWindow::setDimensions(const Rect2D& dims) {
    #ifdef G3D_WIN32
        int W = screenWidth();
        int H = screenHeight();

        int x = iClamp((int)dims.x0(), 0, W);
        int y = iClamp((int)dims.y0(), 0, H);
        int w = iClamp((int)dims.width(), 1, W);
        int h = iClamp((int)dims.height(), 1, H);

        SetWindowPos(_Win32HWND, NULL, x, y, w, h, SWP_NOZORDER);
        // Do not update settings-- wait for an event to notify us
    #endif

	#ifdef G3D_LINUX
		//TODO: Linux
	#endif 

    // TODO: OS X
}