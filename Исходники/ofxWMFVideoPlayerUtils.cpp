HRESULT CPlayer::OpenMultipleURL(vector<const WCHAR *> &urls)
{

	if (m_state == OpenPending) return S_FALSE;
	IMFTopology *pTopology = NULL;
	IMFPresentationDescriptor* pSourcePD = NULL;


	//Some lolilol for the sequencer that's coming from the outerspace (see topoEdit src code)
	IMFMediaSource* spSrc = NULL;
	IMFPresentationDescriptor* spPD = NULL;
	IMFMediaSourceTopologyProvider* spSrcTopoProvider = NULL;

	HRESULT hr = S_OK;

	if (_previousTopoID != 0)
	{
		hr = m_pSequencerSource->DeleteTopology(_previousTopoID);
		_previousTopoID = 0;
	}

	SafeRelease(&m_pSequencerSource);

	if (!m_pSequencerSource)
	{
		CHECK_HR(hr = MFCreateSequencerSource(NULL, &m_pSequencerSource));

		CHECK_HR(hr = CreateSession());

		CHECK_HR(hr = m_pSequencerSource->QueryInterface(IID_PPV_ARGS(&m_pSource)));

	}

	int nUrl = urls.size();
	int nPresenters = v_EVRPresenters.size();

	for (int i = nPresenters; i < nUrl; i++)
	{
		EVRCustomPresenter* presenter = new EVRCustomPresenter(hr);
		presenter->SetVideoWindow(m_hwndVideo);
		v_EVRPresenters.push_back(presenter);
	}

	// Create the media session.

	//SafeRelease(&m_pSource);

	for (int i = 0; i < nUrl; i++)
	{


		IMFMediaSource* source = NULL;

		const WCHAR* sURL = urls[i];
		// Create the media source.
		CHECK_HR(hr = CreateMediaSource(sURL, &source));

		return hr;
		//All the following code will never be reached...

		// Create the presentation descriptor for the media source.
		CHECK_HR(hr = source->CreatePresentationDescriptor(&pSourcePD));

		if (i == 0)  	hr = CreatePlaybackTopology(source, pSourcePD, m_hwndVideo, &pTopology, v_EVRPresenters[i]);
		else CHECK_HR(hr = AddToPlaybackTopology(source, pSourcePD, m_hwndVideo, pTopology, v_EVRPresenters[i]));


		//v_sources.push_back(source);

		/*if (i==0) m_pSource = source; //keep one source for time tracking
		else */ SafeRelease(&source);
		SetMediaInfo(pSourcePD);

		SafeRelease(&pSourcePD);
	}


	MFSequencerElementId NewID;
	CHECK_HR(hr = m_pSequencerSource->AppendTopology(pTopology, SequencerTopologyFlags_Last, &NewID));
	_previousTopoID = NewID;
	CHECK_HR(hr = m_pSequencerSource->QueryInterface(IID_IMFMediaSource, (void**)&spSrc));
	CHECK_HR(hr = spSrc->CreatePresentationDescriptor(&spPD));
	CHECK_HR(hr = m_pSequencerSource->QueryInterface(IID_IMFMediaSourceTopologyProvider, (void**)&spSrcTopoProvider));

	SafeRelease(&pTopology);
	CHECK_HR(hr = spSrcTopoProvider->GetMediaSourceTopology(spPD, &pTopology));

	//Now that we're done, we set the topolgy as it should be....

	CHECK_HR(hr = m_pSession->SetTopology(0, pTopology));

	m_state = OpenPending;
	_currentVolume = 1.0f;

	// If SetTopology succeeds, the media session will queue an 
	// MESessionTopologySet event.

done:
	if (FAILED(hr))
	{
		m_state = Closed;
	}
	SafeRelease(&pSourcePD);
	SafeRelease(&pTopology);
	//SafeRelease(&spPD);
	//SafeRelease(&spSrc);
	//SafeRelease(&spSrcTopoProvider);  //Uncoment this and get a crash in D3D shared texture..
	return hr;
}