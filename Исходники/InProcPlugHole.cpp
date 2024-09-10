// Must only be called from within critical section
IIPDolphinPtr CInProcPlugHole::GetPeerForCurrentThread()
{
	if (m_piMarshalledPeer == NULL)
		return NULL;

	_ASSERTE(m_dwVMStarterId != 0);
	_ASSERTE(m_hDolphinThread != 0);

	// Note use of reference here so if null, new entry gets updated
	IIPDolphinPtr& piPeer = m_mapPeers[CoGetCurrentProcess()];
	if (piPeer == NULL)
	{
		TRACE("%#x: New peer requested for COM thread id %#x\n", GetCurrentThreadId(), CoGetCurrentProcess());

		LARGE_INTEGER pos;
		pos.QuadPart = 0;
		m_piMarshalledPeer->Seek(pos, STREAM_SEEK_SET, NULL);
		HRESULT hr = ::CoUnmarshalInterface(m_piMarshalledPeer, __uuidof(IIPDolphin), reinterpret_cast<void**>(&piPeer));
		_ASSERTE(SUCCEEDED(hr));
	}

	return piPeer;
}