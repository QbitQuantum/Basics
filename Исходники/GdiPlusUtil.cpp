CLSID GetEncoderClsid(const WCHAR* format) {
    CLSID null = {0};
    UINT numEncoders, size;
    Status ok = GetImageEncodersSize(&numEncoders, &size);
    if (ok != Ok || 0 == size)
        return null;
    ScopedMem<ImageCodecInfo> codecInfo((ImageCodecInfo*)malloc(size));
    if (!codecInfo)
        return null;
    GetImageEncoders(numEncoders, size, codecInfo);
    for (UINT j = 0; j < numEncoders; j++) {
        if (str::Eq(codecInfo[j].MimeType, format)) {
            return codecInfo[j].Clsid;
        }
    }
    return null;
}