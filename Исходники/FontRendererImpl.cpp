void FontRendererImpl::Initialize()
{
	trace("[FontRenderer] Initializing DirectWrite.\n");

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)m_dwFactory.GetAddressOf());

	// attempt to get a IDWriteFactory2
	HRESULT hr = m_dwFactory.As(&m_dwFactory2);

	if (FAILED(hr))
	{
		trace("[FontRenderer] IDWriteFactory2 unavailable (hr=%08x), colored font rendering will not be used\n", hr);
	}

	m_gameInterface = CreateGameInterface();

	CreateTextRenderer();
}