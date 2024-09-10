static jpeg_boolean dest_mgr_empty_output_buffer(j_compress_ptr cinfo)
{
    JpegEncoder *This = encoder_from_compress(cinfo);
    HRESULT hr;
    ULONG byteswritten;

    hr = IStream_Write(This->stream, This->dest_buffer,
        sizeof(This->dest_buffer), &byteswritten);

    if (hr != S_OK || byteswritten == 0)
    {
        ERR("Failed writing data, hr=%x\n", hr);
        return FALSE;
    }

    This->dest_mgr.next_output_byte = This->dest_buffer;
    This->dest_mgr.free_in_buffer = sizeof(This->dest_buffer);
    return TRUE;
}