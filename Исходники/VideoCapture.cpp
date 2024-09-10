long VideoCapture::ShowPropertyPage(HWND hwndParent)
{

	HRESULT hr;
	ISpecifyPropertyPages *pSpecify=0;
	CAUUID cauuid;

	hr = pSource->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpecify);

	if (SUCCEEDED(hr)) 
	{
		do 
		{
			hr = pSpecify->GetPages(&cauuid);

			hr = OleCreatePropertyFrame(hwndParent, 0, 0, NULL, 1,
				(IUnknown **)&pSource, cauuid.cElems,
				(GUID *)cauuid.pElems, 0, 0, NULL);

			CoTaskMemFree(cauuid.pElems);
		} while(0);
	}

	// Release interfaces
	if (pSpecify)
		pSpecify->Release();

	return hr;
}