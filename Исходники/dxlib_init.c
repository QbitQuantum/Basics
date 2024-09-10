int DxLib_Init()
{
	if(dxpGeneralData.initialized)return 0;

	if(dxpMutexInit() < 0)return -1;
	if(dxpMemoryInit() < 0)return -1;
	if(!dxpGeneralData.homebutton_callback_initialized)
	{
		dxpGeneralData.homebutton_callback_threadid = SetExitCallback();
		dxpGeneralData.homebutton_callback_initialized = 1;
	}
	dxpInputInit();
    if(dxpFileioInit() < 0)return -1;
	if(dxpGraphicsInit() < 0)return -1;
	if(dxpSoundInit() < 0)return -1;

	SRand(time(NULL));
	
	dxpGeneralData.initialized = 1;
	return 0;
	/*
err:
	return -1;
	*/
}