	CXmlWriter_COM::CXmlWriter_COM(_In_ PExportStream pExportStream)
		: CXmlWriter(pExportStream)
	{
		HRESULT hResult;
		if (pExportStream.get() == nullptr)
			throw CNMRException(NMR_ERROR_INVALIDPARAM);

		// Create XML Writer
		hResult = CreateXmlWriter(__uuidof(IXmlWriter), (void**)&m_pXMLWriter, nullptr);
		if (hResult != S_OK)
			throw CNMRException_Windows(NMR_ERROR_COULDNOTCREATEXMLWRITER, hResult);

		// Cast to COM Streams
		CExportStream_COM * pCOMExportStream = dynamic_cast<CExportStream_COM *> (pExportStream.get());
		if (pCOMExportStream == nullptr)
			throw CNMRException(NMR_ERROR_INVALIDSTREAMTYPE);
		m_pCOMStream = pCOMExportStream->getCOMStream();

		// Set XML Writer Output
		hResult = m_pXMLWriter->SetOutput(m_pCOMStream);
		if (hResult != S_OK)
		  throw CNMRException_Windows(NMR_ERROR_COULDNOTSETXMLOUTPUT, hResult);

		// Set XML Writer Property
		hResult = m_pXMLWriter->SetProperty(XmlWriterProperty_Indent, true);
		if (hResult != S_OK)
			throw CNMRException_Windows(NMR_ERROR_COULDNOTSETXMLPROPERTY, hResult);
	}