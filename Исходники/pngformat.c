static void user_write_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
    PngEncoder *This = ppng_get_io_ptr(png_ptr);
    HRESULT hr;
    ULONG byteswritten;

    hr = IStream_Write(This->stream, data, length, &byteswritten);
    if (FAILED(hr) || byteswritten != length)
    {
        ppng_error(png_ptr, "failed writing data");
    }
}