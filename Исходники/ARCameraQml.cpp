bool VideoSurface_ForQQuickItem::start(const QVideoSurfaceFormat& format)
{
    if (!supportedPixelFormats(format.handleType()).contains(format.pixelFormat())) {
        qDebug() << format.handleType() << " " << format.pixelFormat() << " - format is not supported.";
        return false;
    }
    return QAbstractVideoSurface::start(format);
}