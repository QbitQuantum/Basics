//************************************************************************************
// DriverEnumCallback()
// Callback function for enumerating drivers.
//************************************************************************************
static BOOL WINAPI DriverEnumCallback(GUID * pGUID, TCHAR * strDesc,
                                      TCHAR * strName, VOID *, HMONITOR)
{
	D3DEnum_DeviceInfo d3dDeviceInfo;
	LPDIRECTDRAW7      pDD;
	LPDIRECT3D7        pD3D;
	HRESULT            hr;

	// Use the GUID to create the DirectDraw object
	hr = DirectDrawCreateEx(pGUID, (VOID **)&pDD, IID_IDirectDraw7, NULL);

	if (FAILED(hr))
	{
		DEBUG_MSG(_T("Can't create DDraw during enumeration!"));
		return D3DENUMRET_OK;
	}

	// Create a D3D object, to enumerate the d3d devices
	hr = pDD->QueryInterface(IID_IDirect3D7, (VOID **)&pD3D);

	if (FAILED(hr))
	{
		pDD->Release();
		DEBUG_MSG(_T("Can't query IDirect3D7 during enumeration!"));
		return D3DENUMRET_OK;
	}

	// Copy data to a device info structure
	ZeroMemory(&d3dDeviceInfo, sizeof(d3dDeviceInfo));
	lstrcpyn(d3dDeviceInfo.strDesc, strDesc, 39);
	d3dDeviceInfo.ddDriverCaps.dwSize = sizeof(DDCAPS);
	d3dDeviceInfo.ddHELCaps.dwSize    = sizeof(DDCAPS);
	pDD->GetCaps(&d3dDeviceInfo.ddDriverCaps, &d3dDeviceInfo.ddHELCaps);

	if (pGUID)
	{
		d3dDeviceInfo.guidDriver = (*pGUID);
		d3dDeviceInfo.pDriverGUID = &d3dDeviceInfo.guidDriver;
	}

	// Record whether the device can render into a desktop window
	if (d3dDeviceInfo.ddDriverCaps.dwCaps2 & DDCAPS2_CANRENDERWINDOWED)
		if (NULL == d3dDeviceInfo.pDriverGUID)
			d3dDeviceInfo.bDesktopCompatible = TRUE;

	// Enumerate the fullscreen display modes.
	pDD->EnumDisplayModes(0, NULL, &d3dDeviceInfo, ModeEnumCallback);

	// Sort list of display modes
	qsort(d3dDeviceInfo.pddsdModes, d3dDeviceInfo.dwNumModes,
	      sizeof(DDSURFACEDESC2), SortModesCallback);

	// Now, enumerate all the 3D devices
	pD3D->EnumDevices(DeviceEnumCallback, &d3dDeviceInfo);

	// Clean up and return
	SAFE_DELETE(d3dDeviceInfo.pddsdModes);
	pD3D->Release();
	pDD->Release();

	return DDENUMRET_OK;
}