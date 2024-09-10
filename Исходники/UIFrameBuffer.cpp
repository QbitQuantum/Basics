STDMETHODIMP UIFrameBuffer::COMGETTER(PixelFormat) (ULONG *puPixelFormat)
{
    if (!puPixelFormat)
        return E_POINTER;
    *puPixelFormat = pixelFormat();
    return S_OK;
}