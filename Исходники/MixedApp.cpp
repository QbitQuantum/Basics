std::unique_ptr<uint8_t[]> MixedApp::LoadImageFile(const wchar_t* filename, uint32_t* width, uint32_t* height)
{
    ComPtr<IWICBitmapDecoder> decoder;
    HRESULT hr = WicFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
    CHECKHR(hr, L"Failed to create image decoder for file. %s, hr = 0x%08x.", filename, hr);

    ComPtr<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame(0, &frame);
    CHECKHR(hr, L"Failed to decode image frame. hr = 0x%08x.", hr);

    ComPtr<IWICFormatConverter> converter;
    hr = WicFactory->CreateFormatConverter(&converter);
    CHECKHR(hr, L"Failed to create image format converter. hr = 0x%08x.", hr);

    hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom);
    CHECKHR(hr, L"Failed to initialize image format converter. hr = 0x%08x.", hr);

    frame->GetSize(width, height);
    std::unique_ptr<uint8_t[]> pixels(new uint8_t[(*width) * (*height) * sizeof(uint32_t)]);
    hr = converter->CopyPixels(nullptr, sizeof(uint32_t) * (*width), sizeof(uint32_t) * (*width) * (*height), pixels.get());
    CHECKHR(hr, L"Failed to decode image pixels. hr = 0x%08x.", hr);

    return pixels;
}