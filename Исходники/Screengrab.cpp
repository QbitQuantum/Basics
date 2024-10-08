_Use_decl_annotations_
HRESULT DirectX::SaveWICTextureToFile(
    ID3D11DeviceContext* pContext,
    ID3D11Resource* pSource,
    REFGUID guidContainerFormat,
    const wchar_t* fileName,
    const GUID* targetFormat,
    std::function<void(IPropertyBag2*)> setCustomProps)
{
    if (!fileName)
        return E_INVALIDARG;

    D3D11_TEXTURE2D_DESC desc = {};
    ComPtr<ID3D11Texture2D> pStaging;
    HRESULT hr = CaptureTexture(pContext, pSource, desc, pStaging);
    if (FAILED(hr))
        return hr;

    // Determine source format's WIC equivalent
    WICPixelFormatGUID pfGuid;
    bool sRGB = false;
    switch (desc.Format)
    {
        case DXGI_FORMAT_R32G32B32A32_FLOAT:            pfGuid = GUID_WICPixelFormat128bppRGBAFloat; break;
        case DXGI_FORMAT_R16G16B16A16_FLOAT:            pfGuid = GUID_WICPixelFormat64bppRGBAHalf; break;
        case DXGI_FORMAT_R16G16B16A16_UNORM:            pfGuid = GUID_WICPixelFormat64bppRGBA; break;
        case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:    pfGuid = GUID_WICPixelFormat32bppRGBA1010102XR; break; // DXGI 1.1
        case DXGI_FORMAT_R10G10B10A2_UNORM:             pfGuid = GUID_WICPixelFormat32bppRGBA1010102; break;
        case DXGI_FORMAT_B5G5R5A1_UNORM:                pfGuid = GUID_WICPixelFormat16bppBGRA5551; break;
        case DXGI_FORMAT_B5G6R5_UNORM:                  pfGuid = GUID_WICPixelFormat16bppBGR565; break;
        case DXGI_FORMAT_R32_FLOAT:                     pfGuid = GUID_WICPixelFormat32bppGrayFloat; break;
        case DXGI_FORMAT_R16_FLOAT:                     pfGuid = GUID_WICPixelFormat16bppGrayHalf; break;
        case DXGI_FORMAT_R16_UNORM:                     pfGuid = GUID_WICPixelFormat16bppGray; break;
        case DXGI_FORMAT_R8_UNORM:                      pfGuid = GUID_WICPixelFormat8bppGray; break;
        case DXGI_FORMAT_A8_UNORM:                      pfGuid = GUID_WICPixelFormat8bppAlpha; break;

        case DXGI_FORMAT_R8G8B8A8_UNORM:
            pfGuid = GUID_WICPixelFormat32bppRGBA;
            break;

        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
            pfGuid = GUID_WICPixelFormat32bppRGBA;
            sRGB = true;
            break;

        case DXGI_FORMAT_B8G8R8A8_UNORM: // DXGI 1.1
            pfGuid = GUID_WICPixelFormat32bppBGRA;
            break;

        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB: // DXGI 1.1
            pfGuid = GUID_WICPixelFormat32bppBGRA;
            sRGB = true;
            break;

        case DXGI_FORMAT_B8G8R8X8_UNORM: // DXGI 1.1
            pfGuid = GUID_WICPixelFormat32bppBGR;
            break;

        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB: // DXGI 1.1
            pfGuid = GUID_WICPixelFormat32bppBGR;
            sRGB = true;
            break;

        default:
            return HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED);
    }

    auto pWIC = _GetWIC();
    if (!pWIC)
        return E_NOINTERFACE;

    ComPtr<IWICStream> stream;
    hr = pWIC->CreateStream(stream.GetAddressOf());
    if (FAILED(hr))
        return hr;

    hr = stream->InitializeFromFilename(fileName, GENERIC_WRITE);
    if (FAILED(hr))
        return hr;

    auto_delete_file_wic delonfail(stream, fileName);

    ComPtr<IWICBitmapEncoder> encoder;
    hr = pWIC->CreateEncoder(guidContainerFormat, 0, encoder.GetAddressOf());
    if (FAILED(hr))
        return hr;

    hr = encoder->Initialize(stream.Get(), WICBitmapEncoderNoCache);
    if (FAILED(hr))
        return hr;

    ComPtr<IWICBitmapFrameEncode> frame;
    ComPtr<IPropertyBag2> props;
    hr = encoder->CreateNewFrame(frame.GetAddressOf(), props.GetAddressOf());
    if (FAILED(hr))
        return hr;

    if (targetFormat && memcmp(&guidContainerFormat, &GUID_ContainerFormatBmp, sizeof(WICPixelFormatGUID)) == 0 && _IsWIC2())
    {
        // Opt-in to the WIC2 support for writing 32-bit Windows BMP files with an alpha channel
        PROPBAG2 option = {};
        option.pstrName = const_cast<wchar_t*>(L"EnableV5Header32bppBGRA");

        VARIANT varValue;
        varValue.vt = VT_BOOL;
        varValue.boolVal = VARIANT_TRUE;
        (void)props->Write(1, &option, &varValue);
    }

    if (setCustomProps)
    {
        setCustomProps(props.Get());
    }

    hr = frame->Initialize(props.Get());
    if (FAILED(hr))
        return hr;

    hr = frame->SetSize(desc.Width, desc.Height);
    if (FAILED(hr))
        return hr;

    hr = frame->SetResolution(72, 72);
    if (FAILED(hr))
        return hr;

    // Pick a target format
    WICPixelFormatGUID targetGuid;
    if (targetFormat)
    {
        targetGuid = *targetFormat;
    }
    else
    {
        // Screenshots don't typically include the alpha channel of the render target
        switch (desc.Format)
        {
        #if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
            case DXGI_FORMAT_R32G32B32A32_FLOAT:
            case DXGI_FORMAT_R16G16B16A16_FLOAT:
                if (_IsWIC2())
                {
                    targetGuid = GUID_WICPixelFormat96bppRGBFloat;
                }
                else
                {
                    targetGuid = GUID_WICPixelFormat24bppBGR;
                }
                break;
            #endif

            case DXGI_FORMAT_R16G16B16A16_UNORM: targetGuid = GUID_WICPixelFormat48bppBGR; break;
            case DXGI_FORMAT_B5G5R5A1_UNORM:     targetGuid = GUID_WICPixelFormat16bppBGR555; break;
            case DXGI_FORMAT_B5G6R5_UNORM:       targetGuid = GUID_WICPixelFormat16bppBGR565; break;

            case DXGI_FORMAT_R32_FLOAT:
            case DXGI_FORMAT_R16_FLOAT:
            case DXGI_FORMAT_R16_UNORM:
            case DXGI_FORMAT_R8_UNORM:
            case DXGI_FORMAT_A8_UNORM:
                targetGuid = GUID_WICPixelFormat8bppGray;
                break;

            default:
                targetGuid = GUID_WICPixelFormat24bppBGR;
                break;
        }
    }

    hr = frame->SetPixelFormat(&targetGuid);
    if (FAILED(hr))
        return hr;

    if (targetFormat && memcmp(targetFormat, &targetGuid, sizeof(WICPixelFormatGUID)) != 0)
    {
        // Requested output pixel format is not supported by the WIC codec
        return E_FAIL;
    }

    // Encode WIC metadata
    ComPtr<IWICMetadataQueryWriter> metawriter;
    if (SUCCEEDED(frame->GetMetadataQueryWriter(metawriter.GetAddressOf())))
    {
        PROPVARIANT value;
        PropVariantInit(&value);

        value.vt = VT_LPSTR;
        value.pszVal = const_cast<char*>("DirectXTK");

        if (memcmp(&guidContainerFormat, &GUID_ContainerFormatPng, sizeof(GUID)) == 0)
        {
            // Set Software name
            (void)metawriter->SetMetadataByName(L"/tEXt/{str=Software}", &value);

            // Set sRGB chunk
            if (sRGB)
            {
                value.vt = VT_UI1;
                value.bVal = 0;
                (void)metawriter->SetMetadataByName(L"/sRGB/RenderingIntent", &value);
            }
            else
            {
                // add gAMA chunk with gamma 1.0
                value.vt = VT_UI4;
                value.uintVal = 100000; // gama value * 100,000 -- i.e. gamma 1.0
                (void)metawriter->SetMetadataByName(L"/gAMA/ImageGamma", &value);

                // remove sRGB chunk which is added by default.
                (void)metawriter->RemoveMetadataByName(L"/sRGB/RenderingIntent");
            }
        }
    #if defined(_XBOX_ONE) && defined(_TITLE)
        else if (memcmp(&guidContainerFormat, &GUID_ContainerFormatJpeg, sizeof(GUID)) == 0)
        {
            // Set Software name
            (void)metawriter->SetMetadataByName(L"/app1/ifd/{ushort=305}", &value);

            if (sRGB)
            {
                // Set EXIF Colorspace of sRGB
                value.vt = VT_UI2;
                value.uiVal = 1;
                (void)metawriter->SetMetadataByName(L"/app1/ifd/exif/{ushort=40961}", &value);
            }
        }
        else if (memcmp(&guidContainerFormat, &GUID_ContainerFormatTiff, sizeof(GUID)) == 0)
        {
            // Set Software name
            (void)metawriter->SetMetadataByName(L"/ifd/{ushort=305}", &value);

            if (sRGB)
            {
                // Set EXIF Colorspace of sRGB
                value.vt = VT_UI2;
                value.uiVal = 1;
                (void)metawriter->SetMetadataByName(L"/ifd/exif/{ushort=40961}", &value);
            }
        }
    #else
        else
        {
            // Set Software name
            (void)metawriter->SetMetadataByName(L"System.ApplicationName", &value);

            if (sRGB)
            {
                // Set EXIF Colorspace of sRGB
                value.vt = VT_UI2;
                value.uiVal = 1;
                (void)metawriter->SetMetadataByName(L"System.Image.ColorSpace", &value);
            }
        }
    #endif
    }

    D3D11_MAPPED_SUBRESOURCE mapped;
    hr = pContext->Map(pStaging.Get(), 0, D3D11_MAP_READ, 0, &mapped);
    if (FAILED(hr))
        return hr;

    if (memcmp(&targetGuid, &pfGuid, sizeof(WICPixelFormatGUID)) != 0)
    {
        // Conversion required to write
        ComPtr<IWICBitmap> source;
        hr = pWIC->CreateBitmapFromMemory(desc.Width, desc.Height, pfGuid,
                                          mapped.RowPitch, mapped.RowPitch * desc.Height,
                                          static_cast<BYTE*>(mapped.pData), source.GetAddressOf());
        if (FAILED(hr))
        {
            pContext->Unmap(pStaging.Get(), 0);
            return hr;
        }

        ComPtr<IWICFormatConverter> FC;
        hr = pWIC->CreateFormatConverter(FC.GetAddressOf());
        if (FAILED(hr))
        {
            pContext->Unmap(pStaging.Get(), 0);
            return hr;
        }

        BOOL canConvert = FALSE;
        hr = FC->CanConvert(pfGuid, targetGuid, &canConvert);
        if (FAILED(hr) || !canConvert)
        {
            return E_UNEXPECTED;
        }

        hr = FC->Initialize(source.Get(), targetGuid, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeMedianCut);
        if (FAILED(hr))
        {
            pContext->Unmap(pStaging.Get(), 0);
            return hr;
        }

        WICRect rect = { 0, 0, static_cast<INT>(desc.Width), static_cast<INT>(desc.Height) };
        hr = frame->WriteSource(FC.Get(), &rect);
        if (FAILED(hr))
        {
            pContext->Unmap(pStaging.Get(), 0);
            return hr;
        }
    }
    else
    {
        // No conversion required
        hr = frame->WritePixels(desc.Height, mapped.RowPitch, mapped.RowPitch * desc.Height, static_cast<BYTE*>(mapped.pData));
        if (FAILED(hr))
            return hr;
    }

    pContext->Unmap(pStaging.Get(), 0);

    hr = frame->Commit();
    if (FAILED(hr))
        return hr;

    hr = encoder->Commit();
    if (FAILED(hr))
        return hr;

    delonfail.clear();

    return S_OK;
}