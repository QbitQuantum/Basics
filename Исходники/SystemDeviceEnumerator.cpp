void CSystemDeviceEnumerator::EnumerateDMOs(const IID clsidDMOCategory)
{
	IEnumDMO* pEnum = NULL; 
	HRESULT hr = DMOEnum(
		clsidDMOCategory,			// Category
		DMO_ENUMF_INCLUDE_KEYED,	// Included keyed DMOs
		0, NULL,					// Input types (don't care)
		0, NULL,					// Output types (don't care)
		&pEnum);

	if (SUCCEEDED(hr)) 
	{
		CLSID clsidDMO;
		WCHAR* wszName;
		do
		{
			hr = pEnum->Next(1, &clsidDMO, &wszName, NULL);
			if (hr == S_OK) 
			{  
				// Now wszName holds the friendly name of the DMO, 
				// and clsidDMO holds the CLSID. 
				CString sName(wszName);
				m_listDMOs.push_back(sName);
				CoTaskMemFree(wszName);
			}
		} while (hr == S_OK);
		pEnum->Release();
	}
}