internal void
Win32LoadWGLExtensions()
{
    WNDCLASSA WindowClass     = {0};
    WindowClass.lpfnWndProc   = DefWindowProcA;
    WindowClass.hInstance     = GetModuleHandle(0);
    WindowClass.lpszClassName = "LudusWGLLoader";

    if(RegisterClassA(&WindowClass))
    {
        HWND Window = CreateWindowExA(0,
                                      WindowClass.lpszClassName,
                                      "Ludus WGL Loader",
                                      0,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      CW_USEDEFAULT,
                                      0,
                                      0,
                                      WindowClass.hInstance,
                                      0);
        if(Window)
        {
            HDC WindowDC = GetDC(Window);
            Win32SetPixelFormat(WindowDC);
            HGLRC OpenGLRC = wglCreateContext(WindowDC);

            if(wglMakeCurrent(WindowDC, OpenGLRC))
            {
                wglSwapInterval = (wgl_swap_interval_ext*)wglGetProcAddress("wglSwapIntervalEXT");
                if(!wglSwapInterval)
                {
                    Win32Log("Couldnt get wglSwapInternalEXT extension");
                }

                wglChoosePixelFormatARB = (wgl_choose_pixel_format_arb*)wglGetProcAddress("wglChoosePixelFormatARB");
                if(!wglChoosePixelFormatARB)
                {
                    Win32Log("Couldnt get wglChoosePixelFormatARB extension");
                }

                wglCreateContextAttribsARB =
                    (wgl_create_context_attribs_arb*)wglGetProcAddress("wglCreateContextAttribsARB");
                if(!wglCreateContextAttribsARB)
                {
                    Win32Log("Couldnt get wglCreateContextAttribsARB extension");
                }

                wglMakeCurrent(0, 0);
            }

            wglDeleteContext(OpenGLRC);
            ReleaseDC(Window, WindowDC);
            DestroyWindow(Window);
        }
        else
        {
            Win32Log("Couldnt create WGL Loader Window");
            LOG_FORMATTED_ERROR(4096);
        }
    }
    else
    {
        Win32Log("Couldnt register class for WGL Loader Window");
        LOG_FORMATTED_ERROR(4096);
    }
}