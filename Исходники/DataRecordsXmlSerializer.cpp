BOOL DataRecordsXmlSerializer::Export(LPCTSTR fileName, FullTrackRecordCollection& col)
{
	HRESULT hr;
	CComPtr<IStream> pOutFileStream;
	CComPtr<IXmlWriter> pWriter;

	//Open writeable output stream
	if (FAILED(hr = FileStream::OpenFile(fileName, &pOutFileStream, TRUE)))
	{
		TRACE(_T("@1 DataRecordsXmlSerializer::Export. Error creating file writer, error is %08.8lx"), hr);
		return FALSE;
	}

	if (FAILED(hr = CreateXmlWriter(__uuidof(IXmlWriter),(void**) &pWriter, NULL)))
	{
		TRACE(_T("@1 DataRecordsXmlSerializer::Export. Error creating xml writer, error is %08.8lx"), hr);
		return FALSE;
	}

	if (FAILED(hr = pWriter->SetOutput(pOutFileStream)))
	{
		TRACE(_T("@1 DataRecordsXmlSerializer::Export. Error setting output for writer, error is %08.8lx"), hr);
		return FALSE;
	}
	pWriter->WriteStartElement(NULL, _T("fulltrackcollection"), NULL);
	FullTrackRecordCollection::iterator it = col.begin();
	while (it != col.end())
	{
		pWriter->WriteStartElement(NULL, _T("fulltrackrecord"), NULL);
		AppendXMLElement(*pWriter, (*it)->track);
		AppendXMLElement(*pWriter, (*it)->album);
		AppendXMLElement(*pWriter, (*it)->artist);
		AppendXMLElement(*pWriter, (*it)->genre);
		AppendXMLElement(*pWriter, (*it)->collection);
		pWriter->WriteEndElement();
		it++;
	}
	pWriter->WriteEndElement();
	pWriter.Release();
	pOutFileStream.Release();
	return TRUE;
}