// Initialize Device List
HRESULT DeviceList::EnumerateDevices()
{
	HRESULT hr = S_OK;
	IMFAttributes *pAttributes = NULL;

	Clear();

	// Initialize an attribute store. We will use this to
	// specify the enumeration parameters.

	hr = MFCreateAttributes(&pAttributes, 1);

	// Ask for source type = video capture devices
	if (SUCCEEDED(hr))
	{
		hr = pAttributes->SetGUID(
			MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE,
			MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
			);
	}

	// Enumerate devices.
	if (SUCCEEDED(hr))
	{
		hr = MFEnumDeviceSources(pAttributes, &m_ppDevices, &m_cDevices);
	}

	SafeRelease(&pAttributes);

	return hr;
}