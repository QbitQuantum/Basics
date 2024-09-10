bool QAbstractVideoSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    return supportedPixelFormats(format.handleType()).contains(format.pixelFormat());
}