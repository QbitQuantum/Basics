BOOL WINAPI DDEnumDevCallback(GUID FAR *lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext, HMONITOR hm)
{
	LPDIRECTDRAW ddp;
	LPDIRECTDRAW4 dd4p;
	DDDEVICEIDENTIFIER ddDev;
	BOOL ret = FALSE;

	if (DirectDrawCreate(lpGUID,&ddp,0) == DD_OK)
	{
		if(ddp->QueryInterface(IID_IDirectDraw4,(void **)&dd4p) == S_OK)
		{
			ZeroMemory(&ddDev,sizeof(ddDev));
			if(GetDeviceIdentifierEx(dd4p,&ddDev, DDGDI_GETHOSTIDENTIFIER) == DD_OK)
			{
				// add to table
				USES_CONVERSION;
				CUtilGPU::AddDisplayDevice(A2CT(lpDriverName), ddDev.dwVendorId, ddDev.dwDeviceId, ddDev.szDescription, ddDev.szDriver);
				ret = TRUE;
			}
			dd4p->Release();
		}
		ddp->Release();
	}

	return ret;
}