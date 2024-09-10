void PageRenderer::CreateDeviceIndependentResources()
{
    DirectXBase::CreateDeviceIndependentResources();

    // Create a DirectWrite text format object for the sample's content.
    DX::ThrowIfFailed(
        m_dwriteFactory->CreateTextFormat(
            L"Segoe UI",
            nullptr,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            40.0f,
            L"en-us", // locale
            &m_textFormat
            )
        );

    // Align the text horizontally.
    DX::ThrowIfFailed(
        m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)
        );

    // Center the text vertically.
    DX::ThrowIfFailed(
        m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)
        );

    // Create a DirectWrite text format object for status messages.
    DX::ThrowIfFailed(
        m_dwriteFactory->CreateTextFormat(
            L"Segoe UI",
            nullptr,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            20.0f,
            L"en-us", // locale
            &m_messageFormat
            )
        );

    // Center the text horizontally.
    DX::ThrowIfFailed(
        m_messageFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER)
        );

    // Center the text vertically.
    DX::ThrowIfFailed(
        m_messageFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER)
        );

    // Load the source bitmap file into a WIC bitmap source.
    ComPtr<IWICBitmapDecoder> decoder;
    DX::ThrowIfFailed(
        m_wicFactory->CreateDecoderFromFilename(
            L"test.jpg",
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

    DX::ThrowIfFailed(
        m_wicFactory->CreateFormatConverter(&m_wicConvertedSource)
        );

    DX::ThrowIfFailed(
        m_wicConvertedSource->Initialize(
            frame.Get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0f,
            WICBitmapPaletteTypeCustom  // Premultiplied BGRA has no paletting, so this is ignored.
            )
        );

    // Load the source color profile.
    DX::ThrowIfFailed(
        m_wicFactory->CreateColorContext(&m_wicColorContext)
        );

    DX::ThrowIfFailed(
        m_wicColorContext->InitializeFromFilename(L"profile.icm")
        );

    // Create another BitmapSource effect, for printing only.
    // We first encode the WIC bitmap source and the WIC color context to an
    // in-memory stream, then create a new WIC bitmap source from that stream,
    // and finally create a BitmapSource effect based on the newly created WIC
    // bitmap source. By doing so, we pass the original WIC bitmap source and
    // the WIC color context (both embedded in that stream) directly to the
    // print path, and achieve better performance and fidelity with delayed
    // color conversion.

    // Step 1: Encode both the WIC bitmap source and the color context to an
    // in-memory stream.
    auto memoryStream = ref new InMemoryRandomAccessStream();
    ComPtr<IStream> stream;
    DX::ThrowIfFailed(
        CreateStreamOverRandomAccessStream(memoryStream, IID_PPV_ARGS(&stream))
        );

    ComPtr<IWICBitmapEncoder> wicBitmapEncoder;
    DX::ThrowIfFailed(
        m_wicFactory->CreateEncoder(
            GUID_ContainerFormatPng,    // Encode as PNG.
            nullptr,    // No preferred codec vendor.
            &wicBitmapEncoder
            )
        );

    DX::ThrowIfFailed(
        wicBitmapEncoder->Initialize(
            stream.Get(),
            WICBitmapEncoderNoCache
            )
        );

    ComPtr<IWICBitmapFrameEncode> wicFrameEncode;
    DX::ThrowIfFailed(
        wicBitmapEncoder->CreateNewFrame(
            &wicFrameEncode,
            nullptr     // No encoder options.
            )
        );

    DX::ThrowIfFailed(
        wicFrameEncode->Initialize(nullptr)
        );

    // Set color context to the frame.
    IWICColorContext* contexts[1];
    contexts[0] = m_wicColorContext.Get();
    DX::ThrowIfFailed(
        wicFrameEncode->SetColorContexts(1, contexts)
        );

    DX::ThrowIfFailed(
        wicFrameEncode->WriteSource(
            m_wicConvertedSource.Get(),
            nullptr     // Write the whole bitmap.
            )
        );

    DX::ThrowIfFailed(
        wicFrameEncode->Commit()
        );

    DX::ThrowIfFailed(
        wicBitmapEncoder->Commit()
        );

    // Step 2: Decode the newly created image stream.
    ComPtr<IWICBitmapDecoder> bitmapDecoder;
    DX::ThrowIfFailed(
        m_wicFactory->CreateDecoderFromStream(
            stream.Get(),
            nullptr,    // No preferred codec vendor.
            WICDecodeMetadataCacheOnLoad,
            &bitmapDecoder
            )
        );

    // Get the initial frame as the new WIC bitmap source.
    DX::ThrowIfFailed(
        bitmapDecoder->GetFrame(0, &m_profiledWicBitmap)
        );
}