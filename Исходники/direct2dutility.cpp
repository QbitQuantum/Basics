//
// Creates a Direct2D bitmap from the specified
// resource name and type.
//
HRESULT Direct2DUtility::LoadBitmapFromResource(
    ID2D1RenderTarget *renderTarget,
    const wchar_t *resourceName,
    const wchar_t *resourceType,
    unsigned int destinationWidth,
    unsigned int destinationHeight,
    ID2D1Bitmap **bitmap
    )
{
    HRESULT hr = S_OK;
    ComPtr<IWICImagingFactory> wicFactory;
    ComPtr<IWICBitmapDecoder> decoder;
    ComPtr<IWICBitmapFrameDecode> bitmapSource;
    ComPtr<IWICStream> stream;
    ComPtr<IWICFormatConverter> formatConverter;
    ComPtr<IWICBitmapScaler> scaler;

    HRSRC imageResHandle = nullptr;
    HGLOBAL imageResDataHandle = nullptr;
    void *imageFile = nullptr;
    unsigned long imageFileSize = 0;

    // Locate the resource.
    imageResHandle = ::FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);

    hr = imageResHandle ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
        // Load the resource.
        imageResDataHandle = ::LoadResource(HINST_THISCOMPONENT, imageResHandle);

        hr = imageResDataHandle ? S_OK : E_FAIL;
    }
    if (SUCCEEDED(hr))
    {
        // Lock it to get a system memory pointer.
        imageFile = ::LockResource(imageResDataHandle);

        hr = imageFile ? S_OK : E_FAIL;
    }
    if (SUCCEEDED(hr))
    {
        // Calculate the size.
        imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

        hr = imageFileSize ? S_OK : E_FAIL;
    }

    if (SUCCEEDED(hr))
    {
        hr = GetWICFactory(&wicFactory);
    }

    if (SUCCEEDED(hr))
    {
        // Create a WIC stream to map onto the memory.
        hr = wicFactory->CreateStream(&stream);
    }

    if (SUCCEEDED(hr))
    {
        // Initialize the stream with the memory pointer and size.
        hr = stream->InitializeFromMemory(
            reinterpret_cast<unsigned char*>(imageFile),
            imageFileSize
            );
    }

    if (SUCCEEDED(hr))
    {
        // Create a decoder for the stream.
        hr = wicFactory->CreateDecoderFromStream(
            stream,
            nullptr,
            WICDecodeMetadataCacheOnLoad,
            &decoder
            );
    }

    if (SUCCEEDED(hr))
    {
        // Create the initial frame.
        hr = decoder->GetFrame(0, &bitmapSource);
    }

    if (SUCCEEDED(hr))
    {
        // Convert the image format to 32bppPBGRA
        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
        hr = wicFactory->CreateFormatConverter(&formatConverter);
    }

    if (SUCCEEDED(hr))
    {
        // If a new width or height was specified, create an
        // IWICBitmapScaler and use it to resize the image.
        if (destinationWidth != 0 || destinationHeight != 0)
        {
            unsigned int originalWidth, originalHeight;
            hr = bitmapSource->GetSize(&originalWidth, &originalHeight);
            if (SUCCEEDED(hr))
            {
                if (destinationWidth == 0)
                {
                    float scalar = static_cast<float>(destinationHeight) / static_cast<float>(originalHeight);
                    destinationWidth = static_cast<unsigned int>(scalar * static_cast<float>(originalWidth));
                }
                else if (destinationHeight == 0)
                {
                    float scalar = static_cast<float>(destinationWidth) / static_cast<float>(originalWidth);
                    destinationHeight = static_cast<unsigned int>(scalar * static_cast<float>(originalHeight));
                }

                hr = wicFactory->CreateBitmapScaler(&scaler);
                if (SUCCEEDED(hr))
                {
                    hr = scaler->Initialize(
                        bitmapSource,
                        destinationWidth,
                        destinationHeight,
                        WICBitmapInterpolationModeCubic
                        );
                    if (SUCCEEDED(hr))
                    {
                        hr = formatConverter->Initialize(
                            scaler,
                            GUID_WICPixelFormat32bppPBGRA,
                            WICBitmapDitherTypeNone,
                            nullptr,
                            0.f,
                            WICBitmapPaletteTypeMedianCut
                            );
                    }
                }
            }
        }
        else
        {
            hr = formatConverter->Initialize(
                bitmapSource,
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.f,
                WICBitmapPaletteTypeMedianCut
                );
        }
    }

    if (SUCCEEDED(hr))
    {
        //create a Direct2D bitmap from the WIC bitmap.
        hr = renderTarget->CreateBitmapFromWicBitmap(
            formatConverter,
            nullptr,
            bitmap
            );
    }

    return hr;
}