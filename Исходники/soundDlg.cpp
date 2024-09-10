BOOL CSoundDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	ant_k_freq = _k_freq = 1;
	m_freq.SetRange(0,100);
	m_freq.SetPos(100-_k_freq*50);

	_volumen = 1;
	_left = 0.5;
	_right = 0.5;
	m_vol.SetRange(0,100);
	m_vol.SetPos((1-_volumen)*100);
	m_left.SetRange(0,100);
	m_left.SetPos((1-_left)*100);
	m_right.SetRange(0,100);
	m_right.SetPos((1-_right)*100);



	// Cargo el wav que voy a usar de muestreo
	char wav = QUE_WAV;
	switch(wav)
	{
		case 0:
			_cant_samples = generateWav("jet.wav",&_pcm);
			break;
		case 1:
			_cant_samples = generateWav("engine1.wav",&_pcm);
			break;
		case 2:
			_cant_samples = generateWav("spaceship.wav",&_pcm)*0.5;
			break;
	}
			

	_index = 0;
	WAVEFORMATEX   Format; 
	Format.cbSize = sizeof(WAVEFORMATEX);
	Format.wFormatTag = WAVE_FORMAT_PCM;
	Format.nChannels = 2;
	Format.nSamplesPerSec = SAMPLE_RATE;
	Format.wBitsPerSample = 16;
	Format.nBlockAlign = 4;
	Format.nAvgBytesPerSec = Format.nSamplesPerSec*Format.nBlockAlign;

	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &Format, (DWORD)GetSafeHwnd() , 
			0L,CALLBACK_WINDOW)!=MMSYSERR_NOERROR)
	{       
		return TRUE;
	}


	QueryPerformanceFrequency(&F);
	QueryPerformanceCounter(&T0);

	// Genereo el timer 
	SetTimer(999,lap=TIME_LAP,NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}