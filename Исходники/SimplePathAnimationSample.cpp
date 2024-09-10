HRESULT DemoApp::Initialize()
{
    HRESULT hr;

    //register window class
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = DemoApp::WndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = sizeof(LONG_PTR);
    wcex.hInstance     = HINST_THISCOMPONENT;
    wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName  = NULL;
    wcex.lpszClassName = L"D2DDemoApp";

    RegisterClassEx(&wcex);

    hr = CreateDeviceIndependentResources();
    if (SUCCEEDED(hr))
    {
        // Create the application window.
        //
        // Because the CreateWindow function takes its size in pixels, we
        // obtain the system DPI and use it to scale the window size.
        FLOAT dpiX, dpiY;
        m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

        m_hwnd = CreateWindow(
            L"D2DDemoApp",
            L"D2D Simple Path Animation Sample",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(512.f * dpiX / 96.f)),
            static_cast<UINT>(ceil(512.f * dpiY / 96.f)),
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this
            );
        hr = m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            float length = 0;

            hr = m_pPathGeometry->ComputeLength(
                NULL, //no transform
                &length
                );
            if (SUCCEEDED(hr))
            {
                m_Animation.SetStart(0);        //start at beginning of path
                m_Animation.SetEnd(length);     //length at end of path
                m_Animation.SetDuration(5.0f);  //seconds

                ZeroMemory(&m_DwmTimingInfo, sizeof(m_DwmTimingInfo));
                m_DwmTimingInfo.cbSize = sizeof(m_DwmTimingInfo);

                // Get the composition refresh rate. If the DWM isn't running,
                // get the refresh rate from GDI -- probably going to be 60Hz
                if (FAILED(DwmGetCompositionTimingInfo(NULL, &m_DwmTimingInfo)))
                {
                    HDC hdc = GetDC(m_hwnd);
                    m_DwmTimingInfo.rateCompose.uiDenominator = 1;
                    m_DwmTimingInfo.rateCompose.uiNumerator = GetDeviceCaps(hdc, VREFRESH);
                    ReleaseDC(m_hwnd, hdc);
                }

                ShowWindow(m_hwnd, SW_SHOWNORMAL);

                UpdateWindow(m_hwnd);
            }
        }
    }

    return hr;
}