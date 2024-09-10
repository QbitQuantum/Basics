static vmResult	win32ddraw_init(void)
{
	LPDIRECTDRAW	oldDraw;
	int ret;

	int	x;
	
	if (!win_registerDirectDrawWindowClass(myHInst, myHPreInst) ||
		!win_createDirectDrawWindows(myHInst, mynCmdShow))
		return vmInternalError;

//	log("init\n");

	for (x=0; x<16; x++)
		win_rgbmap[x]=x;
	win_rgbmap[16] = 15;

	/*	DirectDraw initialization */
	ret = DirectDrawCreate((GUID *)NULL, &oldDraw, NULL);
	if (ret != DD_OK)
		DDFAIL("DirectDrawCreate", ret);

	if (!SUCCEEDED(oldDraw->QueryInterface(IID_IDirectDraw2,
		        reinterpret_cast<void**>(&lpDD))))
		DDFAIL("QueryInterface", -1);

// --
		
	features|=FE_SHOWVIDEO|FE_VIDEO;
	
	return vmOk;
}