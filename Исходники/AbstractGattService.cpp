HRESULT AbstractGattService::Initialize(
    _In_ IWDFDevice* pDevice,
    _In_ BthLEDevice * pBthLEDevice)
{
    HRESULT hr = S_OK;

    m_hEventSync = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (NULL == m_hEventSync)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        CHECK_HR(hr, "Failed to create the queue sync event");
    }

    if (SUCCEEDED(hr))
    {
        hr = GetDeviceAddressFromDevice(pDevice, &m_BthDeviceAddress);
    }

    if (SUCCEEDED(hr))
    {
        m_pDevice = pDevice;
        m_pBthLEDevice = pBthLEDevice;

        HBLUETOOTH_RADIO_FIND hRadioFind = NULL;
        BLUETOOTH_FIND_RADIO_PARAMS frp = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};

        hRadioFind = BluetoothFindFirstRadio(&frp, &m_hRadioHandle);
        if (NULL != hRadioFind) {
            BluetoothFindRadioClose(hRadioFind);
            hRadioFind = NULL;
        }

        if (NULL == m_hRadioHandle)
        {
            hr = E_FAIL;
            CHECK_HR(hr, "Failed to open a BT radio handle");
        }
    }

    if (SUCCEEDED(hr))
    {
        hr = StartMessagePump();
    }

    return hr;
}