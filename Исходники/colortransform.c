static HRESULT WINAPI ColorTransform_Initialize(IWICColorTransform *iface,
    IWICBitmapSource *pIBitmapSource, IWICColorContext *pIContextSource,
    IWICColorContext *pIContextDest, REFWICPixelFormatGUID pixelFmtDest)
{
    ColorTransform *This = impl_from_IWICColorTransform(iface);
    IWICBitmapSource *dst;
    HRESULT hr;

    TRACE("(%p,%p,%p,%p,%s)\n", iface, pIBitmapSource, pIContextSource,
          pIContextDest, debugstr_guid(pixelFmtDest));

    FIXME("ignoring color contexts\n");

    hr = WICConvertBitmapSource(pixelFmtDest, pIBitmapSource, &dst);
    if (FAILED(hr)) return hr;

    if (This->dst) IWICBitmapSource_Release(This->dst);
    This->dst = dst;
    return S_OK;
}