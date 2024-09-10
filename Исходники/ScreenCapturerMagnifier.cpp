bool ScreenCapturerMagnifier::InitializeMagnifier()
{
    BOOL bResult;

    // Import necessary functions
    m_hMagLib = ::LoadLibrary(L"Magnification.dll");
    if (!m_hMagLib) {
        TRACE(L"Failed to load Magnification.dll library\n");
        return false;
    }

    m_MagInitializeFunc              = reinterpret_cast<MagInitializeFunc>(GetProcAddress(m_hMagLib, "MagInitialize"));
    m_MagUninitializeFunc            = reinterpret_cast<MagUninitializeFunc>(GetProcAddress(m_hMagLib, "MagUninitialize"));
    m_MagSetWindowSourceFunc         = reinterpret_cast<MagSetWindowSourceFunc>(GetProcAddress(m_hMagLib, "MagSetWindowSource"));
    m_MagSetWindowFilterListFunc     = reinterpret_cast<MagSetWindowFilterListFunc>(GetProcAddress(m_hMagLib, "MagSetWindowFilterList"));
    m_MagSetImageScalingCallbackFunc = reinterpret_cast<MagSetImageScalingCallbackFunc>(GetProcAddress(m_hMagLib, "MagSetImageScalingCallback"));

    if (!m_MagInitializeFunc || !m_MagUninitializeFunc || !m_MagSetWindowSourceFunc ||
        !m_MagSetWindowFilterListFunc || !m_MagSetImageScalingCallbackFunc) {
        TRACE(L"Failed to initialize one of the Magnification functions\n");
        return false;
    }

    // Initialize Magnifier
    bResult = m_MagInitializeFunc();
    if (!bResult) {
        TRACE(L"MagInitialize() failed\n");
        return false;
    }

    // Create host window
    HMODULE hInst;
    bResult = GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, 
                                 reinterpret_cast<char*>(&DefWindowProc), 
                                 &hInst);
    if (!bResult) {
        m_MagUninitializeFunc();
        TRACE(L"GetModuleHandle() failed\n");
        return false;
    }

    // Register host window class
    WNDCLASSEX wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = &DefWindowProc;
    wcex.hInstance = hInst;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.lpszClassName = kMagnifierHostClass;

    RegisterClassEx(&wcex);

    m_hHostWindow = CreateWindowEx(WS_EX_LAYERED,
                                   kMagnifierHostClass,
                                   kHostWindowName,
                                   0,
                                   0, 0, 0, 0,
                                   NULL,
                                   NULL,
                                   hInst,
                                   NULL);
    if (!m_hHostWindow) {
        m_MagUninitializeFunc();
        TRACE(L"Failed to create host window\n");
        return false;
    }

    // Create the magnifier control in host window created above
    m_hMagnifierControlWindow = CreateWindow(kMagnifierWindowClass,
                                             kMagnifierWindowName,
                                             WS_CHILD | WS_VISIBLE | MS_SHOWMAGNIFIEDCURSOR,
                                             0, 0, 0, 0,
                                             m_hHostWindow,
                                             NULL,
                                             NULL,
                                             NULL);
    if (!m_hMagnifierControlWindow) {
        m_MagUninitializeFunc();
        TRACE(L"CreteWindow for Magnifier Control failed\n");
        return false;
    }

    // Hide host window
    ShowWindow(m_hHostWindow, SW_HIDE);

    // Set callback to receive captured image
    bResult = m_MagSetImageScalingCallbackFunc(m_hMagnifierControlWindow, &ScreenCapturerMagnifier::OnMagImageScalingCallback);
    if (!bResult) {
        m_MagUninitializeFunc();
        TRACE(L"Failed to set Magnifier callback\n");
        return false;
    }

    // Don't forget to try to exclude window here
    if (m_hExcludedWindow) {
        bResult = m_MagSetWindowFilterListFunc(m_hMagnifierControlWindow, MW_FILTERMODE_EXCLUDE, 1, &m_hExcludedWindow);
        if (!bResult) {
            TRACE(L"Failed to exclude requested window: 0x%x\n", GetLastError());
            return false;
        }
    }

    g_Owner = this;

    m_bMagInitialized = true;
    return true;
}