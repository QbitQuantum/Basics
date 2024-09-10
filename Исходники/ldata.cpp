bool CG27::InitializeG27()  
{  
    HRESULT hr;  
  
    // Register with the DirectInput subsystem and get a pointer to a IDirectInput interface we can use.  
    // Create a DInput object  
  
    //initialize directinput library  
    if( FAILED( hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION,  
        IID_IDirectInput8, ( VOID** )&g_pDI, NULL ) ) )  
        return false;  
  
  
    LPDIRECTINPUTDEVICE8 joystick;  
  
    // Look for the first simple joystick we can find.  
    if (FAILED(hr = g_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback,  
        NULL, DIEDFL_ATTACHEDONLY))) {  
            return false;  
    }  
  
    if (g_pJoystick == NULL)    
    {  
//        ShowMessageBox("g27 not found, please check the connection, exiting........");  
		qDebug() << "fucklrl";
        return false;  
    }  
  
    if (FAILED(hr = g_pJoystick->SetDataFormat(&c_dfDIJoystick2)))  
    {  
//        ShowMessageBox(" set g27 data format error, exiting.......");  
		qDebug() << "fuckld";
        return false;  
    }  
  
    g_pJoystick->SetCooperativeLevel(NULL, DISCL_EXCLUSIVE|DISCL_FOREGROUND);  
  
    DIDEVCAPS capabilities;  
    capabilities.dwSize = sizeof(DIDEVCAPS);  
  
    g_pJoystick->GetCapabilities(&capabilities);  
  
    if (FAILED(hr=g_pJoystick->EnumObjects(enumAxesCallback, NULL, DIDFT_AXIS)))  
    {  
  
    }  
	qDebug() << "initializing succeeded";
    return true;  
}  