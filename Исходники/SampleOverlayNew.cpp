void SampleOverlay::CreateDeviceDependentResources()
{
    DX::ThrowIfFailed(
        m_deviceResources->GetD2DDeviceContext()->CreateSolidColorBrush(ColorF(ColorF::White), &m_whiteBrush)
    );

    ComPtr<IWICBitmapDecoder> wicBitmapDecoder;
    DX::ThrowIfFailed(
        m_deviceResources->GetWicImagingFactory()->CreateDecoderFromFilename(
            L"windowstitle-sdk.png",
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnDemand,
            &wicBitmapDecoder
        )
    );

    ComPtr<IWICBitmapFrameDecode> wicBitmapFrame;
    DX::ThrowIfFailed(
        wicBitmapDecoder->GetFrame(0, &wicBitmapFrame)
    );

    ComPtr<IWICFormatConverter> wicFormatConverter;
    DX::ThrowIfFailed(
        m_deviceResources->GetWicImagingFactory()->CreateFormatConverter(&wicFormatConverter)
    );

    DX::ThrowIfFailed(
        wicFormatConverter->Initialize(
            wicBitmapFrame.Get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0,
            WICBitmapPaletteTypeCustom  // the BGRA format has no palette so this value is ignored
        )
    );

    double dpiX = 96.0;
    double dpiY = 96.0;
    DX::ThrowIfFailed(
        wicFormatConverter->GetResolution(&dpiX, &dpiY)
    );

    DX::ThrowIfFailed(
        m_deviceResources->GetD2DDeviceContext()->CreateBitmapFromWicBitmap(
            wicFormatConverter.Get(),
            BitmapProperties(
                PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
                static_cast<float>(dpiX),
                static_cast<float>(dpiY)
            ),
            &m_logoBitmap
        )
    );

    m_logoSize = m_logoBitmap->GetSize();

    ComPtr<IDWriteTextFormat> nameTextFormat;
    DX::ThrowIfFailed(
        m_deviceResources->GetDWriteFactory()->CreateTextFormat(
            L"Segoe UI",
            nullptr,
            DWRITE_FONT_WEIGHT_LIGHT,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            36.0f,
            L"en-US",
            &nameTextFormat
        )
    );

    DX::ThrowIfFailed(
        nameTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)
    );

    DX::ThrowIfFailed(
        nameTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR)
    );

    DX::ThrowIfFailed(
        m_deviceResources->GetDWriteFactory()->CreateTextLayout(
            m_caption.c_str(),
            static_cast<UINT32>(m_caption.size()),
            nameTextFormat.Get(),
            4096.0f,
            4096.0f,
            &m_textLayout
        )
    );

    DWRITE_TEXT_METRICS metrics = {0};
    DX::ThrowIfFailed(
        m_textLayout->GetMetrics(&metrics)
    );

    m_overlayWidth = m_padding * 3.0f + m_logoSize.width + metrics.width;

    DX::ThrowIfFailed(
        m_deviceResources->GetD2DFactory()->CreateDrawingStateBlock(&m_stateBlock)
    );
}