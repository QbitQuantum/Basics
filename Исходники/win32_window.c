// Creates the GLFW window and rendering context
//
static GLFWbool createWindow(_GLFWwindow* window,
                             const _GLFWwndconfig* wndconfig,
                             const _GLFWctxconfig* ctxconfig,
                             const _GLFWfbconfig* fbconfig)
{
    int xpos, ypos, fullWidth, fullHeight;
    WCHAR* wideTitle;

    if (wndconfig->monitor)
    {
        GLFWvidmode mode;

        // NOTE: This window placement is temporary and approximate, as the
        //       correct position and size cannot be known until the monitor
        //       video mode has been set
        _glfwPlatformGetMonitorPos(wndconfig->monitor, &xpos, &ypos);
        _glfwPlatformGetVideoMode(wndconfig->monitor, &mode);
        fullWidth  = mode.width;
        fullHeight = mode.height;
    }
    else
    {
        xpos = CW_USEDEFAULT;
        ypos = CW_USEDEFAULT;

        getFullWindowSize(getWindowStyle(window), getWindowExStyle(window),
                          wndconfig->width, wndconfig->height,
                          &fullWidth, &fullHeight);
    }

    wideTitle = _glfwCreateWideStringFromUTF8(wndconfig->title);
    if (!wideTitle)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Win32: Failed to convert window title to UTF-16");
        return GLFW_FALSE;
    }

    window->win32.handle = CreateWindowExW(getWindowExStyle(window),
                                           _GLFW_WNDCLASSNAME,
                                           wideTitle,
                                           getWindowStyle(window),
                                           xpos, ypos,
                                           fullWidth, fullHeight,
                                           NULL, // No parent window
                                           NULL, // No window menu
                                           GetModuleHandleW(NULL),
                                           window); // Pass object to WM_CREATE

    free(wideTitle);

    if (!window->win32.handle)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Win32: Failed to create window");
        return GLFW_FALSE;
    }

    if (_glfw_ChangeWindowMessageFilterEx)
    {
        _glfw_ChangeWindowMessageFilterEx(window->win32.handle,
                                          WM_DROPFILES, MSGFLT_ALLOW, NULL);
        _glfw_ChangeWindowMessageFilterEx(window->win32.handle,
                                          WM_COPYDATA, MSGFLT_ALLOW, NULL);
        _glfw_ChangeWindowMessageFilterEx(window->win32.handle,
                                          WM_COPYGLOBALDATA, MSGFLT_ALLOW, NULL);
    }

    if (wndconfig->floating && !wndconfig->monitor)
    {
        SetWindowPos(window->win32.handle,
                     HWND_TOPMOST,
                     0, 0, 0, 0,
                     SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
    }

    DragAcceptFiles(window->win32.handle, TRUE);

    if (!_glfwCreateContext(window, ctxconfig, fbconfig))
        return GLFW_FALSE;

    window->win32.minwidth  = GLFW_DONT_CARE;
    window->win32.minheight = GLFW_DONT_CARE;
    window->win32.maxwidth  = GLFW_DONT_CARE;
    window->win32.maxheight = GLFW_DONT_CARE;
    window->win32.numer     = GLFW_DONT_CARE;
    window->win32.denom     = GLFW_DONT_CARE;

    return GLFW_TRUE;
}