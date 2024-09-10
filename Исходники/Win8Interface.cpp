BOOL CBtWin8Interface::Init()
{
    if ((m_hDevice = OpenBleDevice(&m_bth)) == INVALID_HANDLE_VALUE)
        return FALSE;

	USHORT num = 0;
	HRESULT hr;

    FP_BluetoothGATTGetServices pBluetoothGATTGetServices = (FP_BluetoothGATTGetServices)GetProcAddress(m_hLib, "BluetoothGATTGetServices");
	hr = pBluetoothGATTGetServices(m_hDevice, 0, NULL, &num, BLUETOOTH_GATT_FLAG_NONE);
    if (num == 0)
        return FALSE;

    PBTH_LE_GATT_SERVICE pServices = (PBTH_LE_GATT_SERVICE) malloc(sizeof(BTH_LE_GATT_SERVICE) * num);
    if (pServices == NULL) 
        return FALSE;

    RtlZeroMemory(pServices, sizeof(BTH_LE_GATT_SERVICE) * num);
    
    hr = pBluetoothGATTGetServices(m_hDevice, num, pServices, &num, BLUETOOTH_GATT_FLAG_NONE);
    if (S_OK != hr) 
    {
        ods("BluetoothGATTGetServices - Actual Data %x", hr);
        return FALSE;
    }

    // search for SPI COMM services.
    _BTH_LE_UUID uuidSpiComm;
    uuidSpiComm.IsShortUuid = FALSE;
    uuidSpiComm.Value.LongUuid = GUID_SPI_COMM_SERVICE;
    for (int i = 0; i < num; i++)
    {
        if (IsBthLEUuidMatch(pServices[i].ServiceUuid, uuidSpiComm))
            m_service = pServices[i];
    }

    PBTH_LE_GATT_CHARACTERISTIC pChars;

    FP_BluetoothGATTGetCharacteristics pBluetoothGATTGetCharacteristics = (FP_BluetoothGATTGetCharacteristics)GetProcAddress(m_hLib, "BluetoothGATTGetCharacteristics");

    // Go through all characteristics of the SPI COMM service to find Control Point and Data
    num = 0;
	pBluetoothGATTGetCharacteristics(m_hDevice, &m_service, 0, NULL, &num, BLUETOOTH_GATT_FLAG_NONE);
	if (num != 0)
	{
	    if ((pChars = new BTH_LE_GATT_CHARACTERISTIC[num]) == NULL)
		    return FALSE;

        if ((pBluetoothGATTGetCharacteristics(m_hDevice, &m_service, num, pChars, &num, BLUETOOTH_GATT_FLAG_NONE)) != S_OK)
	    {
            ods("LoadCharacteristics hr:0x%x\n", hr);
		    delete [] pChars;
		    return FALSE;
	    }
    }
    // search for SPI Comm service characteristics.
    m_charSpiCommControlPoint.AttributeHandle = 0;
    m_charSpiCommData.AttributeHandle = 0;

    _BTH_LE_UUID charControlPoint, charData;
    charControlPoint.IsShortUuid = FALSE;
    charControlPoint.Value.LongUuid = GUID_SPI_COMM_CHARACTERISTIC_CONTROL_POINT;
    charData.IsShortUuid = FALSE;
    charData.Value.LongUuid = GUID_SPI_COMM_CHARACTERISTIC_DATA;
    for (int i = 0; i < num; i++)
    {
        BTH_LE_GATT_DESCRIPTOR *pClientConfig;

        if (IsBthLEUuidMatch(pChars[i].CharacteristicUuid, charControlPoint))
        {
            m_charSpiCommControlPoint = pChars[i];
            pClientConfig = &m_descrSpiDataClientConfig;
        }
        else if (IsBthLEUuidMatch(pChars[i].CharacteristicUuid, charData))
        {
            m_charSpiCommData = pChars[i];
            pClientConfig = &m_descrSpiControlClientConfig;
        }
        else 
            continue;

        PBTH_LE_GATT_DESCRIPTOR pDescrs = NULL;
        USHORT numDescr = 0;

        FP_BluetoothGATTGetDescriptors pBluetoothGATTGetDescriptors = (FP_BluetoothGATTGetDescriptors)GetProcAddress(m_hLib, "BluetoothGATTGetDescriptors");
	    pBluetoothGATTGetDescriptors(m_hDevice, &pChars[i], 0, NULL, &numDescr, BLUETOOTH_GATT_FLAG_NONE);
	    if (numDescr != 0)
	    {
	        if ((pDescrs = new BTH_LE_GATT_DESCRIPTOR[numDescr]) == NULL)
		        break;

            if ((pBluetoothGATTGetDescriptors(m_hDevice, &pChars[i], numDescr, pDescrs, &numDescr, BLUETOOTH_GATT_FLAG_NONE)) != S_OK)
	        {
                ods("LoadCharacteristics hr:0x%x\n", hr);
		        delete [] pDescrs;
		        break;
	        }
        }

        // search for client configuration descriptor.
        _BTH_LE_UUID uuidClientConfig;
        uuidClientConfig.IsShortUuid = TRUE;
        uuidClientConfig.Value.ShortUuid = BTW_GATT_UUID_DESCRIPTOR_CLIENT_CONFIG;

        for (int j = 0; j < numDescr; j++)
        {
            if (IsBthLEUuidMatch(pDescrs[j].DescriptorUuid, uuidClientConfig))
            {
                *pClientConfig = pDescrs[j];
                break;
            }
        }
        delete []pDescrs;
    }
    free (pServices);
    return TRUE;
}