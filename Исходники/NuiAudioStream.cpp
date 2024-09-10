/// <summary>
/// Start processing stream
/// </summary>
/// <returns>Indicates success or failure</returns>
HRESULT NuiAudioStream::StartStream()
{
    // Get audio source interface
    HRESULT hr = m_pNuiSensor->NuiGetAudioSource(&m_pNuiAudioSource);
    if (FAILED(hr))
    {
        return hr;
    }

    // Query dmo interface
    hr = m_pNuiAudioSource->QueryInterface(IID_IMediaObject, (void**)&m_pDMO);
    if (FAILED(hr))
    {
        return hr;
    }

    // Query property store interface
    hr = m_pNuiAudioSource->QueryInterface(IID_IPropertyStore, (void**)&m_pPropertyStore);
    if (FAILED(hr))
    {
        return hr;
    }

    // Set AEC-MicArray DMO system mode. This must be set for the DMO to work properly.
    // Possible values are:
    //   SINGLE_CHANNEL_AEC = 0
    //   OPTIBEAM_ARRAY_ONLY = 2
    //   OPTIBEAM_ARRAY_AND_AEC = 4
    //   SINGLE_CHANNEL_NSAGC = 5

    PROPVARIANT pvSysMode;

    // Initialize the variable
    PropVariantInit(&pvSysMode);

    // Assign properties
    pvSysMode.vt   = VT_I4;
    pvSysMode.lVal = (LONG)(2); // Use OPTIBEAM_ARRAY_ONLY setting. Set OPTIBEAM_ARRAY_AND_AEC instead if you expect to have sound playing from speakers.

    // Set properties
    m_pPropertyStore->SetValue(MFPKEY_WMAAECMA_SYSTEM_MODE, pvSysMode);

    // Release the variable
    PropVariantClear(&pvSysMode);

    // Set DMO output format
    WAVEFORMATEX   wfxOut = {AudioFormat, AudioChannels, AudioSamplesPerSecond, AudioAverageBytesPerSecond, AudioBlockAlign, AudioBitsPerSample, 0};
	memcpy_s(&m_wfxOut,sizeof(WAVEFORMATEX),&wfxOut,sizeof(WAVEFORMATEX));

    DMO_MEDIA_TYPE mt     = {0};

    // Initialize variable
    MoInitMediaType(&mt, sizeof(WAVEFORMATEX));

    // Assign format
    mt.majortype            = MEDIATYPE_Audio;
    mt.subtype              = MEDIASUBTYPE_PCM;
    mt.lSampleSize          = 0;
    mt.bFixedSizeSamples    = TRUE;
    mt.bTemporalCompression = FALSE;
    mt.formattype           = FORMAT_WaveFormatEx;	

    memcpy_s(mt.pbFormat, sizeof(WAVEFORMATEX), &m_wfxOut, sizeof(WAVEFORMATEX));

    // Set format
    hr = m_pDMO->SetOutputType(0, &mt, 0); 

    // Release variable
    MoFreeMediaType(&mt);

    return hr;
}