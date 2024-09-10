void MediaPlayerPrivateMediaFoundation::seekDouble(double time)
{
    const double tenMegahertz = 10000000;
    PROPVARIANT propVariant;
    PropVariantInit(&propVariant);
    propVariant.vt = VT_I8;
    propVariant.hVal.QuadPart = static_cast<__int64>(time * tenMegahertz);
    
    HRESULT hr = m_mediaSession->Start(&GUID_NULL, &propVariant);
    ASSERT(SUCCEEDED(hr));
    PropVariantClear(&propVariant);
}