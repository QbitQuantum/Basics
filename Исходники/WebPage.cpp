	void StartClassify(const CComBSTR & scriptText)
	{
		clib::recursive_mutex::scoped_lock proc(m_mutex);
		if (m_classified)
		{
			proc.unlock();
			on_refresh(this, EVENT_CLASSIFIED);
			return;
		}
		m_classified = true;
		ClassifyStructVector request;
		
		//Process Main Frame
		InsertScript(m_doc, scriptText);
		PrepRequest(m_doc, request);
		
		//Process Child Frames
		CComQIPtr<IOleContainer> pContainer = m_doc;
		if (!pContainer)
			return;

		CComPtr<IEnumUnknown> pEnumerator;
		HRESULT hr = pContainer->EnumObjects(OLECONTF_EMBEDDINGS, &pEnumerator);
		if (FAILED(hr))
			return;

		CComPtr<IUnknown> pUnk;
		ULONG uFetched;
		for (UINT i = 0; S_OK == pEnumerator->Next(1, &pUnk, &uFetched); i++)
		{
			CComQIPtr<IWebBrowser2> pBrowser = pUnk;
			if (pBrowser)
			{
				CComPtr<IDispatch> spDispDoc;
				HRESULT hr = pBrowser->get_Document(&spDispDoc);
				if (SUCCEEDED(hr))
				{
					// ...and query for an HTML document.
					CComQIPtr<IHTMLDocument> spHTMLDoc = spDispDoc;
					if (spHTMLDoc)
					{
						InsertScript(spHTMLDoc, scriptText);
						PrepRequest(spHTMLDoc, request);
					}
				}
			}
			pUnk.Release();
		}

		m_classifyThreads.SetMaxThreadCount(0);
		ClassifyStructVector batchRequest;
		int textLen = 0;
		for(ClassifyStructVector::iterator itr = request.begin(); itr != request.end(); ++itr)
		{
			textLen += itr->text.length();
			batchRequest.push_back(*itr);
			if (textLen > BATCH_SIZE)
			{
				m_classifyThreads.Append(__FUNCTION__, boost::bind(&threadClassify, this, batchRequest));
				batchRequest.clear();
				textLen = 0;
			}
		}
		if (batchRequest.size())
		{
			m_classifyThreads.Append(__FUNCTION__, boost::bind(&threadClassify, this, batchRequest));
			batchRequest.clear();
		}
		m_classifyThreads.SetMaxThreadCount(THREAD_COUNT);
		//int textLen = 0;
		//BOOL finished = false;
		//HRESULT hr = S_OK;
		//while(hr == S_OK && !finished)
		//{
		//	MARKUP_CONTEXT_TYPE pContext = CONTEXT_TYPE_None;
		//	long pcch = -1;
		//	prev->MoveToPointer(finger);
		//	hr = finger->Right(true, &pContext, NULL, &pcch, NULL);
		//	if (pContext == CONTEXT_TYPE_Text && pcch > 1)
		//	{
		//		ClassifyStruct newItem;
		//		newItem.text.resize(pcch);
		//		prev->Right(false, NULL, NULL, &pcch, &newItem.text[0]);
		//		std::wstring testStr = newItem.text;
		//		boost::algorithm::trim(testStr);
		//		if (testStr.length())
		//		{
		//			markupServices->CreateMarkupPointer(&newItem.textNode);
		//			newItem.textNode->MoveToPointer(prev);
		//			request.push_back(newItem);
		//			textLen += pcch;
		//			if (textLen > 1000)
		//			{
		//				m_classifyThreads.Append(__FUNCTION__, boost::bind(&threadClassify, this, request));
		//				request.clear();
		//				textLen = 0;
		//			}
		//		}
		//	}
		//	finger->IsRightOfOrEqualTo(end, &finished);
		//}
		//if (request.size())
		//{
		//	m_classifyThreads.Append(__FUNCTION__, boost::bind(&threadClassify, this, request));
		//	request.clear();
		//}
		//m_classifyThreads.SetMaxThreadCount(THREAD_COUNT);
	}