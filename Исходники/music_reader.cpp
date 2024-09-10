std::vector<std::vector<double>> ReadMusicFrequencyData(const WCHAR *sURL)
{
    //CComPtr<IMFByteStream> pStream;
    CComPtr<IMFMediaSink> pSink;
    CComPtr<IMFMediaSource> pSource;
    CComPtr<IMFTopology> pTopology;
	CComPtr<IWaveDataRecorder> waveRecord;
	HRESULT hr=0;
	hr=CWavRecord::CreateInstanse(&waveRecord);
    //hr = MFCreateFile(MF_ACCESSMODE_WRITE, MF_OPENMODE_DELETE_IF_EXIST, MF_FILEFLAGS_NONE, sOutputFile, &pStream);
    if (FAILED(hr))
    {
        wprintf(L"MFCreateFile failed!\n");
    }

    // Create the WavSink object.
    if (SUCCEEDED(hr))
    {
        hr = CreateWavSink(NULL,waveRecord, &pSink);
    }

    // Create the media source from the URL.
    if (SUCCEEDED(hr))
    {
        hr = CreateMediaSource(sURL, &pSource);
    }

    // Create the topology.
    if (SUCCEEDED(hr))
    {
        hr = CreateTopology(pSource, pSink, &pTopology);
    }

    // Run the media session.
    if (SUCCEEDED(hr))
    {
        hr = RunMediaSession(pTopology);
        if (FAILED(hr))
        {
            wprintf(L"RunMediaSession failed!\n");
        }
    }

    if (pSource)
    {
        pSource->Shutdown();
    }

	std::vector<std::vector<double>> data;
	if(waveRecord)
		waveRecord->PullOutData(&data);
    return data;
}