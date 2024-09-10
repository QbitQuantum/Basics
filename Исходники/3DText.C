LRESULT CALLBACK
ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT Screen;                            // Used Later On To Get The Size Of The Window
    GLuint PixelFormat;                     // Pixel Format Storage
    static PIXELFORMATDESCRIPTOR pfd=       // Pixel Format Descriptor
    {
        sizeof(PIXELFORMATDESCRIPTOR),      // Size Of This Pixel Format Descriptor
        1,                                  // Version Number (?)
        PFD_DRAW_TO_WINDOW |                // Format Must Support Window
        PFD_SUPPORT_OPENGL |                // Format Must Support OpenGL
        PFD_DOUBLEBUFFER,                   // Must Support Double Buffering
        PFD_TYPE_RGBA,                      // Request An RGBA Format
        16,                                 // Select A 16Bit Color Depth
        0, 0, 0, 0, 0, 0,                   // Color Bits Ignored (?)
        0,                                  // No Alpha Buffer
        0,                                  // Shift Bit Ignored (?)
        0,                                  // No Accumulation Buffer
        0, 0, 0, 0,                         // Accumulation Bits Ignored (?)
        16,                                 // 16Bit Z-Buffer (Depth Buffer)
        0,                                  // No Stencil Buffer
        0,                                  // No Auxiliary Buffer (?)
        PFD_MAIN_PLANE,                     // Main Drawing Layer
        0,                                  // Reserved (?)
        0, 0, 0                             // Layer Masks Ignored (?)
    };

    switch (message)
    {
        case WM_CREATE:
            LoadSettings();

            // Gets A Device Context For The Window
            hDC = GetDC(hWnd);

            // Finds The Closest Match To The Pixel Format We Set Above
            PixelFormat = ChoosePixelFormat(hDC, &pfd);

            // No Matching Pixel Format?
            if (!PixelFormat)
            {
                MessageBox(0, _TEXT("Can't Find A Suitable PixelFormat."), _TEXT("Error"),MB_OK | MB_ICONERROR);

                // This Sends A 'Message' Telling The Program To Quit
                PostQuitMessage(0);
                break;
            }

            // Can We Set The Pixel Mode?
            if (!SetPixelFormat(hDC, PixelFormat, &pfd))
            {
                MessageBox(0, _TEXT("Can't Set The PixelFormat."), _TEXT("Error"), MB_OK | MB_ICONERROR);

                // This Sends A 'Message' Telling The Program To Quit
                PostQuitMessage(0);
                break;
            }

            // Grab A Rendering Context
            hRC = wglCreateContext(hDC);

            // Did We Get One?
            if (!hRC)
            {
                MessageBox(0, _TEXT("Can't Create A GL Rendering Context."), _TEXT("Error"), MB_OK | MB_ICONERROR);

                // This Sends A 'Message' Telling The Program To Quit
                PostQuitMessage(0);
                break;
            }

            // Can We Make The RC Active?
            if (!wglMakeCurrent(hDC, hRC))
            {
                MessageBox(0, _TEXT("Can't Activate GLRC."), _TEXT("Error"), MB_OK | MB_ICONERROR);

                // This Sends A 'Message' Telling The Program To Quit
                PostQuitMessage(0);
                break;
            }

            // Grab Screen Info For The Current Window
            GetClientRect(hWnd, &Screen);

            // Initialize The GL Screen Using Screen Info
            InitGL(Screen.right, Screen.bottom);
            break;

        case WM_DESTROY:
            // Disable Fullscreen Mode
            ChangeDisplaySettings(NULL, 0);

            // Deletes The Font Display List
            KillFont();

            // Make The DC Current
            wglMakeCurrent(hDC, NULL);

            // Kill The RC
            wglDeleteContext(hRC);

            // Free The DC
            ReleaseDC(hWnd, hDC);
            break;

        case WM_PAINT:
            DrawGLScene();
            SwapBuffers(hDC);
            break;

        case WM_SIZE: // Resizing The Screen
            // Resize To The New Window Size
            ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
            break;

        default:
            // Pass Windows Messages to the default screensaver window procedure
            return DefScreenSaverProc(hWnd, message, wParam, lParam);
    }

    return 0;
}