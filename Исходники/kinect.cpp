HRESULT
KinectImpl::initAudio(){
  HRESULT hr = S_OK;

  // Set high priority to avoid getting preempted while capturing sound
#if 1
  DWORD m_TaskIndex=0;
  h_TaskIndex = AvSetMmThreadCharacteristicsW(L"Audio", &m_TaskIndex);

  if (h_TaskIndex == NULL) {
    hr = E_FAIL;
	puts("Failed to set thread priority\n");
	return hr;
  }
#endif

  // DMO initialization
  INuiAudioBeam* pAudio;
  hr = m_pNuiSensor->NuiGetAudioSource(&pAudio);
  if (FAILED(hr)) {
    puts("Failed to NuiGetAudioSource\n");
	return hr;
  }
 
  hr = pAudio->QueryInterface(IID_IMediaObject, (void**)&pMediaObject);
  if (FAILED(hr)) {
    puts("Fail to call pAudio->QueryInterface(pMediaObject)\n");
	return hr;
  }

  hr = pAudio->QueryInterface(IID_IPropertyStore, (void**)&pPropertyStore);
  if (FAILED(hr)) {
    puts("Fail to call pAudio->QueryInterface(pPropertyStore)\n");
    return hr;
  }
  pAudio->Release();

  // Set AEC-MicArray DMO system mode.
  // This must be set for the DMO to work properly
  PROPVARIANT pvSysMode;
  PropVariantInit(&pvSysMode);
  pvSysMode.vt = VT_I4;
  pvSysMode.lVal = (LONG)(4);
  hr = pPropertyStore->SetValue(MFPKEY_WMAAECMA_SYSTEM_MODE, pvSysMode);
  if (FAILED(hr)) {
    puts("Fail to call pPS->SetValue\n");
    return hr;
  }
  PropVariantClear(&pvSysMode);

  // NOTE: Need to wait 4 seconds for device to be ready right after initialization
 
  DWORD dwWait = 4;
  while (dwWait > 0){
    _tprintf(_T("Device will be ready for recording in %d second(s).\r"), dwWait--);
    Sleep(1000);
  }
  _tprintf(_T("Device is ready.                                                  \n"));

  /*** set output buffer ***/
  memset(&OutputBufferStruct,0, sizeof(OutputBufferStruct));
  OutputBufferStruct.pBuffer = &outputBuffer;

  // Set DMO output format  
  WAVEFORMATEX wfxOut = {WAVE_FORMAT_PCM, 1, 16000, 32000, 2, 16, 0};
  DMO_MEDIA_TYPE mt = {0};

  hr = MoInitMediaType(&mt, sizeof(WAVEFORMATEX));
  if (FAILED(hr)) {
    puts("MoInitMediaType failed\n");
    return hr;
  }
    
  mt.majortype = MEDIATYPE_Audio;
  mt.subtype = MEDIASUBTYPE_PCM;
  mt.lSampleSize = 0;
  mt.bFixedSizeSamples = TRUE;
  mt.bTemporalCompression = FALSE;
  mt.formattype = FORMAT_WaveFormatEx;	
  memcpy(mt.pbFormat, &wfxOut, sizeof(WAVEFORMATEX));
    
  hr = pMediaObject->SetOutputType(0, &mt, 0); 
  if (FAILED(hr)) {
    puts("SetOutputType failed\n");
    return hr;
  }
  MoFreeMediaType(&mt);

  hr = pMediaObject->AllocateStreamingResources();
  if (FAILED(hr)) {
    puts("AllocateStreamingResources failed\n");
    return hr;
  }


  int iFrameSize;
  PROPVARIANT pvFrameSize;
  PropVariantInit(&pvFrameSize);
  hr = pPropertyStore->GetValue(MFPKEY_WMAAECMA_FEATR_FRAME_SIZE, &pvFrameSize);
  if (FAILED(hr)) {
    puts("Fail to call pPS->GetValue\n");
    return hr;
  }
  iFrameSize = pvFrameSize.lVal;
  PropVariantClear(&pvFrameSize);

  // allocate output buffer
  DWORD cOutputBufLen = wfxOut.nSamplesPerSec * wfxOut.nBlockAlign;
  pbOutputBuffer = new BYTE[cOutputBufLen];

  if (pbOutputBuffer == NULL) {
    puts("Fail to allocate output buffer.\n");
	return hr;
  }
  
  //  
  hr = pMediaObject->QueryInterface(IID_INuiAudioBeam, (void**)&pAudioBeam);
  if (FAILED(hr)) {
    puts("QueryInterface for IID_INuiAudioBeam failed\n");
    return hr;
  }

  outputBuffer.Init((byte*)pbOutputBuffer, cOutputBufLen, 0);

  return S_OK;
}