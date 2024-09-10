DWORD WINAPI FTHelper2::FaceTrackingThread()
{
    FT_CAMERA_CONFIG videoConfig;
    FT_CAMERA_CONFIG depthConfig;
    FT_CAMERA_CONFIG* pDepthConfig = NULL;

    // Try to get the Kinect camera to work
    HRESULT hr = m_KinectSensor.Init(m_depthType, m_depthRes, m_bNearMode, FALSE, m_colorType, m_colorRes, m_bSeatedSkeleton);
    if (SUCCEEDED(hr))
    {
        m_KinectSensorPresent = TRUE;
        m_KinectSensor.GetVideoConfiguration(&videoConfig);
        m_KinectSensor.GetDepthConfiguration(&depthConfig);
        pDepthConfig = &depthConfig;
    }
    else
    {
        m_KinectSensorPresent = FALSE;

        MessageBoxW(m_hWnd, L"Could not initialize the Kinect sensor.\n", L"Face Tracker Initialization Error\n", MB_OK);
        return 1;
    }

    m_UserContext = new FTHelperContext[m_nbUsers];
    if (m_UserContext != 0)
    {
        memset(m_UserContext, 0, sizeof(FTHelperContext)*m_nbUsers);
    }
    else
    {
        MessageBoxW(m_hWnd, L"Could not allocate user context array.\n", L"Face Tracker Initialization Error\n", MB_OK);
        return 2;
    }

    for (UINT i=0; i<m_nbUsers; i++)
    {
        // Try to start the face tracker.
        m_UserContext[i].m_pFaceTracker = FTCreateFaceTracker(_opt);
        if (!m_UserContext[i].m_pFaceTracker)
        {
            MessageBoxW(m_hWnd, L"Could not create the face tracker.\n", L"Face Tracker Initialization Error\n", MB_OK);
            return 3;
        }

        hr = m_UserContext[i].m_pFaceTracker->Initialize(&videoConfig, pDepthConfig, NULL, NULL);
        if (FAILED(hr))
        {
            WCHAR path[512], buffer[1024];
            GetCurrentDirectoryW(ARRAYSIZE(path), path);
            wsprintf(buffer, L"Could not initialize face tracker (%s) for user %d.\n", path, i);

            MessageBoxW(m_hWnd, buffer, L"Face Tracker Initialization Error\n", MB_OK);

            return 4;
        }
        m_UserContext[i].m_pFaceTracker->CreateFTResult(&m_UserContext[i].m_pFTResult);
        if (!m_UserContext[i].m_pFTResult)
        {
            MessageBoxW(m_hWnd, L"Could not initialize the face tracker result for user %d.\n", L"Face Tracker Initialization Error\n", MB_OK);
            return 5;
        }
        m_UserContext[i].m_LastTrackSucceeded = false;
    }

    // Initialize the RGB image.
    m_colorImage = FTCreateImage();
    if (!m_colorImage || FAILED(hr = m_colorImage->Allocate(videoConfig.Width, videoConfig.Height, FTIMAGEFORMAT_UINT8_B8G8R8X8)))
    {
        return 6;
    }

    if (pDepthConfig)
    {
        m_depthImage = FTCreateImage();
        if (!m_depthImage || FAILED(hr = m_depthImage->Allocate(depthConfig.Width, depthConfig.Height, FTIMAGEFORMAT_UINT16_D13P3)))
        {
            return 7;
        }
    }

    SetCenterOfImage(NULL);

    while (m_ApplicationIsRunning)
    {
        CheckCameraInput();
        InvalidateRect(m_hWnd, NULL, FALSE);
        UpdateWindow(m_hWnd);
        Sleep(16);
    }
    return 0;
}