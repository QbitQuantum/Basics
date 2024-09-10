void gs_device::InitFactory(uint32_t adapterIdx, IDXGIAdapter1 **padapter)
{
	HRESULT hr;
	IID factoryIID = (GetWinVer() >= 0x602) ? dxgiFactory2 :
		__uuidof(IDXGIFactory1);

	hr = CreateDXGIFactory1(factoryIID, (void**)factory.Assign());
	if (FAILED(hr))
		throw UnsupportedHWError("Failed to create DXGIFactory", hr);

	hr = factory->EnumAdapters1(adapterIdx, padapter);
	if (FAILED(hr))
		throw UnsupportedHWError("Failed to enumerate DXGIAdapter", hr);
}