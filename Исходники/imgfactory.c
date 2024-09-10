HRESULT WINAPI WICCreateBitmapFromSection(UINT width, UINT height,
        REFWICPixelFormatGUID format, HANDLE section,
        UINT stride, UINT offset, IWICBitmap **bitmap)
{
    TRACE("%u,%u,%s,%p,%u,%u,%p\n", width, height, debugstr_guid(format),
        section, stride, offset, bitmap);

    return WICCreateBitmapFromSectionEx(width, height, format, section,
        stride, offset, WICSectionAccessLevelRead, bitmap);
}