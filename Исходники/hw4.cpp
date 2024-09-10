HRESULT DemoApp::Initialize()
{
    HRESULT hr;

    //register window class
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = DemoApp::WndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = sizeof(LONG_PTR);
    wcex.hInstance     = HINST_THISCOMPONENT;
    wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName  = NULL;
    wcex.lpszClassName = L"App";

    RegisterClassEx(&wcex);

    hr = CreateDeviceIndependentResources();
    if (SUCCEEDED(hr))
    {
        // Create the application window.
        m_hwnd = CreateWindow(
            L"App",
            L"달걀 채색 공장(201001622 이진용)",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            1200,
			600,
            NULL,
            NULL,
            HINST_THISCOMPONENT,
            this
            );
        hr = m_hwnd ? S_OK : E_FAIL;

        if (SUCCEEDED(hr))
        {
            float length = 0;
            hr = m_wheelPath->ComputeLength(
                NULL, //no transform
                &length
                );

            if (SUCCEEDED(hr) )
            {
                m_Animation.SetStart(0);        //start at beginning of path
                m_Animation.SetEnd(length);     //length at end of path
                m_Animation.SetDuration(5.f );  //seconds

                ZeroMemory(&m_DwmTimingInfo, sizeof(m_DwmTimingInfo));
                m_DwmTimingInfo.cbSize = sizeof(m_DwmTimingInfo);

                // Get the composition refresh rate. If the DWM isn't running,
                // get the refresh rate from GDI -- probably going to be 60Hz
                if (FAILED(DwmGetCompositionTimingInfo(NULL, &m_DwmTimingInfo)))
                {
                    HDC hdc = GetDC(m_hwnd);
                    m_DwmTimingInfo.rateCompose.uiDenominator = 1;
                    m_DwmTimingInfo.rateCompose.uiNumerator = GetDeviceCaps(hdc, VREFRESH);
                    ReleaseDC(m_hwnd, hdc);
                }

                ShowWindow(m_hwnd, SW_SHOWNORMAL);

                UpdateWindow(m_hwnd);
            }
        }



		if (SUCCEEDED(hr))
        {
            float pLength = 0;
			hr = m_flyPath->ComputeLength(
                NULL, //no transform
                &pLength
                );

            if (SUCCEEDED(hr) )
            {
                m_linearAnimation.SetStart(0);        //start at beginning of path
                m_linearAnimation.SetEnd(pLength);     //length at end of path
                m_linearAnimation.SetDuration(10.f);  //seconds

                ZeroMemory(&m_DwmTimingInfo, sizeof(m_DwmTimingInfo));
                m_DwmTimingInfo.cbSize = sizeof(m_DwmTimingInfo);

                // Get the composition refresh rate. If the DWM isn't running,
                // get the refresh rate from GDI -- probably going to be 60Hz
                if (FAILED(DwmGetCompositionTimingInfo(NULL, &m_DwmTimingInfo)))
                {
                    HDC hdc = GetDC(m_hwnd);
                    m_DwmTimingInfo.rateCompose.uiDenominator = 1;
                    m_DwmTimingInfo.rateCompose.uiNumerator = GetDeviceCaps(hdc, VREFRESH);
                    ReleaseDC(m_hwnd, hdc);
                }

                ShowWindow(m_hwnd, SW_SHOWNORMAL);

                UpdateWindow(m_hwnd);
            }
        }
    }

	
	//장치 객체 생성
	IDirectSound8* directSound;
	DirectSoundCreate8(NULL,&directSound, NULL);

	
	//협력레벨 지정
	directSound->SetCooperativeLevel(m_hwnd,DSSCL_PRIORITY);

	//주버퍼 포맷 지정
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd,sizeof(DSBUFFERDESC) );
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = NULL;
	

	//IDirectSoundBuffer* pDSBPrimary = NULL;
	directSound->CreateSoundBuffer(&dsbd, &pDSBPrimary, NULL);
	
	WAVEFORMATEX wfx;
	ZeroMemory(&wfx, sizeof(WAVEFORMATEX) );
	wfx.wFormatTag = (WORD)WAVE_FORMAT_PCM;
	wfx.nChannels =(WORD)2;
	wfx.nSamplesPerSec = (DWORD)22050;
	wfx.wBitsPerSample = (WORD)16;
	wfx.nBlockAlign = (WORD)(wfx.wBitsPerSample / 8 * wfx.nChannels );
	wfx.nAvgBytesPerSec = (DWORD)(wfx.nSamplesPerSec * wfx.nBlockAlign );

	pDSBPrimary->SetFormat(&wfx);

	pDSBPrimary->Release();

	//2차 버퍼 생성  BGM
	CWaveFile* pWaveFile = NULL;
	pWaveFile = new CWaveFile();
	pWaveFile->Open( L".\\pokemonCenter.wav", NULL, WAVEFILE_READ );
	
	
	//DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC) );
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLVOLUME;
	dsbd.guid3DAlgorithm = GUID_NULL;
	dsbd.lpwfxFormat = pWaveFile->m_pwfx;
	dsbd.dwBufferBytes = pWaveFile->GetSize();
	

	
	directSound->CreateSoundBuffer(&dsbd, &pDSBuffer, NULL);



	//이차버퍼에 데이터 채우기
	sound = new CSound(&pDSBuffer, dsbd.dwBufferBytes, 1 , pWaveFile, 0 );  // pDSBuffer 위에 전역변수임


	pDSBPrimary->SetVolume(scaledVolume);

	sound->Play(0,DSBPLAY_LOOPING);
	


	soundManager = new CSoundManager;
	if( ! soundManager->init(m_hwnd) )
		return FALSE;

	int id;
	if (! soundManager->add(L".\\boss.wav", &id)) //id=0부터 시작함.
		return FALSE;
	if (! soundManager->add(L".\\storm.wav",&id));




    return hr;
}