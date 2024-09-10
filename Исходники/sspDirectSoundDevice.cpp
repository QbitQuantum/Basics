// initialize
bool sspDSDeviceGroup::initializeImpl(LPVOID hWnd)
{
	if (m_pDS.size() > 0) return TRUE;	// Already initialized

    if (hWnd == NULL)
    {
        // Error, invalid hwnd
        DOUT (_T("ERROR: Invalid parameters, unable to initialize services\n\r"));
        return FALSE;
    }
	m_hApp = (HWND) hWnd;
    setBufferFormat(2);
	m_pDS.reserve(m_nDevices.size());
	m_pDSBuf.reserve(m_nDevices.size());
	for (unsigned int i=0; i<m_nDevices.size(); i++) {
		// Create DirectSound object
		LPDIRECTSOUND ds;
		HRESULT nResult = DirectSoundCreate(m_dsInfo[m_nDevices[i]]->lpGuid, &ds, NULL);
		if (nResult == DS_OK) {
			nResult = ds->SetCooperativeLevel(m_hApp, DSSCL_PRIORITY);
			if (nResult == DS_OK) {
				LPDIRECTSOUNDBUFFER dsbuf;
				nResult = ds->CreateSoundBuffer(&m_dsBufDesc, &dsbuf, NULL);
				if (nResult == DS_OK) {
					nResult = dsbuf->SetFormat(&m_pcmWf);
					if (nResult == DS_OK) {
						DOUT (_T("SUCCESS: DirectSound created and formatted\n\r"));
					}
					else {
						DOUT(_T("ERROR: Unable to set DirectSound format\n\r"));
						return FALSE;
					}
				m_pDSBuf.push_back(dsbuf);
				}
				else {
					DOUT(_T("ERROR: Unable to create DirectSound buffer\n\r"));
					return FALSE;
				}
			}
			else {
				DOUT(_T("ERROR: Unable to set DirectSound cooperative level\n\r"));
				return FALSE;
			}
			m_pDS.push_back(ds);
		}
		else {
			// Error
			DOUT(_T("ERROR: Unable to create DirectSound object\n\r"));
			return FALSE;
		}
	}
    return TRUE;
}