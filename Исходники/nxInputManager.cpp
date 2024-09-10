BOOL CALLBACK nxInputManager::EnumJoysticksCallback( const DIDEVICEINSTANCE* pInstance,VOID* ptData )
{
    // Skip XInput devices
    if (nxXInputDevice::IsXInputDevice(pInstance->guidProduct))
        return DIENUM_CONTINUE;

    nxInputManager&objManager = nxInputManager::instance();

    LPDIRECTINPUTDEVICE8 ptDevice;
    //  Attempt to create a device interface for the joystick
    if (objManager.pDI->CreateDevice( pInstance->guidInstance, &ptDevice, NULL ) == DI_OK)
    {
        /*TODO: Set the range for axis and buttons
        DIPROPRANGE diPropRange;
        diPropRange.diph.dwSize = sizeof(DIPROPRANGE);
        diPropRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);*/


        // Set the device parameters
        if( ptDevice->SetDataFormat( &c_dfDIJoystick ) != DI_OK ||
            ptDevice->SetCooperativeLevel(NULL,DISCL_BACKGROUND|DISCL_NONEXCLUSIVE) != DI_OK ||
            ptDevice->EnumObjects(EnumObjectsCallback,reinterpret_cast<VOID*>(ptDevice),DIDFT_AXIS) != DI_OK)
        {
            ptDevice->Release();
        }
        else
        {
            // Create the interface to device id mapping
            nxDeviceId uDevId = objManager.CreateDeviceId();
            // Add the handle to device id mapping
            objManager.mpHandleId[ptDevice] = uDevId;
            // Add the device to the list of DInput devices (used for polling)
            objManager.stDInputDevices.insert(ptDevice);
            // Map the GUID to the device id
            objManager.SetGUIDMapping(uDevId,GUIDToString(pInstance->guidInstance));
        }
    }
    return DIENUM_CONTINUE;
}