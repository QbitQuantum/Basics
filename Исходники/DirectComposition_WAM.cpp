HRESULT CApplication::CreateD2D1BitmapFromFile(LPCWSTR filename, ID2D1Bitmap **bitmap)
{
    HRESULT hr = (bitmap == nullptr) ? E_POINTER : S_OK;

    if (SUCCEEDED(hr))
    {
        *bitmap = nullptr;

        hr = (_wicFactory == nullptr) ? E_UNEXPECTED : S_OK;
    }

    CComPtr<IWICBitmapDecoder> wicBitmapDecoder;

    if (SUCCEEDED(hr))
    {
        hr = _wicFactory->CreateDecoderFromFilename(
            filename,
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &wicBitmapDecoder);
    }

    CComPtr<IWICBitmapFrameDecode> wicBitmapFrame;

    if (SUCCEEDED(hr))
    {
        hr = wicBitmapDecoder->GetFrame(0, &wicBitmapFrame);
    }

    CComPtr<IWICFormatConverter> wicFormatConverter;

    if (SUCCEEDED(hr))
    {
        hr = _wicFactory->CreateFormatConverter(&wicFormatConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = wicFormatConverter->Initialize(
            wicBitmapFrame,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0f,
            WICBitmapPaletteTypeMedianCut);
    }

    CComPtr<IWICBitmap> wicBitmap;

    if (SUCCEEDED(hr))
    {
        hr = _wicFactory->CreateBitmapFromSource(wicFormatConverter, WICBitmapCacheOnLoad, &wicBitmap);
    }

    if (SUCCEEDED(hr))
    {
        hr = _d2d1DeviceContext->CreateBitmapFromWicBitmap(wicBitmap, bitmap); 
    }

    return hr;
}