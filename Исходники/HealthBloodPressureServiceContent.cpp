HRESULT HealthBloodPressureServiceContent::InitializeContent(
    _In_ IWDFDevice* pDevice,
    _Inout_ DWORD *pdwLastObjectID,
    _In_ HANDLE hDeviceHandle,
    _In_ BthLEDevice * pBthLEDevice)
{
    HRESULT hr = S_OK;

    //
    // Service
    //
    PBTH_LE_GATT_SERVICE services = NULL;
    USHORT numServices = 0;
    USHORT numServicesActual = 0;
    USHORT serviceIndex = 0;
    BOOLEAN isFoundService = FALSE;

    //
    // Characteristic
    //
    PBTH_LE_GATT_CHARACTERISTIC characteristics = NULL;
    USHORT numChar = 0;
    USHORT numCharsActual = 0;
    BOOLEAN isCharacteristicFound = FALSE;
    USHORT foundCharacteristicIndex = 0;

    if (pDevice == NULL ||
        pdwLastObjectID == NULL ||
        hDeviceHandle == NULL)
    {
        hr = E_POINTER;
        CHECK_HR(hr, "Cannot have NULL parameter");
    }

    //
    // Save the WDF device and client context map for async events
    //
    if (SUCCEEDED(hr))
    {
        m_pDevice = pDevice;
        m_pBthLEDevice = pBthLEDevice;
    }

    //
    // Get the WpdSerializer to use to Object Change events
    //
    if (SUCCEEDED(hr))
    {
        hr = CoCreateInstance(CLSID_WpdSerializer,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              IID_IWpdSerializer,
                              (VOID**)&m_pWpdSerializer);
        CHECK_HR(hr, "Failed to CoCreate CLSID_WpdSerializer");
    }


    //
    // Get the number of services
    //
    if (SUCCEEDED(hr))
    {
        hr = BluetoothGATTGetServices(
                            hDeviceHandle,
                            0,
                            NULL,
                            &numServices,
                            BLUETOOTH_GATT_FLAG_NONE);

        if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) == hr)
        {
            hr = S_OK;
        }
        else
        {
            CHECK_HR(hr, "Failed to get the service count - changing to E_FAIL");
            hr = E_FAIL;
        }
    }

    if (SUCCEEDED(hr))
    {
        services = new BTH_LE_GATT_SERVICE[numServices];
        if (NULL == services)
        {
            hr = E_OUTOFMEMORY;
        }
        CHECK_HR(hr, "Failed to allocate the service buffer");
    }

    if (SUCCEEDED(hr))
    {
        //
        // Get the services
        //
        hr = BluetoothGATTGetServices(
                            hDeviceHandle,
                            numServices,
                            services,
                            &numServicesActual,
                            BLUETOOTH_GATT_FLAG_NONE);
        CHECK_HR(hr, "Failed to get the services");
    }

    if (SUCCEEDED(hr))
    {
        //
        // Double check to confirm that the number of services that are returned
        // are what we have expected, just in case if the cache has changed due
        // to things like service change events.
        //
        if (numServices != numServicesActual)
        {
            // The returned number of services do not match what we have
            // originally.
            hr = E_FAIL;
        }
        CHECK_HR(hr, "The service count doesn't match the returned services");
    }

    if (SUCCEEDED(hr))
    {
        //
        // Find the service in the list
        //
        for(USHORT i = 0; i < numServices; i++)
        {
            if (IsHealthBloodPressureServiceUuid(services[i].ServiceUuid)) {
                isFoundService = TRUE;
                serviceIndex = i;
                break;
            }            
        }

        if (FALSE == isFoundService)
        {
            hr = E_FAIL;
        }
        CHECK_HR(hr, "The HealthBloodPressure Service was not found");

    }

    if (SUCCEEDED(hr))
    {
        //
        // Find the blood pressure measurement characteristic
        //
        hr = BluetoothGATTGetCharacteristics(
                hDeviceHandle,
                &services[serviceIndex],
                0,
                NULL,
                &numChar,
                BLUETOOTH_GATT_FLAG_NONE);

        if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) == hr)
        {
            hr = S_OK;
        }
        else
        {
            CHECK_HR(hr, "Failed to get the Characteristic count - changing to E_FAIL");
            hr = E_FAIL;
        }
    }

    if (SUCCEEDED(hr))
    {
        characteristics= new BTH_LE_GATT_CHARACTERISTIC[numChar];
        if (NULL == characteristics)
        {
            hr = E_OUTOFMEMORY;
        }
        CHECK_HR(hr, "Failed to allocate the Characteristic buffer");
    }

    if (SUCCEEDED(hr))
    {
        hr = BluetoothGATTGetCharacteristics(
                hDeviceHandle,
                &services[serviceIndex],
                numChar,
                characteristics,
                &numCharsActual,
                BLUETOOTH_GATT_FLAG_NONE);
        CHECK_HR(hr, "Failed to get the Characteristics");
    }

    if (SUCCEEDED(hr))
    {
        //
        // Double check to confirm that the number of characteristics that are
        // returned are what we have expected,.
        //
        if (numChar != numCharsActual)
        {
            // The returned number of characteristics do not match what we have
            // originally.
            hr = E_FAIL;
        }
        CHECK_HR(hr, "Number of Characteristics do not match");
    }

    if (SUCCEEDED(hr))
    {
        for (USHORT i = 0; i < numChar; i++)
        {
            if (IsBloodPressureMeasurementCharacteristic(characteristics[i].CharacteristicUuid))
            {
                isCharacteristicFound = TRUE;
                foundCharacteristicIndex = i;
                break;
                }
        }

        if (FALSE == isCharacteristicFound)
        {
            hr = E_FAIL;
        }
        CHECK_HR(hr, "BloodPressureMeasurement characteristic not found");
    }

    if (SUCCEEDED(hr))
    {
        //
        // Cache the characteristic to differ reading the value when the client requests it (client polling)
        //
        CopyMemory(&m_BloodPressureMeasurementCharacteristic, &characteristics[foundCharacteristicIndex], sizeof(m_BloodPressureMeasurementCharacteristic));
        
        //
        // Setting the member DeviceHandle for use by SetCCCD
        //
        m_hDeviceHandle = hDeviceHandle;

        hr = SetCCCD();
        CHECK_HR(hr, "Setting the CCCD on Device Content initialization failed");

        if (SUCCEEDED(hr)) 
        {
            //
            // Setting a member flag to ensure we don't try to set the CCCD more than once
            // This is a performance optimization that avoids a cache query to get the current CCCD value
            // and also avoids resetting the CCCD (over the air - with the biggest performance hit)
            //
            CComCritSecLock<CComAutoCriticalSection> Lock(m_CCCDSetCS);
            m_bCCCDSet = TRUE;
        }

        //
        // This only needs to be set once, so ignoring errors in the event the device is not connectable (ie: reboot)
        //
        hr = S_OK;
    }

    //
    // Cleanup
    //
    if (NULL != services)
    {
        delete [] services;
    }

    if (NULL != characteristics)
    {
        delete [] characteristics;
    }

    return hr;
}