bool CSoundComponent::InitXACT(const char* engine_xgs)
{
	HRESULT hr;
	CoInitializeEx( NULL, COINIT_MULTITHREADED );  // COINIT_APARTMENTTHREADED will work too
	//TODO("Create the XACT engine");
	hr=XACT3CreateEngine(0, &mpXEngine);

	if( FAILED( hr ) || mpXEngine == NULL )
	{
		FAIL("Problems creating XACT engine","InitXACT Failed");
		return false;
	}

	// Load the global settings file and pass it into XACTInitialize
	VOID* pGlobalSettingsData = NULL;
	DWORD dwGlobalSettingsFileSize = 0;
	bool bSuccess = false;
	HANDLE hFile = CreateFile( engine_xgs, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if( hFile!=INVALID_HANDLE_VALUE )
	{
		dwGlobalSettingsFileSize = GetFileSize( hFile, NULL );
		if( dwGlobalSettingsFileSize != INVALID_FILE_SIZE )
		{
			pGlobalSettingsData = CoTaskMemAlloc( dwGlobalSettingsFileSize );
			if( pGlobalSettingsData )
			{
				DWORD dwBytesRead;
				if( 0 != ReadFile( hFile, pGlobalSettingsData, dwGlobalSettingsFileSize, &dwBytesRead, NULL ) )
				{
					bSuccess = true;
				}
			}
		}
		CloseHandle( hFile );
	}
	if( !bSuccess )
	{
		if( pGlobalSettingsData )
			CoTaskMemFree( pGlobalSettingsData );
		pGlobalSettingsData = NULL;
		dwGlobalSettingsFileSize = 0;
		FAIL(engine_xgs,"Problems opening engine file");
		return false;
	}

	// Initialize & create the XACT runtime 
	XACT_RUNTIME_PARAMETERS xrParams = {0};
	xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	xrParams.pGlobalSettingsBuffer = pGlobalSettingsData;
	xrParams.globalSettingsBufferSize = dwGlobalSettingsFileSize;
	xrParams.globalSettingsFlags = XACT_FLAG_GLOBAL_SETTINGS_MANAGEDATA; // this will tell XACT to delete[] the buffer when its unneeded
	//TODO(Initalise the XACT engine);
	hr=mpXEngine->Initialize(&xrParams);
	if( FAILED( hr ) )
	{
		FAIL(engine_xgs,"Problems Initalising XACT engine");
		return false;
	}

	X3DAUDIO_EMITTER emitter = {0};
	X3DAUDIO_LISTENER listener = {0};

	listener.OrientFront = D3DXVECTOR3( 0, 0, 1 );
	listener.OrientTop = D3DXVECTOR3( 0, 1, 0 );
	listener.Position = D3DXVECTOR3( 0, 0, 0 );
	listener.Velocity = D3DXVECTOR3( 0, 0, 0 );

	// the following need to be orthonormal
	emitter.OrientFront = D3DXVECTOR3( 0, 0, 1 );
	emitter.OrientTop = D3DXVECTOR3( 0, 1, 0 );
	emitter.Position = D3DXVECTOR3( 0, 0, 0 );
	emitter.Velocity = D3DXVECTOR3( 0, 0, 0 ); // needs to not be zero if you want to hear Doppler effect

	// emitter ChannelCount and DSP Setting's SrcChannelCount must match
	emitter.ChannelCount = 2;   

	// this will be set by XACT3DCalculate if ChannelCount > 1.
	emitter.ChannelRadius = 1.0f;   

	// will be set by XACT3DCalculate
	emitter.pChannelAzimuths = NULL;

	// will be set by XACT3DCalculate
	emitter.pVolumeCurve = emitter.pLFECurve
		= emitter.pLPFDirectCurve
		= emitter.pLPFReverbCurve
		= emitter.pReverbCurve
		= NULL;

	emitter.CurveDistanceScaler = 1.0;
	emitter.DopplerScaler = 1.0f;

	hr = XACT3DInitialize(mpXEngine, xact3dInstance);

	if( FAILED( hr ) )
	{
		FAIL(engine_xgs,"Problems Initalising XACT 3D engine");
		return false;
	}

	// check how many output channels are supported
	WAVEFORMATEXTENSIBLE format;
	hr = mpXEngine->GetFinalMixFormat(&format);
	if(FAILED(hr))
	{
		FAIL("BLABLBA");
	}
	// fill the DSP
	ZeroMemory(&dspSettings,sizeof(dspSettings));
	// different code's seem to suggest 1 or 2 channels for the emitter
	dspSettings.SrcChannelCount = 1;
	dspSettings.DstChannelCount = format.Format.nChannels;  // as supported 
	dspSettings.pMatrixCoefficients = new FLOAT32[dspSettings.SrcChannelCount * dspSettings.DstChannelCount];
	ZeroMemory(dspSettings.pMatrixCoefficients ,sizeof(FLOAT32)*dspSettings.SrcChannelCount * dspSettings.DstChannelCount);

	return true;
}