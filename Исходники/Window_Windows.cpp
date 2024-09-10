  Window::Window(Engine *aEngine, const char *aWindowName,
                 const char *aWindowIcon, const char *aCursorIcon, int aWidth,
                 int aHeight, Window *aParentWindow)
    : mEngine(aEngine), mParentWindow(aParentWindow), mHeight(aHeight), mWidth(aWidth)
  {
    WindowData *windowData = mPlatformSpecificData.ConstructAndGet<WindowData>();

    WNDCLASS windowsData;

    if (aWindowName == nullptr)
    {
      aWindowName = "Yours-Truly-Engine";
    }

    if (nullptr == aWindowIcon)
    {
      aWindowIcon = IDI_APPLICATION;
    }

    if (nullptr == aCursorIcon)
    {
      aCursorIcon = IDC_ARROW;
    }

    HWND parentHandle = nullptr;
    if (nullptr != aParentWindow)
    {
      parentHandle = aParentWindow->mPlatformSpecificData.Get<WindowData>()->mWindowHandle;
    }

    windowsData.style = CS_HREDRAW | CS_VREDRAW;

    //TODO: Investigate the following flags
    //mData.mWindowsData.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

    // Set our message pump callback.
    windowsData.lpfnWndProc = WindowsMessagePump;
    windowsData.cbClsExtra = 0;
    windowsData.cbWndExtra = 0;

    // This needs to be changed for multiple windows to work, I think.
    windowData->mInstance = GetModuleHandleA(nullptr);
    windowsData.hInstance = windowData->mInstance;

    windowsData.hIcon = LoadIconA(nullptr, aWindowIcon);

    windowsData.hCursor = LoadCursorA(nullptr, aCursorIcon);

    windowsData.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowsData.lpszMenuName = aWindowName;
    windowsData.lpszClassName = "Yours-Truly-Engine_Game";

    RegisterClass(&windowsData);

    windowData->mWindowHandle = CreateWindowExA(
                                                0,
                                                windowsData.lpszClassName,
                                                windowsData.lpszMenuName,
                                                WS_OVERLAPPEDWINDOW,
                                                CW_USEDEFAULT,
                                                CW_USEDEFAULT,
                                                aWidth,
                                                aHeight,
                                                parentHandle,
                                                nullptr,
                                                windowsData.hInstance,
                                                this
                                               );

    // The window was sized to the values we want for the client area.
    // Add the difference between the two to grow the client area correctly,
    // unless the windows border size changes based on window size or 
    // something but thats weird so I'm not going to deal with that.
    RECT clientSize;
    GetClientRect(windowData->mWindowHandle, &clientSize);

    // Keep the previous position (more or less)
    RECT forPosition;
    GetWindowRect(windowData->mWindowHandle, &forPosition);
    int differenceX = aWidth - clientSize.right;
    int differenceY = aHeight - clientSize.bottom;

    // Try to keep the window centered by assuming the border is spaced
    // evenly (almost certainly wrong on the Y axis if it has a window title)
    MoveWindow(
               windowData->mWindowHandle, 
               forPosition.left - differenceX / 2,
               forPosition.top - differenceY / 2, 
               aWidth + differenceX,
               aHeight + differenceY, 
               false
              );

    ShowWindow(windowData->mWindowHandle, SW_SHOWNORMAL);
    UpdateWindow(windowData->mWindowHandle);
  }