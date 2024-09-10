int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR pszCmdLine,
    int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(pszCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if (SUCCEEDED(hr))
    {
        {
            DemoApp app;
            HWND hWndMain = NULL;

            hWndMain = app.Initialize(hInstance);
            hr = hWndMain ? S_OK : E_FAIL;

            if (SUCCEEDED(hr))
            {
                BOOL fRet;
                MSG msg;

                // Load accelerator table
                HACCEL haccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDA_ACCEL_TABLE));
                if (haccel == NULL) 
                {
                    hr = E_FAIL;
                }
                // Main message loop:
                while ((fRet = GetMessage(&msg, NULL, 0, 0)) != 0)
                {
                    if (fRet == -1)
                    {
                        break;
                    }
                    else
                    {
                        if (!TranslateAccelerator(hWndMain, haccel, &msg))
                        {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                        }
                    }
                }
            }
        }
        CoUninitialize();
    }

    return 0;
}