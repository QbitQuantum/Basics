int PolylineTest::writeFileMoniker()
{
	ComPtr<IMoniker> moniker;
	auto hr = CreateFileMoniker(kFileName, &moniker);
	if (FAILED(hr)) {
		return -1;
	}
	IBindCtx* pbc;
	CreateBindCtx(0, &pbc);
	ComPtr<IPolyline> polyline;
	hr = moniker->BindToObject(pbc, NULL, IID_IPolyline, (void**)&polyline);
	if (FAILED(hr)) {
		return -1;
	}
	polyline->put_Color(RGB(0xff, 0x00, 0x00));
	COLORREF value;
	polyline->get_Color(&value);
	assert(value == RGB(0xff, 0x00, 0x00));

	ComPtr<IStorage> pStorage;
	ComPtr<IStream> pStream;
	hr = StgCreateStorageEx(kMonikerFileName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
	if (FAILED(hr))
		return hr;
	hr = pStorage->CreateStream(kStreamName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		0, 0, &pStream);
	if (FAILED(hr))
		return hr;
	OleSaveToStream(moniker, pStream);
	return 0;
}