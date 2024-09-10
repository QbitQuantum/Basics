	HRESULT XmlFileParser::ElementContent( const WCHAR* strData, UINT DataLen, BOOL More )
	{
		// Accumulate this element content into the current desc body content.
		wcsncat_s( m_CurrentElementDesc.strElementBody, strData, DataLen );


		if(m_nType == 1 && localFind && _wcsicmp(m_CurrentElementDesc.strElementName,L"Description") == 0)
		{
			memset(pArcadeInfo->strDescription,0,1024); 
			
			wcsncpy_s( pArcadeInfo->strDescription,m_CurrentElementDesc.strElementBody,wcslen(m_CurrentElementDesc.strElementBody) );
			localFind = false;
		}
		return S_OK;
	}