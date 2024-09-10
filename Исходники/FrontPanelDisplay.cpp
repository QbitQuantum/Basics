void FrontPanelDisplay::SaveWICToFile(_In_z_ const wchar_t *filename, REFGUID guidContainerFormat) const
{
    if (!IsAvailable())
    {
        return;
    }

    if (!filename)
    {
        throw std::invalid_argument("Invalid filename");
    }

    auto pWIC = _GetWIC();
    if (!pWIC)
    {
        throw std::exception("_GetWIC");
    }

    ComPtr<IWICStream> stream;
    ThrowIfFailed(
        pWIC->CreateStream(stream.GetAddressOf())
    );

    ThrowIfFailed(
        stream->InitializeFromFilename(filename, GENERIC_WRITE)
    );

    auto_delete_file_wic delonfail(stream, filename);

    ComPtr<IWICBitmapEncoder> encoder;
    ThrowIfFailed(
        pWIC->CreateEncoder(guidContainerFormat, nullptr, encoder.GetAddressOf())
    );

    ThrowIfFailed(
        encoder->Initialize(stream.Get(), WICBitmapEncoderNoCache)
    );

    ComPtr<IWICBitmapFrameEncode> frame;
    ThrowIfFailed(
        encoder->CreateNewFrame(frame.GetAddressOf(), nullptr)
    );

    ThrowIfFailed(
        frame->Initialize(nullptr)
    );

    ThrowIfFailed(
        frame->SetSize(m_displayWidth, m_displayHeight)
    );

    ThrowIfFailed(
        frame->SetResolution(72, 72)
    );

    WICPixelFormatGUID targetGuid = GUID_WICPixelFormat8bppGray;
    ThrowIfFailed(
        frame->SetPixelFormat(&targetGuid)
    );

    UINT rowPitch = m_displayWidth;
    UINT imageSize = m_displayWidth * m_displayHeight;

    if (memcmp(&targetGuid, &GUID_WICPixelFormat8bppGray, sizeof(WICPixelFormatGUID)) != 0)
    {
        // Conversion required to write
        ComPtr<IWICBitmap> source;
        ThrowIfFailed(
            pWIC->CreateBitmapFromMemory(m_displayWidth, m_displayHeight, GUID_WICPixelFormat8bppGray,
                rowPitch, imageSize,
                reinterpret_cast<BYTE*>(m_buffer.get()), source.GetAddressOf())
        );

        ComPtr<IWICFormatConverter> FC;
        ThrowIfFailed(
            pWIC->CreateFormatConverter(FC.GetAddressOf())
        );

        BOOL canConvert = FALSE;
        ThrowIfFailed(
            FC->CanConvert(GUID_WICPixelFormat8bppGray, targetGuid, &canConvert)
        );

        if (!canConvert)
        {
            throw std::exception("CanConvert");
        }

        ThrowIfFailed(
            FC->Initialize(source.Get(), targetGuid, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeFixedGray16)
        );

        WICRect rect = { 0, 0, static_cast<INT>(m_displayWidth), static_cast<INT>(m_displayHeight) };
        ThrowIfFailed(
            frame->WriteSource(FC.Get(), &rect)
        );
    }
    else
    {
        ThrowIfFailed(
            frame->WritePixels(
                m_displayHeight,
                rowPitch, imageSize,
                reinterpret_cast<BYTE*>(m_buffer.get()))
        );
    }

    ThrowIfFailed(
        frame->Commit()
    );

    ThrowIfFailed(
        encoder->Commit()
    );

    delonfail.clear();
}