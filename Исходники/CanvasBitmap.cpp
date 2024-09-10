    ComPtr<IWICBitmapSource> DefaultBitmapAdapter::CreateWICFormatConverter(IStream* fileStream)
    {
        ComPtr<IWICFormatConverter> wicFormatConverter;

        ComPtr<IWICBitmapDecoder> wicBitmapDecoder;
        ThrowIfFailed(m_wicFactory->CreateDecoderFromStream(
            fileStream,
            nullptr,
            WICDecodeMetadataCacheOnDemand,
            &wicBitmapDecoder));

        ComPtr<IWICBitmapFrameDecode> wicBitmapFrameSource;
        ThrowIfFailed(wicBitmapDecoder->GetFrame(0, &wicBitmapFrameSource));

        ThrowIfFailed(m_wicFactory->CreateFormatConverter(&wicFormatConverter));

        ThrowIfFailed(wicFormatConverter->Initialize(
            wicBitmapFrameSource.Get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0,
            WICBitmapPaletteTypeMedianCut));

        return ApplyRotationIfNeeded(m_wicFactory.Get(), wicBitmapFrameSource, wicFormatConverter);
    }