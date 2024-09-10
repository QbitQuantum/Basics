void SaveBitmap(IWICBitmap* bitmap, GUID pixelFormat, const WCHAR *filename)
{
	HRESULT result = S_OK;
	ComPtr<IWICStream> stream;
	ComPtr<ID2D1Factory1> d2dfactory;
	ComPtr<IDWriteFactory> dwriteFactory;
	ComPtr<IWICImagingFactory> wicFactory;

	d2d_create_factory_fn pfn_D2D1CreateFactory("D2D1CreateFactory", L"D2d1.dll");
	dwrite_create_factory_fn pfn_DWriteCreateFactory("DWriteCreateFactory", L"Dwrite.dll");
	HR_RET(pfn_D2D1CreateFactory.initialize());
	HR_RET(pfn_DWriteCreateFactory.initialize());

	// Create a Direct2D factory
	HR_RET(pfn_D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		__uuidof(ID2D1Factory1),
		nullptr,
		reinterpret_cast<void**>(d2dfactory.GetAddressOf())));

	// Initialize COM - ignore failure
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	// Create a DirectWrite factory.
	HR_RET(pfn_DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown **>(dwriteFactory.GetAddressOf())));

	HR_RET(CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWICImagingFactory),
		(void**)&wicFactory));

	HR_RET(wicFactory->CreateStream(&stream));
	HR_RET(stream->InitializeFromFilename(filename, GENERIC_WRITE));

	ComPtr<IWICBitmapEncoder> encoder;
	HR_RET(wicFactory->CreateEncoder(GUID_ContainerFormatBmp, nullptr, &encoder));
	HR_RET(encoder->Initialize(stream.Get(), WICBitmapEncoderNoCache));

	ComPtr<IWICBitmapFrameEncode> frameEncode;
	HR_RET(encoder->CreateNewFrame(&frameEncode, nullptr));
	HR_RET(frameEncode->Initialize(nullptr));

	UINT width, height;
	HR_RET(bitmap->GetSize(&width, &height));
	HR_RET(frameEncode->SetSize(width, height));
	HR_RET(frameEncode->SetPixelFormat(&pixelFormat));

	HR_RET(frameEncode->WriteSource(bitmap, nullptr));

	HR_RET(frameEncode->Commit());
	HR_RET(encoder->Commit());
}