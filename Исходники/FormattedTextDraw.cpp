HRESULT CFormattedTextDraw::CreateTextServicesObject()
{
	HRESULT hr;
	IUnknown *spUnk;

	hr = CreateTextServices(NULL, static_cast<ITextHost*>(this), &spUnk);
	if (hr == S_OK) {
		hr = spUnk->QueryInterface(IID_ITextServices, (void**)&m_spTextServices);
		hr = spUnk->QueryInterface(IID_ITextDocument, (void**)&m_spTextDocument);
		spUnk->Release();
	}
	return hr;
}