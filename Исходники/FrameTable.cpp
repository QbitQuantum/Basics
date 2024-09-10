void                                           
CFrame::UpdateLinks()
{
	// start from scratch
	m_ChildFrames.clear();

	// detect all child frames
	CComQIPtr<IOleContainer> spContainer = m_Document;
	if (!!spContainer)
	{
		// get an enumerator for the frames
		IEnumUnknown* pEnumerator;
		HRESULT hr = spContainer->EnumObjects(OLECONTF_EMBEDDINGS, &pEnumerator);

		if (SUCCEEDED(hr))
		{
			IUnknown* pUnknown;
			ULONG uFetched;

			// enumerate all the frames
			for (UINT i = 0; S_OK == pEnumerator->Next(1, &pUnknown, &uFetched); i++)
			{
				CComQIPtr<IWebBrowser2> spChildBrowser = pUnknown;
				pUnknown->Release();
				if (!!spChildBrowser)
				{
					// well done, store child frame
					CComPtr<IDispatch> spChildDispDoc;
					CHECK_COM(spChildBrowser->get_Document(&spChildDispDoc), FS(_T("Cannot retrieve document object from %08X"), spChildBrowser));
					CComQIPtr<IHTMLDocument2> spChildDoc = spChildDispDoc;

					// sometimes IE can return NULL spChildDispDoc 
					// 
					// (observed on pages with file download blocking)
					// test for valid doc
					if (!!spChildDoc)
					{
						CComBSTR url2;
						CHECK_COM(spChildDoc->get_URL(&url2), FS(_T("Cannot retrieve location URL from %08X"), spChildDoc));
						CString URL2 = url2;

						// it wouldn't be so easy to simply add child document into childs
						// but IE (maybe) does some reallocation of this document, so we need to do lookup via frameId

						TFrameId id = m_FrameTable.GetFrameId(spChildDoc, false);

						// wait for document to load, 
						// there is RISK OF CALLS to other functions !!!
						//if (id==NULL_FRAME) id = m_FrameTable.GetFrameId(spChildDoc, true); // blocking call
						if (id==NULL_FRAME)
						{
							// TODO: tohle se muze nekdy stat, kdyz se frame jeste nestihne naloadovat pri F5, napriklad gmail.com to dela
							TRACE_W(FS(_T("Child doc not found for %s !!"), URL2));
						}
						else
						{
							m_ChildFrames.push_back(id);
						}
					}
				}
			}
		}
		pEnumerator->Release();
	}
}