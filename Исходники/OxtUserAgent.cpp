static void OxtUpdateScreens(BOOL bClearScreens)
{
    DWORD dwDevNum;
    int iCount = 0;
    DISPLAY_DEVICE DisplayDevice;
    BOOL bRet;
    IOxtGuestServices *piOxtSvcs = NULL;
    HRESULT hr;
    int iWidth, iHeight;
    WCHAR wszData[MAX_LOADSTRING];
    CComBSTR bstrPath, bstrValue;

    hr = ::CoCreateInstance(CLSID_OxtGuestServices,
                            NULL,
                            CLSCTX_LOCAL_SERVER,
                            IID_IOxtGuestServices,
                            (LPVOID*)&piOxtSvcs);
    if (FAILED(hr))
    {
        // Not much we can do...
        return;
    }

    if (bClearScreens)
    {
        bstrPath = L"display/activeAdapter";
        bstrValue = L"0";
        piOxtSvcs->XenStoreWrite(bstrPath, bstrValue);
        return;
    }

    ::memset(&DisplayDevice, 0, sizeof(DISPLAY_DEVICE));
    DisplayDevice.cb = sizeof(DISPLAY_DEVICE);

    for (dwDevNum = 0; ; dwDevNum++)
    {
        bRet = ::EnumDisplayDevices(NULL, dwDevNum, &DisplayDevice, 0);
        if (!bRet)
        {
            // We are done, error returned when there are no more
            break;
        }

        if (((DisplayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE) == 0) ||
            (DisplayDevice.StateFlags & DISPLAY_DEVICE_REMOTE))
        {
            continue;
        }

        _snwprintf(wszData, MAX_LOADSTRING, L"display/activeAdapter/%d", iCount);
        bstrPath = wszData;
        bstrValue = DisplayDevice.DeviceString;
        piOxtSvcs->XenStoreWrite(bstrPath, bstrValue);

        iCount++;
    }

    // First the active adapter count (not sure if it is used though).
    bstrPath = L"display/activeAdapter";
    _snwprintf(wszData, MAX_LOADSTRING, L"%d", iCount);
    bstrValue = wszData;
    piOxtSvcs->XenStoreWrite(bstrPath, bstrValue);

    iWidth = ::GetSystemMetrics(SM_CXVIRTUALSCREEN);
    iHeight = ::GetSystemMetrics(SM_CYVIRTUALSCREEN);

    bstrPath = L"attr/desktopDimensions";
    _snwprintf(wszData, MAX_LOADSTRING, L"%d %d", iWidth, iHeight);
    bstrValue = wszData;
    piOxtSvcs->XenStoreWrite(bstrPath, bstrValue);

    piOxtSvcs->Release();
}