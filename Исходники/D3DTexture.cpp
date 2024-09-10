void D3DTexture2D::DrawAsDc(std::function<void (const HDC, RECT**)> fn){
	IDXGISurface1* surface = nullptr;
	HRESULT hr = texture->QueryInterface(__uuidof(IDXGISurface1), (void**)&surface);
	IF_NG(hr) {
		LOG_DBG("Failed to get IDXGISurface1 Interface.\r\n");
		return;
	}

	HDC dc = nullptr;
	hr = surface->GetDC(false, &dc);
	IF_NG(hr) {
		LOG_DBG("Failed to get HDC Handle.\r\n");
		surface->Release();
		return;
	}

	RECT* prect;

	fn(dc, &prect);

	surface->ReleaseDC(prect);

	if (prect) delete prect;
	surface->Release();
}