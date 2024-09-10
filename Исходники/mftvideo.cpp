QVideoSurfaceFormat MFTransform::videoFormatForMFMediaType(IMFMediaType *mediaType, int *bytesPerLine)
{
    UINT32 stride;
    if (FAILED(mediaType->GetUINT32(MF_MT_DEFAULT_STRIDE, &stride))) {
        *bytesPerLine = 0;
        return QVideoSurfaceFormat();
    }

    *bytesPerLine = (int)stride;

    QSize size;
    UINT32 width, height;
    if (FAILED(MFGetAttributeSize(mediaType, MF_MT_FRAME_SIZE, &width, &height)))
        return QVideoSurfaceFormat();

    size.setWidth(width);
    size.setHeight(height);

    GUID subtype = GUID_NULL;
    if (FAILED(mediaType->GetGUID(MF_MT_SUBTYPE, &subtype)))
        return QVideoSurfaceFormat();

    QVideoFrame::PixelFormat pixelFormat = formatFromSubtype(subtype);
    QVideoSurfaceFormat format(size, pixelFormat);

    UINT32 num, den;
    if (SUCCEEDED(MFGetAttributeRatio(mediaType, MF_MT_PIXEL_ASPECT_RATIO, &num, &den))) {
        format.setPixelAspectRatio(num, den);
    }
    if (SUCCEEDED(MFGetAttributeRatio(mediaType, MF_MT_FRAME_RATE, &num, &den))) {
        format.setFrameRate(qreal(num)/den);
    }

    return format;
}