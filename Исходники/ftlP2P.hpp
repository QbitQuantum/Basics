	CFP2PEnvInit::~CFP2PEnvInit()
	{
		HRESULT hr = S_OK;
		if (m_bInitPnrp)
		{
			COM_VERIFY(PeerPnrpShutdown());
		}
		if (m_bInitGraph)
		{
			COM_VERIFY(PeerGraphShutdown());
		}
	}