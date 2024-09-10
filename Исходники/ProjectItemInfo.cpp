HRESULT STDMETHODCALLTYPE CProjectItemInfo::CreateConfigurationParams(ItcProjectNode * AParentNode, ItcProjectNodeConfigurationInfo * * Value)
{
	HRESULT hr;

	// Get location path
	CComBSTR path = GetPath(AParentNode);

	// Choose the name
	CComBSTR name = GetName(AParentNode, 0);

	CComObject<CPluginConfiguration>* conf;
	hr = CComObject<CPluginConfiguration>::CreateInstance(&conf);
	if (FAILED(hr)) return hr;
  
	conf->Initialize( name,
	                  path,
	                  AParentNode,
	                  m_messenger );

	return conf->QueryInterface(Value);
}