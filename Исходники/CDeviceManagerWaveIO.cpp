CDeviceManagerWaveIO::CDeviceManagerWaveIO()
{
	muiNbOfDrivers_Outputs = waveOutGetNumDevs();
	tuint32 ui;
	for (ui = 0; ui<muiNbOfDrivers_Outputs; ui++) {
		UINT uiDevID = ui;
		SMyWaveOutCaps* p = new SMyWaveOutCaps();
		MMRESULT mmres = waveOutGetDevCaps((UINT_PTR)uiDevID, &(p->wocaps), sizeof(WAVEOUTCAPS));
		if (mmres == MMSYSERR_NOERROR) {
			if (p->wocaps.dwFormats & WAVE_FORMAT_4S16)
				p->b44100 = TRUE;
			p->b48000 = CDeviceWaveIO::TestWaveOutCaps(&uiDevID, 48000);
			p->b88200 = CDeviceWaveIO::TestWaveOutCaps(&uiDevID, 88200);
			if (p->wocaps.dwFormats & WAVE_FORMAT_96S16)
				p->b96000 = TRUE;
#ifdef _DEBUG
			tchar pszDevName[1024];
			strcpy(pszDevName, p->wocaps.szPname);
			WORD wChannels = p->wocaps.wChannels;
			std::cout << "CDeviceManagerWaveIO::CDeviceManagerWaveIO() - Add device " << uiDevID << " = '" << pszDevName << "', " << wChannels << " channels.\n";
#endif _DEBUG
		}
		else {
			std::cerr << "CDeviceManagerWaveIO::CDeviceManagerWaveIO() - Unable to add device " << uiDevID << ".\n";
		}
		mlistpMyWaveOutCaps.insert(mlistpMyWaveOutCaps.end(), p);
	}

	muiNbOfDrivers_Total = muiNbOfDrivers_Outputs + waveInGetNumDevs();
	for (ui = muiNbOfDrivers_Outputs; ui < muiNbOfDrivers_Total; ui++) {
		UINT uiDevID = ui - muiNbOfDrivers_Outputs;
		SWaveInCaps* p = new SWaveInCaps();
		MMRESULT mmres = waveInGetDevCaps((UINT_PTR)uiDevID, &(p->wicaps), sizeof(WAVEINCAPS));
		if (mmres == MMSYSERR_NOERROR) {
#ifdef _DEBUG
			tchar pszDevName[1024];
			strcpy(pszDevName, p->wicaps.szPname);
			WORD wChannels = p->wicaps.wChannels;
			std::cout << "CDeviceManagerWaveIO::CDeviceManagerWaveIO() - Add device " << uiDevID << " = '" << pszDevName << "', " << wChannels << " channels.\n";
#endif _DEBUG
		}
		else {
			std::cerr << "CDeviceManagerWaveIO::CDeviceManagerWaveIO() - Unable to add device " << uiDevID << ".\n";
		}
		mWaveInCaps.push_back(p);
	}
} // constructor