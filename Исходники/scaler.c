static HRESULT WINAPI BitmapScaler_Initialize(IWICBitmapScaler *iface,
    IWICBitmapSource *pISource, UINT uiWidth, UINT uiHeight,
    WICBitmapInterpolationMode mode)
{
    BitmapScaler *This = impl_from_IWICBitmapScaler(iface);
    HRESULT hr;
    GUID src_pixelformat;

    TRACE("(%p,%p,%u,%u,%u)\n", iface, pISource, uiWidth, uiHeight, mode);

    EnterCriticalSection(&This->lock);

    if (This->source)
    {
        hr = WINCODEC_ERR_WRONGSTATE;
        goto end;
    }

    This->width = uiWidth;
    This->height = uiHeight;
    This->mode = mode;

    hr = IWICBitmapSource_GetSize(pISource, &This->src_width, &This->src_height);

    if (SUCCEEDED(hr))
        hr = IWICBitmapSource_GetPixelFormat(pISource, &src_pixelformat);

    if (SUCCEEDED(hr))
    {
        hr = get_pixelformat_bpp(&src_pixelformat, &This->bpp);
    }

    if (SUCCEEDED(hr))
    {
        switch (mode)
        {
        default:
            FIXME("unsupported mode %i\n", mode);
            /* fall-through */
        case WICBitmapInterpolationModeNearestNeighbor:
            if ((This->bpp % 8) == 0)
            {
                IWICBitmapSource_AddRef(pISource);
                This->source = pISource;
            }
            else
            {
                hr = WICConvertBitmapSource(&GUID_WICPixelFormat32bppBGRA,
                    pISource, &This->source);
                This->bpp = 32;
            }
            This->fn_get_required_source_rect = NearestNeighbor_GetRequiredSourceRect;
            This->fn_copy_scanline = NearestNeighbor_CopyScanline;
            break;
        }
    }

end:
    LeaveCriticalSection(&This->lock);

    return hr;
}