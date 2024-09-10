Err GE2DLibOpen()
{
	DDSURFACEDESC Desc;

	HRESULT (WINAPI* DirectDrawCreate)( void*, LPDIRECTDRAW*, void* );
	Module = LoadLibrary(T("DDRAW.DLL"));
	*(FARPROC*)&DirectDrawCreate = GetProcAddress(Module,"DirectDrawCreate");

	if (!DirectDrawCreate)
		return 1;

	if (DirectDrawCreate(NULL,&DD,NULL)!=DD_OK)
		return 1;

	IDirectDraw_SetCooperativeLevel(DD, NULL, DDSCL_NORMAL);

	// get primary surface
	memset(&Desc,0,sizeof(DDSURFACEDESC));
	Desc.dwSize = sizeof(DDSURFACEDESC);
	Desc.dwFlags = DDSD_CAPS;
	Desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	if (IDirectDraw_CreateSurface(DD,&Desc,&DDPrimary,NULL) != DD_OK)
		return 1;

	return errNone;
}