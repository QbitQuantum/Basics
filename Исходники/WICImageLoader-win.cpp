bool WICImageLoader::encodeImageData(std::string path, ImageBlob data, size_t dataLen, WICPixelFormatGUID pixelFormat, int width, int height, GUID containerFormat)
{
	assert(data != NULL);
	assert(dataLen > 0 && width > 0 && height > 0);

	IWICImagingFactory* pFact = getWICFactory();

	HRESULT hr = S_FALSE;
	IWICStream* pStream = NULL;

	if(NULL != pFact)
	{
		hr = pFact->CreateStream(&pStream);
	}

	if(SUCCEEDED(hr))
	{
		std::wstring wpath;
		wpath.assign(path.begin(), path.end());
		hr = pStream->InitializeFromFilename(wpath.c_str(), GENERIC_WRITE);
	}

	IWICBitmapEncoder* pEnc = NULL;

	if(SUCCEEDED(hr))
	{
		hr = pFact->CreateEncoder(containerFormat, NULL, &pEnc);
	}

	if(SUCCEEDED(hr))
	{
		hr = pEnc->Initialize(pStream, WICBitmapEncoderNoCache);
	}

	IWICBitmapFrameEncode* pFrame = NULL;
	IPropertyBag2* pProp = NULL;

	if(SUCCEEDED(hr))
	{
		hr = pEnc->CreateNewFrame(&pFrame, &pProp);
	}

	if(SUCCEEDED(hr))
	{
		hr = pFrame->Initialize(pProp);
	}

	if(SUCCEEDED(hr))
	{
		hr = pFrame->SetSize(width, height);
	}

	if(SUCCEEDED(hr))
	{
		hr = pFrame->SetPixelFormat(&pixelFormat);
	}

	if(SUCCEEDED(hr))
	{
		size_t bpp = getBitsPerPixel(pixelFormat);
		size_t stride = (width * bpp + 7) / 8;

		hr = pFrame->WritePixels(height, stride, dataLen, (BYTE*)data);
	}

	if(SUCCEEDED(hr))
	{
		hr = pFrame->Commit();
	}

	if(SUCCEEDED(hr))
	{
		hr = pEnc->Commit();
	}

	SafeRelease(&pStream);
	SafeRelease(&pEnc);
	SafeRelease(&pFrame);
	SafeRelease(&pProp);
	return SUCCEEDED(hr);
}