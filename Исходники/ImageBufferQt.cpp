String ImageBuffer::toDataURL(const String& mimeType, const double* quality, CoordinateSystem) const
{
    ASSERT(MIMETypeRegistry::isSupportedImageMIMETypeForEncoding(mimeType));

    // QImageWriter does not support mimetypes. It does support Qt image formats (png,
    // gif, jpeg..., xpm) so skip the image/ to get the Qt image format used to encode
    // the m_pixmap image.

    RefPtr<Image> image = copyImage(DontCopyBackingStore);
    QByteArray data;
    if (!encodeImage(*image->nativeImageForCurrentFrame(), mimeType.substring(sizeof "image"), quality, data))
        return "data:,";

    return "data:" + mimeType + ";base64," + data.toBase64().data();
}