MFRatio qt_wmf_getPixelAspectRatio(IMFMediaType *type)
{
    MFRatio ratio = { 0, 0 };
    HRESULT hr = S_OK;

    hr = MFGetAttributeRatio(type, MF_MT_PIXEL_ASPECT_RATIO, (UINT32*)&ratio.Numerator, (UINT32*)&ratio.Denominator);
    if (FAILED(hr)) {
        ratio.Numerator = 1;
        ratio.Denominator = 1;
    }
    return ratio;
}