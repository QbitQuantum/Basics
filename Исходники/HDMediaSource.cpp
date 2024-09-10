HRESULT HDMediaSource::DoStart(SourceOperation* op)
{
	DbgLogPrintf(L"%s::DoStart...",L"HDMediaSource");

	if (op->GetOperation() != SourceOperation::OP_START)
		return E_UNEXPECTED;

	ComPtr<IMFPresentationDescriptor> ppd;
	auto start_op = static_cast<StartOperation*>(op);
	HRESULT hr = start_op->GetPresentationDescriptor(ppd.GetAddressOf());
	if (FAILED(hr))
		return hr;

	bool bSeek = false,bResume = false;
	bool forceSeek = false;
	AutoPropVar propvar(&op->GetData());
	if (propvar.GetType() == VT_I8)
	{
		if ((_state != STATE_STOPPED) && (propvar.GetInt64() != 0))
		{
			bSeek = true;
		}else if (propvar.GetInt64() <= 0)
		{
			if (_state == STATE_STARTED || _state == STATE_PAUSED)
				bSeek = forceSeek = true;
		}
	}else if (propvar.GetType() == VT_EMPTY)
	{
		if (_state == STATE_PAUSED)
			bResume = true;
	}

	if (bResume)
		DbgLogPrintf(L"%s::DoStart->Resume Play...",L"HDMediaSource");

	hr = SelectStreams(ppd.Get(),op->GetData(),bSeek,false);

	_seekAfterFlag = false; //指示Seek后的第一个Packet
	if ((SUCCEEDED(hr) && (propvar.GetInt64() != 0)) || forceSeek) {
		hr = SeekOpen(propvar.GetInt64()); //to Seek...
	}else{
		if (start_op->GetSeekToTime() != PACKET_NO_PTS)
			_pMediaParser->Seek(start_op->GetSeekToTime(), true, AVSeekDirection::SeekDirection_Auto);
	}

	if (SUCCEEDED(hr))
	{
		DbgLogPrintf(L"%s::DoStart->Event %s",L"HDMediaSource",
			bSeek ? L"MESourceSeeked":L"MESourceStarted");

		ComPtr<IMFMediaEvent> pNewEvent;
		hr = MFCreateMediaEvent(bSeek ? MESourceSeeked:MESourceStarted,GUID_NULL,S_OK,
			&op->GetData(),pNewEvent.GetAddressOf());

		if (SUCCEEDED(hr)) //[optional] MF_EVENT_SOURCE_ACTUAL_START...
			hr = _pEventQueue->QueueEvent(pNewEvent.Get());

		if (SUCCEEDED(hr) && !bResume)
		{
			_state = STATE_BUFFERING;
			if (_network_mode)
				SendNetworkStartBuffering();
			else
				PreloadStreamPacket(); //如果不是打开网络流，DoOpen就执行LoadSample队列

#ifdef _DEBUG
			double queueMaxTime = GetAllStreamMaxQueueTime();
			DbgLogPrintf(L"%s::DoStart->Queue Max Time %0.3f",L"HDMediaSource",(float)queueMaxTime);
#endif
		}

		if (SUCCEEDED(hr))
		{
			for (unsigned i = 0;i < _streamList.Count();i++)
			{
				ComPtr<HDMediaStream> pStream;
				_streamList.GetAt(i,pStream.GetAddressOf());

				if (pStream->IsActive()) {
					pStream->Start(op->GetData(),bSeek);
					pStream->SetOnceState();
				}
			}
		}
	}

	_state = STATE_STARTED;

	if (FAILED(hr))
		_pEventQueue->QueueEventParamVar(MESourceStarted,GUID_NULL,hr,nullptr);

	DbgLogPrintf(L"%s::DoStart Result:0x%08X",L"HDMediaSource",hr);
	return hr;
}