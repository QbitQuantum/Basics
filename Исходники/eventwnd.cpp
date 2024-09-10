HRESULT
pEnumerateNdasportLogicalUnits(
    __inout CSimpleArray<HDEVNOTIFY>& DevNotifyHandles,
    __in HWND hWnd)
{
    HRESULT hr;

    HDEVINFO devInfoSet = SetupDiGetClassDevsW(
                              NULL,
                              NULL,
                              NULL,
                              DIGCF_ALLCLASSES | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

    if (INVALID_HANDLE_VALUE == devInfoSet)
    {
        hr = HRESULT_FROM_SETUPAPI(GetLastError());
        fprintf(stderr, "SetupDiGetClassDevs failed, hr=0x%X\n", hr);
        return hr;
    }

    SP_DEVINFO_DATA devInfoData;

    for (DWORD index = 0; ; ++index)
    {
        devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        BOOL success = SetupDiEnumDeviceInfo(devInfoSet, index, &devInfoData);
        if (!success)
        {
            if (ERROR_NO_MORE_ITEMS != GetLastError())
            {
                hr = HRESULT_FROM_SETUPAPI(GetLastError());
                fprintf(stderr, "SetupDiEnumDeviceInfo failed, hr=0x%X\n", hr);
            }
            break;
        }
        devInfoData.ClassGuid;
    }

    fprintf(stdout, "Enumerating DISK...\n");

    hr = pEnumerateNdasportLogicalUnits(
             DevNotifyHandles,
             hWnd,
             devInfoSet,
             &GUID_DEVINTERFACE_DISK);

    fprintf(stdout, "Enumerating CDROM...\n");

    hr = pEnumerateNdasportLogicalUnits(
             DevNotifyHandles,
             hWnd,
             devInfoSet,
             &GUID_DEVINTERFACE_CDROM);

    fprintf(stdout, "Enumerating TAPE...\n");

    hr = pEnumerateNdasportLogicalUnits(
             DevNotifyHandles,
             hWnd,
             devInfoSet,
             &GUID_DEVINTERFACE_TAPE);

    fprintf(stdout, "Enumerating WRITEONCEDISK...\n");

    hr = pEnumerateNdasportLogicalUnits(
             DevNotifyHandles,
             hWnd,
             devInfoSet,
             &GUID_DEVINTERFACE_WRITEONCEDISK);

    fprintf(stdout, "Enumerating MEDIUMCHANGER...\n");

    hr = pEnumerateNdasportLogicalUnits(
             DevNotifyHandles,
             hWnd,
             devInfoSet,
             &GUID_DEVINTERFACE_MEDIUMCHANGER);

    fprintf(stdout, "Enumerating CDCHANGER...\n");

    hr = pEnumerateNdasportLogicalUnits(
             DevNotifyHandles,
             hWnd,
             devInfoSet,
             &GUID_DEVINTERFACE_CDCHANGER);

    ATLVERIFY( SetupDiDestroyDeviceInfoList(devInfoSet) );

    return S_OK;
}