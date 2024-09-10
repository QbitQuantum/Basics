bool SFXmlReader::initFrameByXsd(string xsdPath)
{
	HRESULT hr = S_OK;
	CComPtr<IStream> pFileStream;
	CComPtr<IXmlReader> pReader;
	XmlNodeType nodeType = XmlNodeType_None;
	LPCWSTR nodeName;
	LPCWSTR name;
	LPCWSTR value;
	bool ret;

	//Open read-only input stream
	hr = SHCreateStreamOnFileA(xsdPath.c_str(), STGM_READ, &pFileStream);
	if (SUCCEEDED(hr))
	{
		hr = CreateXmlReader(__uuidof(IXmlReader), (void**)&pReader, NULL);
	}
	else
	{
		sf_cout(DEBUG_COM, "Error: Can't find the XSD file. (\"" << xsdPath << "\")" << endl);

		return false;
	}
	pReader->SetInput(pFileStream);
	hr = pReader->Read(NULL);

	UINT tabs = 0;
	vector<string> arrNodeBuffer;
	for (; S_OK == hr; hr = pReader->Read(NULL))
	{
		pReader->GetLocalName(&nodeName, NULL);
		if (nodeName[0] > L' ')
		{
			if (wcscmp(nodeName, L"element") == 0 || wcscmp(nodeName, L"attribute") == 0)
			{
				pReader->GetNodeType(&nodeType);
				if (nodeType == XmlNodeType_Element)
				{
					sf_wcout(DEBUG_RES_LOAD, endl);
					for (UINT i = 0; i < tabs; i++)
					{
						sf_wcout(DEBUG_RES_LOAD, L"\t");
					}
					sf_wcout(DEBUG_RES_LOAD, nodeName << L" ");

					POLL_XML_ATTR_BEGIN
						if (wcscmp(nodeName, L"element") == 0)
						{
							if (tabs >= arrNodeBuffer.size())
							{
								arrNodeBuffer.insert(arrNodeBuffer.end(), utfValue);
							}
							if (utfName == "name" || utfName == "ref")
							{
								arrNodeBuffer[tabs] = utfValue;
								if (m_frame.find(utfValue) == m_frame.end())
								{
									m_frame[utfValue].m_name = utfValue;
									m_frame[utfValue].m_index = 0;
									m_frame[utfValue].m_depth = 0;
									m_frame[utfValue].m_isOnly = true;
									m_frame[utfValue].m_parent = NULL;
									m_frame[utfValue].m_attrData = map<string, XsdAttrData>{};
									m_frame[utfValue].m_nodeData = {};
								}
								if (tabs > 0)
								{
									string parent = arrNodeBuffer[tabs - 1];

									m_frame[utfValue].m_parent = &m_frame[parent];
									m_frame[parent].m_nodeData.insert(m_frame[parent].m_nodeData.end(), &m_frame[utfValue]);
								}
								if (m_pFrameRootNode == NULL)
								{
									m_pFrameRootNode = &m_frame[utfValue];
								}
							}
							else if (utfName == "maxOccurs")
							{
								if (utfValue == "unbounded")
								{
									m_frame[arrNodeBuffer[tabs]].m_isOnly = false;
								}
							}
						}
						else if (wcscmp(nodeName, L"attribute") == 0)
						{
							if (utfName == "name")
							{
								map<string, XsdAttrData>& mapAttr = m_frame[arrNodeBuffer[tabs - 1]].m_attrData;

								mapAttr[utfName].m_name = utfValue;
								mapAttr[utfName].m_index = mapAttr.size();
							}
						}
					POLL_XML_ATTR_END
					if (!(pReader->IsEmptyElement()) && wcscmp(nodeName, L"element") == 0)
					{
						tabs++;
					}
				}
				else if (nodeType == XmlNodeType_EndElement)
				{
					tabs--;
				}
			}