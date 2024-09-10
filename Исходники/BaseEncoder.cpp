STDMETHODIMP BaseFrameEncode::Commit()
{
    HRESULT result = S_OK;
    
    IWICBitmapScaler *scaler = NULL;
    IWICFormatConverter *formatConverter = NULL;

    result = S_OK;

    // Create a scaler to match the requested width and height
    if (SUCCEEDED(result))
        {
        result = factory->CreateBitmapScaler(&scaler);
    }

    if (SUCCEEDED(result))
    {
        result = scaler->Initialize(destSource, destWidth, destHeight, WICBitmapInterpolationModeFant);
    }

    // Create a format converter to output into the proper format
    if (SUCCEEDED(result))
    {
        result = factory->CreateFormatConverter(&formatConverter);
    }
    if (SUCCEEDED(result))
    {
        result = formatConverter->Initialize(scaler, destPixelFormat, WICBitmapDitherTypeErrorDiffusion,
            destPalette, 50.0, WICBitmapPaletteTypeCustom);
    }

    // Cleanup
    if (formatConverter)
    {
        destSource->Release();
        destSource = formatConverter;
    }    
    return result;
}