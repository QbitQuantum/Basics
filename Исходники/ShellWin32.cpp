bool Shell::OpenWindow(const char* name, bool attach_opengl)
{
    WNDCLASS window_class;

    // Fill out the window class struct.
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = WindowProcedure;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = instance_handle;
    window_class.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = NULL;
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = name;

    if (!RegisterClass(&window_class))
    {
        DisplayError("Could not register window class.");

        CloseWindow();
        return false;
    }

    window_handle = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
                                   name,	// Window class name.
                                   name,
                                   WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
                                   0, 0,	// Window position.
                                   0, 0,	// Window size.
                                   NULL,
                                   NULL,
                                   instance_handle,
                                   NULL);
    if (!window_handle)
    {
        DisplayError("Could not create window.");
        CloseWindow();

        return false;
    }

    instance_name = name;

    DWORD style = WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX;
    DWORD extended_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

    // Adjust the window size to take into account the edges
    RECT window_rect;
    window_rect.top = 0;
    window_rect.left = 0;
    window_rect.right = 1024;
    window_rect.bottom = 768;
    AdjustWindowRectEx(&window_rect, style, FALSE, extended_style);

    SetWindowLong(window_handle, GWL_EXSTYLE, extended_style);
    SetWindowLong(window_handle, GWL_STYLE, style);

    // Resize the window.
    SetWindowPos(window_handle, HWND_TOP, 0, 0, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, SWP_NOACTIVATE);

    // Display the new window
    ShowWindow(window_handle, SW_SHOW);
    SetForegroundWindow(window_handle);
    SetFocus(window_handle);

    // Attach OpenGL if necessary
    if (attach_opengl)
    {
        opengl_attached = AttachOpenGL();
        if (!opengl_attached)
            return false;
    }

    return true;
}