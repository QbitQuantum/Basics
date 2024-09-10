ComPtr<CGeometricMediaSource> CGeometricMediaSource::CreateInstance()
{
    ComPtr<CGeometricMediaSource> spSource;
    spSource.Attach(new(std::nothrow) CGeometricMediaSource());
    if (!spSource)
    {
        throw ref new OutOfMemoryException();
    }

    spSource->Initialize();

    return spSource;
}