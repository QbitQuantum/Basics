HRESULT CAMVfwCompressDialogs::GetPropertyWindow(VfwCompressDialogs iDialog, const ACamstudioFilter *pFilter)
{
	if(!pFilter)
		return E_FAIL;
	if(!pFilter->GetFilter())
		return E_FAIL;
	
	IAMVfwCompressDialogs *pCompDialog = NULL;
	HRESULT hr = pFilter->GetFilter()->QueryInterface(IID_IAMVfwCompressDialogs, (void**)& pCompDialog);
	if(SUCCEEDED(hr))
	{
		hr = pCompDialog->ShowDialog(iDialog, m_hWnd);
		return hr;
	}
	if(iDialog == VfwCompressDialog_QueryAbout || iDialog == VfwCompressDialog_About)
	{
		return E_FAIL;
	}

	ISpecifyPropertyPages *pProp;
	hr = pFilter->GetFilter()->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pProp);
	if (SUCCEEDED(hr)) 
	{
		if(VfwCompressDialog_QueryConfig == iDialog || VfwCompressDialog_QueryAbout == iDialog)
		{
			return hr;
		}
		// Get the filter's name and IUnknown pointer.
		FILTER_INFO FilterInfo;
		hr = pFilter->GetFilter()->QueryFilterInfo(&FilterInfo);
		if(FAILED(hr))
			return E_FAIL;
		IUnknown *pFilterUnk = 0;

		if(SUCCEEDED(pFilter->GetFilter()->QueryInterface(IID_IUnknown, (void **)&pFilterUnk)))
		{
			// Show the page. 
			CAUUID caGUID;
			pProp->GetPages(&caGUID);
			pProp->Release();
			OleCreatePropertyFrame(
				m_hWnd,                 // Parent window
				0, 0,                   // Reserved
				FilterInfo.achName,     // Caption for the dialog box
				1,                      // Number of objects (just the filter)
				&pFilterUnk,            // Array of object pointers. 
				caGUID.cElems,          // Number of property pages
				caGUID.pElems,          // Array of property page CLSIDs
				0,                      // Locale identifier
				0, NULL                 // Reserved
				);

			// Clean up.
			if(pFilterUnk)
				pFilterUnk->Release();
			if(FilterInfo.pGraph)
				FilterInfo.pGraph->Release(); 
			if(caGUID.pElems)
				CoTaskMemFree(caGUID.pElems);
		}
	}
	return hr;
}