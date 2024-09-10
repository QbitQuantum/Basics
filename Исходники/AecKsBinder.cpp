///////////////////////////////////////////////////////////////////////////
//
// Function:
//      EnumDevice
//
// Description:
//      Enumerate audio device and return the device information.
//
//  Parameters:
//      eDataFlow: eRender for render device, eCapture for capture device
//      uNumElements: Size of audio device info structure array.
//      pDevicInfo: device info structure array. Caller is responsible to allocate and free
//                  memory. The array size is specified by uNumElements.
//
// Return:
//      S_OK if successful
//
///////////////////////////////////////////////////////////////////////////////
HRESULT EnumDevice(EDataFlow eDataFlow, UINT uNumElements, AUDIO_DEVICE_INFO *pDevicInfo)
{
    HRESULT hResult = S_OK;
    WCHAR* pszDeviceId = NULL;
    PROPVARIANT value;
    UINT index, dwCount;
    bool IsMicArrayDevice;

    CComPtr<IMMDeviceEnumerator> spEnumerator;
    CComPtr<IMMDeviceCollection> spEndpoints;    

    hResult = spEnumerator.CoCreateInstance(__uuidof(MMDeviceEnumerator));
    IF_FAILED_JUMP(hResult, Exit);

    hResult = spEnumerator->EnumAudioEndpoints(eDataFlow, DEVICE_STATE_ACTIVE, &spEndpoints);
    IF_FAILED_JUMP(hResult, Exit);

    hResult = spEndpoints->GetCount(&dwCount);
    IF_FAILED_JUMP(hResult, Exit);

    if (dwCount != uNumElements)
        return E_INVALIDARG;

    ZeroMemory(pDevicInfo, sizeof(AUDIO_DEVICE_INFO)*uNumElements);
    
    for (index = 0; index < dwCount; index++)
    {
        CComPtr<IMMDevice> spDevice;
        CComPtr<IPropertyStore> spProperties;

        PropVariantInit(&value);

        hResult = spEndpoints->Item(index, &spDevice);
        IF_FAILED_JUMP(hResult, Exit);
         
        hResult = spDevice->GetId(&pszDeviceId);
        IF_FAILED_JUMP(hResult, Exit);

        hResult = spDevice->OpenPropertyStore(STGM_READ, &spProperties);
        IF_FAILED_JUMP(hResult, Exit);

        hResult = spProperties->GetValue(PKEY_Device_FriendlyName, &value);
        IF_FAILED_JUMP(hResult, Exit);

        EndpointIsMicArray(spDevice, IsMicArrayDevice);

        StringCchCopy(pDevicInfo[index].szDeviceID, MAX_STR_LEN-1, pszDeviceId);
        StringCchCopy(pDevicInfo[index].szDeviceName, MAX_STR_LEN-1, value.pwszVal);
        pDevicInfo[index].bIsMicArrayDevice = IsMicArrayDevice;
        
        PropVariantClear(&value);
        CoTaskMemFree(pszDeviceId);
        pszDeviceId = NULL;
    }

Exit:
    return hResult;
}