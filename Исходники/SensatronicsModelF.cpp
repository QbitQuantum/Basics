STDMETHODIMP CSensatronicsModelF::GetConfig(void)
{
	HRESULT hr = S_OK;

	CString sTrace(_T(""));

	CComPtr<IDataConnector> pDataConnector = 0;
	hr = pDataConnector.CoCreateInstance(__uuidof(DataConnector));

	if(SUCCEEDED(hr))
	{
		CXMLSensatronicsConfig XMLSensatronicsConfig;
		LONG* plConfigHandler = (LONG*)&XMLSensatronicsConfig;	// so we can pass this through to

		hr = pDataConnector->RequestModelFSerialComConfigData(m_bstrName.Copy(), m_bstrComPort.Copy(), plConfigHandler);

		if(SUCCEEDED(hr))
		{
			hr = ProcessConfig(&XMLSensatronicsConfig);
		}
	}

	return hr;
}