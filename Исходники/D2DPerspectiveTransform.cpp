void D2DPerspectiveTransform::CreateDeviceResources()
{
    DirectXBase::CreateDeviceResources();

    m_sampleOverlay = ref new SampleOverlay();

    m_sampleOverlay->Initialize(
        m_d2dDevice.Get(),
        m_d2dContext.Get(),
        m_wicFactory.Get(),
        m_dwriteFactory.Get(),
        "Direct2D perspective transform sample"
    );

    // Load a bitmap from the Windows Imaging Component decoder.
    ComPtr<IWICBitmapDecoder> decoder;
    DX::ThrowIfFailed(
        m_wicFactory->CreateDecoderFromFilename(
            L"mammoth_small.jpg",
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnDemand,
            &decoder
        )
    );

    ComPtr<IWICBitmapFrameDecode> frame;
    DX::ThrowIfFailed(
        decoder->GetFrame(0, &frame)
    );

    ComPtr<IWICFormatConverter> converter;
    DX::ThrowIfFailed(
        m_wicFactory->CreateFormatConverter(&converter)
    );

    // We format convert to a pixel format that is compatible with Direct2D.
    // To optimize for performance when using WIC and Direct2D together, we need to
    // select the target pixel format based on the image's native precision:
    // - <= 8 bits per channel precision: use BGRA channel order
    //   (example: all JPEGs, including the image in this sample, are 8bpc)
    // -  > 8 bits per channel precision: use RGBA channel order
    //   (example: TIFF and JPEG-XR images support 32bpc float
    // Note that a fully robust system will arbitrate between various WIC pixel formats and
    // hardware feature level support using the IWICPixelFormatInfo2 interface.
    DX::ThrowIfFailed(
        converter->Initialize(
            frame.Get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0f,
            WICBitmapPaletteTypeCustom
        )
    );

    // Create bitmap from WIC bitmap.
    DX::ThrowIfFailed(
        m_d2dContext->CreateBitmapFromWicBitmap(
            converter.Get(),
            nullptr,
            &m_bitmapPerspective
        )
    );
}