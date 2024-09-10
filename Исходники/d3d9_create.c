static BOOL GetDisplayDeviceInfo(IN OUT LPDIRECT3D9_INT pDirect3D9)
{
    DISPLAY_DEVICEA DisplayDevice;
    DWORD AdapterIndex;

    memset(&DisplayDevice, 0, sizeof(DISPLAY_DEVICEA));
    DisplayDevice.cb = sizeof(DISPLAY_DEVICEA);   

    pDirect3D9->NumDisplayAdapters = 0;
    D3D9_PrimaryDeviceName[0] = '\0';

    AdapterIndex = 0;
    while (EnumDisplayDevicesA(NULL, AdapterIndex, &DisplayDevice, 0) == TRUE &&
           pDirect3D9->NumDisplayAdapters < D3D9_INT_MAX_NUM_ADAPTERS)
    {
        if ((DisplayDevice.StateFlags & (DISPLAY_DEVICE_DISCONNECT | DISPLAY_DEVICE_MIRRORING_DRIVER)) == 0 &&
            (DisplayDevice.StateFlags & (DISPLAY_DEVICE_PRIMARY_DEVICE | DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)) != 0)
        {
            SetAdapterInfo(&pDirect3D9->DisplayAdapters[pDirect3D9->NumDisplayAdapters], &DisplayDevice);

            if (pDirect3D9->NumDisplayAdapters == 0)
                lstrcpynA(D3D9_PrimaryDeviceName, DisplayDevice.DeviceName, sizeof(D3D9_PrimaryDeviceName));

            ++pDirect3D9->NumDisplayAdapters;
            break;
        }

        ++AdapterIndex;
    }

    AdapterIndex = 0;
    while (EnumDisplayDevicesA(NULL, AdapterIndex, &DisplayDevice, 0) == TRUE &&
           pDirect3D9->NumDisplayAdapters < D3D9_INT_MAX_NUM_ADAPTERS)
    {
        if ((DisplayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 0 &&
            (DisplayDevice.StateFlags & (DISPLAY_DEVICE_MIRRORING_DRIVER | DISPLAY_DEVICE_PRIMARY_DEVICE)) == 0)
        {
            SetAdapterInfo(&pDirect3D9->DisplayAdapters[pDirect3D9->NumDisplayAdapters], &DisplayDevice);
            ++pDirect3D9->NumDisplayAdapters;
        }

        ++AdapterIndex;
    }

    /* Check if minimum DirectDraw is supported */
    if (IsDirectDrawSupported() == FALSE)
        return FALSE;

    for (AdapterIndex = 0; AdapterIndex < pDirect3D9->NumDisplayAdapters; AdapterIndex++)
    {
        GetDirect3D9AdapterInfo(pDirect3D9->DisplayAdapters, AdapterIndex);
    }

    return TRUE;
}