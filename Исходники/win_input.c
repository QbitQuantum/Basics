qboolean IN_InitDInput(void)
{
	HRESULT         hResult;
	DIPROPDWORD     dipdw = {
		{
		 sizeof(DIPROPDWORD),	// diph.dwSize
		 sizeof(DIPROPHEADER),	// diph.dwHeaderSize
		 0,						// diph.dwObj
		 DIPH_DEVICE,			// diph.dwHow
		 }
		,
		DINPUT_BUFFERSIZE,		// dwData
	};

#ifdef __GNUC__
	hResult = DirectInputCreate(g_wv.hInstance, DIRECTINPUT_VERSION, &g_pdi, NULL);
#else
	hResult = DirectInput8Create(g_wv.hInstance, DIRECTINPUT_VERSION, &IID_IDirectInput8A, &g_pdi, NULL);
#endif

	if(FAILED(hResult))
	{
#ifdef __GNUC__
		Com_Printf("DirectInput8Create failed\n");
#else
		Com_Printf("DirectInput8Create failed\n");
#endif
		return qfalse;
	}

	// obtain an interface to the system mouse device.
	hResult = IDirectInput_CreateDevice(g_pdi, &GUID_SysMouse, &g_pMouse, NULL);

	if(FAILED(hResult))
	{
		Com_Printf("Couldn't open DI mouse device\n");
		return qfalse;
	}

	// set the data format to "mouse format".
	hResult = IDirectInputDevice_SetDataFormat(g_pMouse, &df);

	if(FAILED(hResult))
	{
		Com_Printf("Couldn't set DI mouse format\n");
		return qfalse;
	}

	// set the DirectInput cooperativity level.
	hResult = IDirectInputDevice_SetCooperativeLevel(g_pMouse, g_wv.hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

	if(FAILED(hResult))
	{
		Com_Printf("Couldn't set DI coop level\n");
		return qfalse;
	}


	// set the buffer size to DINPUT_BUFFERSIZE elements.
	// the buffer size is a DWORD property associated with the device
	hResult = IDirectInputDevice_SetProperty(g_pMouse, DIPROP_BUFFERSIZE, &dipdw.diph);

	if(FAILED(hResult))
	{
		Com_Printf("Couldn't set DI buffersize\n");
		return qfalse;
	}

	return qtrue;
}