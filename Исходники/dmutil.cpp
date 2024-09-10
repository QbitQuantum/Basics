//-----------------------------------------------------------------------------
// Name: CMusicManager::CreateSegmentFromResource()
// Desc: 
//-----------------------------------------------------------------------------
HRESULT CMusicManager::CreateSegmentFromResource( CMusicSegment** ppSegment, 
                                                  TCHAR* strResource,
                                                  TCHAR* strResourceType,
                                                  BOOL bDownloadNow,
                                                  BOOL bIsMidiFile )
{
    HRESULT               hr;
    IDirectMusicSegment8* pSegment      = NULL;
    HRSRC                 hres          = NULL;
    void*                 pMem          = NULL;
    DWORD                 dwSize        = 0;
    DMUS_OBJECTDESC       objdesc;

    // Find the resource
    hres = FindResource( NULL,strResource,strResourceType );
    if( NULL == hres ) 
        return E_FAIL;

    // Load the resource
    pMem = (void*)LoadResource( NULL, hres );
    if( NULL == pMem ) 
        return E_FAIL;

    // Store the size of the resource
    dwSize = SizeofResource( NULL, hres ); 
    
    // Set up our object description 
    ZeroMemory(&objdesc,sizeof(DMUS_OBJECTDESC));
    objdesc.dwSize = sizeof(DMUS_OBJECTDESC);
    objdesc.dwValidData = DMUS_OBJ_MEMORY | DMUS_OBJ_CLASS;
    objdesc.guidClass = CLSID_DirectMusicSegment;
    objdesc.llMemLength =(LONGLONG)dwSize;
    objdesc.pbMemData = (BYTE*)pMem;
    
    if (FAILED ( hr = m_pLoader->GetObject( &objdesc,
                                            IID_IDirectMusicSegment8,
                                            (void**)&pSegment ) ) )
    {
        if( hr == DMUS_E_LOADER_FAILEDOPEN )
            return hr;
        return DXTRACE_ERR_MSGBOX( TEXT("LoadObjectFromFile"), hr );
    }

    *ppSegment = new CMusicSegment( m_pPerformance, m_pLoader, pSegment );
    if( NULL == *ppSegment )
        return E_OUTOFMEMORY;

    if( bIsMidiFile )
    {
        // Do this to make sure that the default General MIDI set 
        // is connected appropriately to the MIDI file and 
        // all instruments sound correct.                  
        if( FAILED( hr = pSegment->SetParam( GUID_StandardMIDIFile, 
                                             0xFFFFFFFF, 0, 0, NULL ) ) )
            return DXTRACE_ERR_MSGBOX( TEXT("SetParam"), hr );
    }

    if( bDownloadNow )
    {
        // The segment needs to be download first before playing.  
        // However, some apps may want to wait before calling this 
        // to because the download allocates memory for the 
        // instruments. The more instruments currently downloaded, 
        // the more memory is in use by the synthesizer.
        if( FAILED( hr = (*ppSegment)->Download() ) )
            return DXTRACE_ERR_MSGBOX( TEXT("Download"), hr );
    }

    return S_OK;
}