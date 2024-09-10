static HRESULT WINAPI IcnsEncoder_Commit(IWICBitmapEncoder *iface)
{
    IcnsEncoder *This = impl_from_IWICBitmapEncoder(iface);
    size_t buffer_size;
    HRESULT hr = S_OK;
    ULONG byteswritten;

    TRACE("(%p)\n", iface);

    EnterCriticalSection(&This->lock);

    if (!This->any_frame_committed || This->outstanding_commits > 0 || This->committed)
    {
        hr = WINCODEC_ERR_WRONGSTATE;
        goto end;
    }

    buffer_size = GetHandleSize((Handle)This->icns_family);
    hr = IStream_Write(This->stream, *This->icns_family, buffer_size, &byteswritten);
    if (FAILED(hr) || byteswritten != buffer_size)
    {
        WARN("writing file failed, hr = 0x%08X\n", hr);
        hr = E_FAIL;
        goto end;
    }

    This->committed = TRUE;

end:
    LeaveCriticalSection(&This->lock);
    return hr;
}