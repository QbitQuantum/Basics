// Open multimedia stream.
BOOL CDShow::Open(ZString& pFileName, IDirectDraw7 *pDD)
{
	// Multimedia stream pointer
	IAMMultiMediaStream *pAMStream;
	IGraphBuilder *pGb; // 7/10 #110
	IEnumFilters *pEfs;
	IBasicAudio *pBa;

    
	//7/29/09 we can now do stuff while the video plays
	CoInitializeEx(NULL,COINIT_MULTITHREADED); 
	

    // Create Multimedia stream object
	if (FAILED(CoCreateInstance(CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER,
				 IID_IAMMultiMediaStream, (void **)&pAMStream)))
	{		
		// Return FALSE to let caller know we failed.	
		return FALSE; 
	}
    
	// Initialize Multimedia stream object
	if (FAILED(pAMStream->Initialize(STREAMTYPE_READ, 0, NULL)))
	{	
		// There are alot of possiblities to fail.....		
		return FALSE; 
	}

    // Add primary video stream.
	if (FAILED((pAMStream->AddMediaStream(pDD, &MSPID_PrimaryVideo, 0, NULL))))
	{		
		return FALSE; 
	}

    // Add default sound render to primary video stream,
	// so sound will be played back automatically.
	if (FAILED(pAMStream->AddMediaStream(NULL, &MSPID_PrimaryAudio, AMMSF_ADDDEFAULTRENDERER, NULL)))
	{
		// Return FALSE to let caller know we failed.		
		return FALSE; 
	}

    // Convert filename to UNICODE.
	// Notice the safe way to get the actual size of a string.
	WCHAR wPath[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, pFileName, -1, wPath, sizeof(wPath)/sizeof(wPath[0]));   
    
	// Build the filter graph for our multimedia stream.
	if (FAILED((pAMStream->OpenFile(wPath, 0))))
	{	
		// Return FALSE to let caller know we failed.		
		return FALSE; 
	}

	//7/10 #110
	FILTER_INFO FilterInfo;
	pAMStream->GetFilterGraph(&pGb);
	pGb->EnumFilters(&pEfs);

    IBaseFilter *pFilter;
	unsigned long cFetched;
    while(pEfs->Next(1, &pFilter, &cFetched) == S_OK) {
		FILTER_INFO FilterInfo;
		pFilter->QueryFilterInfo(&FilterInfo);
		char szName[MAX_FILTER_NAME];
		long cch = WideCharToMultiByte(CP_ACP,0,FilterInfo.achName,MAX_FILTER_NAME,szName,MAX_FILTER_NAME,0,0);
		if (cch > 0) {
			if (!strcmp("WMAudio Decoder DMO",szName)) {
				// set the volume to music level
				FilterInfo.pGraph->QueryInterface(IID_IBasicAudio,(void**)&pBa);
				HKEY hKey;
				DWORD dwResult = 0;
				if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, ALLEGIANCE_REGISTRY_KEY_ROOT,0, KEY_READ, &hKey)) {
					DWORD dwSize = sizeof(dwResult);
					DWORD dwType = REG_DWORD;
					::RegQueryValueEx(hKey, "MusicGain", NULL, &dwType, (BYTE*)&dwResult, &dwSize);
					::RegCloseKey(hKey);
					if (dwType != REG_DWORD)
						dwResult = 0;
				}
				long vol = (dwResult * -1) * 100;
				if (vol < -5000) {
					vol = -10000;
				}
				pBa->put_Volume(vol);
				pBa->Release();
			}
           if (FilterInfo.pGraph != NULL)
               FilterInfo.pGraph->Release();
           pFilter->Release();
		}
	}
	pEfs->Release();
	pGb->Release();

    // Assign member to temperary stream pointer.
	m_pMMStream = pAMStream;
	
	// Add a reference to the file
	pAMStream->AddRef();
    	
	// Get media stream interface
	if (FAILED(m_pMMStream->GetMediaStream(MSPID_PrimaryVideo, &m_pPrimaryVideoStream)))
	{	
		return FALSE;
	}
	
	// Get DirectDraw media stream interface
	if (FAILED(m_pPrimaryVideoStream->QueryInterface(IID_IDirectDrawMediaStream,(void **)&m_pDDStream)))
	{				
		return FALSE;
	}	
	
	// Create stream sample
	if (FAILED(m_pDDStream->CreateSample(NULL,NULL,0,&m_pSample)))
	{			
		return FALSE;
	}	
	
	// Get DirectDraw surface interface from Sample.
	if (FAILED(m_pSample->GetSurface(&m_pDDSurface,&m_rSrcRect)))
	{			

		return FALSE;
	}	
	
	// Get DirectDraw surface7 interface
	if (FAILED(m_pDDSurface->QueryInterface(IID_IDirectDrawSurface7,(void**)&m_pDDSurface7)))
	{		
		return FALSE;
	}	
	
	// Ok. Media is open now.
	m_bMediaOpen=TRUE;
	
	// If we are here, everything turned out ok. Return TRUE.
	return TRUE;
}