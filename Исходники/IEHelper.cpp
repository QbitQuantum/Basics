void MonitorFlash(IDispatch *pDisp)
{
	if (!pDisp) return;
	HRESULT hr = S_OK;

	// 使用CFlashSink3, 连接点无法成功Advise, 报错: E_POINTER 0x80004003(无效指针)
	/*
	EVENT_SINK es;
	CFlashSink3* sink3 = new CFlashSink3();
	IDispatch* pSinkDisp = NULL;
	hr = sink3->QueryInterface(DIID__IShockwaveFlashEvents, reinterpret_cast<void**>(&pSinkDisp));
	hr = AtlAdvise(pDisp, sink3, DIID__IShockwaveFlashEvents, &es.dwCookie);
	if (SUCCEEDED(hr))
	{
		es.pUnkSink = pSinkDisp;
		es.pUnkSrc = pDisp;
		es.iid = DIID__IShockwaveFlashEvents;
		CIESeeker::Instance()->AddSink(es);
		cout << _T("Advised[DIID__IShockwaveFlashEvents], dwCookie = ") << es.dwCookie << endl;
	}
	*/

	// 使用CFlashSink2, 连接点无法成功Advise, dwCookie = 0. 报错: CONNECT_E_CANNOTCONNECT 0x80040202(无法连接).
	// IShockwaveFlashEvents不支持CCmdTarget方式的连接点
	/*
	EVENT_SINK es;
	CFlashSink2* sink2 = new CFlashSink2();
	IDispatch* pSinkDisp = sink2->GetIDispatch(FALSE);
	//hr = AfxConnectionAdvise(pDisp, DIID__IShockwaveFlashEvents, pSinkDisp, FALSE, &es.dwCookie);
	hr = AtlAdvise(pDisp, pSinkDisp, DIID__IShockwaveFlashEvents, &es.dwCookie);
	if (hr)
	{
		es.pUnkSink = pSinkDisp;
		es.pUnkSrc = pDisp;
		es.iid = DIID__IShockwaveFlashEvents;
		CIESeeker::Instance()->AddSink(es);
		cout << _T("Advised[DIID__IShockwaveFlashEvents], dwCookie = ") << es.dwCookie << endl;
	}
	*/

	EVENT_SINK es;
	CComObject<CFlashSink> *sink = new CComObject<CFlashSink>;
	hr = AtlAdvise(pDisp, sink, DIID__IShockwaveFlashEvents, &es.dwCookie);
	if (SUCCEEDED(hr))
	{
		es.pUnkSink = sink;
		es.pUnkSrc = pDisp;
		es.iid = DIID__IShockwaveFlashEvents;
		CIESeeker::Instance()->AddSink(es);
		cout << _T("Advised[DIID__IShockwaveFlashEvents], dwCookie = ") << es.dwCookie << endl;
	}

	/*
	IConnectionPointContainer *spCPC = NULL;
	IConnectionPoint *spCP = NULL;
	//CFlashSunk *sink = new CFlashSunk();
	//CComObject<CFlashSunk> *sink = new CComObject<CFlashSunk>();
	//DWORD dwCookie = 0;

	hr = pDisp->QueryInterface(IID_IConnectionPointContainer, reinterpret_cast<void**>(&spCPC));
	if (SUCCEEDED(hr) && spCPC)
	{
		cout << _T("Found IHTMLObjectElement>>IConnectionPointContainer!") << endl;

		hr = spCPC->FindConnectionPoint(DIID__IShockwaveFlashEvents, &spCP);
		if (SUCCEEDED(hr) && spCP) 
		{
			cout << _T("Found IHTMLObjectElement>>IConnectionPointContainer>>IConnectionPoint[DIID__IShockwaveFlashEvents]!") << endl;
			
			hr = spCP->Advise(m_flashSink, &m_flashCookie);
			if (SUCCEEDED(hr))
			{
				cout << _T("Advised[DIID__IShockwaveFlashEvents], dwCookie = ") << m_flashCookie << endl;
			}
		}
	}
	*/
	//if(spCP) spCP->Release();
	//if(spCPC) spCPC->Release();
}