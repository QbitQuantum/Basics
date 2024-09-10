unsigned int __stdcall CreateBrokerThreadEntry(void *data)
{
TRY_CATCH

	CoInitialize(0);

	SBrokerThreadEntryData* inData = reinterpret_cast<SBrokerThreadEntryData*>(data);
	SStartBroker *startBroker = reinterpret_cast<SStartBroker*>(inData->buf);
	if (NULL == startBroker->buf || 0 == startBroker->bufSize)
		throw MCException("NULL == startBroker->buf || 0 == startBroker->bufSize");

	CComPtr<IDispatch> broker;
	HRESULT hr;
	if((hr=broker.CoCreateInstance(L"Broker.CoBroker",NULL,CLSCTX_LOCAL_SERVER))!=S_OK)
		throw CExceptionBase(__LINE__,_T(__FILE__),_T(__DATE__),tstring(_T("CoBroker creation failed")),hr);

	CScopedTracker<HGLOBAL> globalMem;	
	globalMem.reset(GlobalAlloc(GMEM_MOVEABLE, startBroker->bufSize), GlobalFree);
	if (NULL == globalMem)
		throw MCException_Win("Failed to GlobalAlloc");

	CComPtr<IStream> stream;
	hr = CreateStreamOnHGlobal(globalMem, FALSE, &stream);
	if (S_OK != hr)
		throw MCException_Win(Format(_T("Failed to GlobalAlloc; result = %X"),hr));

	ULARGE_INTEGER size;
	size.QuadPart = startBroker->bufSize;
	hr = stream->SetSize(size);
	if (S_OK != hr)
		throw MCException_Win(Format(_T("Failed to stream->SetSize; result = %X"),hr));

	hr = CoMarshalInterface(stream, IID_IDispatch, broker, MSHCTX_LOCAL, NULL, MSHLFLAGS_NORMAL);
	if (S_OK != hr)
		throw MCException_Win(Format(_T("Failed to CoMarshalInterface; result = %X"),hr));

	ULARGE_INTEGER uLi;
	LARGE_INTEGER li;
	li.QuadPart = 0;

	/// Writing stream to client process memory
	stream->Seek(li, STREAM_SEEK_SET, NULL);
	boost::scoped_array<char> localBuf;
	ULONG readCount;
	localBuf.reset(new char[startBroker->bufSize]);
	hr = stream->Read(localBuf.get(), startBroker->bufSize, &readCount);
	if (S_OK != hr)
		throw MCException_Win(Format(_T("stream->Read; result = %X"),hr));

	/// Writing stream date into client process memory
	ULONG writtenCount;
	if (FALSE == WriteProcessMemory(inData->clientProcess, startBroker->buf, localBuf.get(), readCount, &writtenCount))
		throw MCException_Win("Failed to WriteProcessMemory ");

	CoUninitialize();

	Log.Add(_MESSAGE_,_T("Broker created and marshaled to BrokerProxy process"));

	return TRUE;

CATCH_LOG()

	CoUninitialize();
	return FALSE;
}