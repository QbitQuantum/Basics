void RenderDevice::init()
{
	ComResult hr;

	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0, D3D11_SDK_VERSION, &this->pDevice3, nullptr, &this->pDeviceContext3);
	hr = this->pDevice3.As(&this->pxDevice);

	hr = D2D1CreateDevice(this->pxDevice.Get(), D2D1::CreationProperties(
		D2D1_THREADING_MODE_MULTI_THREADED, D2D1_DEBUG_LEVEL_ERROR, D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS),
		&this->pDevice2);

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &this->pdwFactory);
	hr = this->pdwFactory->GetSystemFontCollection(&this->pSystemFontCollection);
}