MMRESULT
WdmAudOpenSoundDeviceByLegacy(
    IN PSOUND_DEVICE SoundDevice,
    OUT PVOID *Handle)
{
    HDEVINFO hDevInfo;
    SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
    GUID SWBusGuid = {STATIC_KSCATEGORY_WDMAUD};
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W DeviceInterfaceDetailData;

    if ( KernelHandle == INVALID_HANDLE_VALUE )
    {
        hDevInfo = SetupDiGetClassDevsW(&SWBusGuid, NULL, NULL,  DIGCF_DEVICEINTERFACE| DIGCF_PRESENT);
        if (!hDevInfo)
        {
            // failed
            return MMSYSERR_ERROR;
        }

        DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
        if (!SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &SWBusGuid, 0, &DeviceInterfaceData))
        {
            // failed
            SetupDiDestroyDeviceInfoList(hDevInfo);
            return MMSYSERR_ERROR;
        }

        DeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)HeapAlloc(GetProcessHeap(), 0, MAX_PATH * sizeof(WCHAR) + sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W));
        if (!DeviceInterfaceDetailData)
        {
            // failed
            SetupDiDestroyDeviceInfoList(hDevInfo);
            return MMSYSERR_ERROR;
        }

        DeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W);
        if (!SetupDiGetDeviceInterfaceDetailW(hDevInfo,  &DeviceInterfaceData, DeviceInterfaceDetailData,MAX_PATH * sizeof(WCHAR) + sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W), NULL, NULL))
        {
            // failed
            HeapFree(GetProcessHeap(), 0, DeviceInterfaceDetailData);
            SetupDiDestroyDeviceInfoList(hDevInfo);
            return MMSYSERR_ERROR;
        }
        SND_TRACE(L"Opening wdmaud device '%s'\n",DeviceInterfaceDetailData->DevicePath);
        KernelHandle = CreateFileW(DeviceInterfaceDetailData->DevicePath,
                                   GENERIC_READ | GENERIC_WRITE,
                                   0,
                                   NULL,
                                   OPEN_EXISTING,
                                   FILE_FLAG_OVERLAPPED,
                                   NULL);

        HeapFree(GetProcessHeap(), 0, DeviceInterfaceDetailData);
        SetupDiDestroyDeviceInfoList(hDevInfo);
    }


    if ( KernelHandle == INVALID_HANDLE_VALUE )
        return MMSYSERR_ERROR;

    ++ OpenCount;
    return MMSYSERR_NOERROR;

}