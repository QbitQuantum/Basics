STDMETHODIMP CLHTMLActiveDocument::put_src(/*[in]*/ BSTR newVal)
{
	ATLASSERT(0);
#if 0
	StopPlay();

	if (m_textData)
	{
		m_textData.Release();
	}

	if (m_pWindow)
	{
#if 0
		m_pWindow->Free();
#endif
		m_pWindow->Release();
		m_pWindow = NULL;

		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	}

	m_src = newVal;

	CComQIPtr<IServiceProvider> sp = m_spClientSite;
	if (sp)
	{
		CComPtr<IMoniker> imkName;

		CComPtr<IBindHost> bindHost;
		if (SUCCEEDED(sp->QueryService(SID_SBindHost, &bindHost)))
		{
			bindHost->CreateMoniker(m_src, NULL, &imkName, 0);
		}
		else
		{
			CreateURLMoniker(NULL, m_src, &imkName);
		}

		if (imkName)
		{
			// Note I'm creating the window before loading the document
			CComObject<CLHTMLWindow2>::CreateInstance(&m_pWindow);
			if (m_pWindow)
			{
				m_pWindow->AddRef();
			//	m_hWnd = m_hWnd;
#if 0	// I Had this
				m_pWindow->m_pActiveDocument = this;
#endif

			// TODO, init scripting if not already done?

				CComPtr<IBindCtx> bctx;
				if (SUCCEEDED(CreateBindCtx(0/*reserved*/, &bctx)))
				{
					Load(FALSE, imkName, bctx, 0);

					if (m_document)
					{
						CComQIPtr<ILDOMDocumentView> documentView = m_document;
						documentView->createPresentation(&m_view);
					//	SetDocument(document);

						if (FALSE)
						{
							StartPlay();
						}

						m_pWindow->m_pCanvas->m_pView = static_cast<CHTMLDocumentView*>(m_view.p);
						m_pWindow->m_pCanvas->m_htmTree = m_pWindow->m_pCanvas->m_pView->m_pRootElement;

					//	CComQIPtr<ILDOMDocumentView> documentView = m_document;
					//	documentView->createPresentation(&m_view);
					//	ATLASSERT(0);
#if 0
						m_pView->SetDocument(m_document);
#endif
					}
				}
			}
		}
	}

#endif
	return S_OK;
}