UINT8 DSound_Init(void)
{
	HRESULT retVal;
	UINT32 curDev;
	
	if (isInit)
		return AERR_WASDONE;
	
	devLstAlloc = 0;
	devLstCount = 0;
	devList = NULL;
	retVal = DirectSoundEnumerateA(&DSEnumCallback, NULL);
	if (retVal != DS_OK)
		return AERR_API_ERR;
	
	deviceList.devNames = (char**)malloc(sizeof(char*) * devLstCount);
	for (curDev = 0; curDev < devLstCount; curDev ++)
		deviceList.devNames[curDev] = devList[curDev].devName;
	deviceList.devCount = curDev;
	
	
	memset(&defOptions, 0x00, sizeof(AUDIO_OPTS));
	defOptions.sampleRate = 44100;
	defOptions.numChannels = 2;
	defOptions.numBitsPerSmpl = 16;
	defOptions.usecPerBuf = 10000;	// 10 ms per buffer
	defOptions.numBuffers = 10;	// 100 ms latency
	
	
	activeDrivers = 0;
	isInit = 1;
	
	return AERR_OK;
}