bool VideoItem::start(const QVideoSurfaceFormat &format)
{
    if (isFormatSupported(format)) {
        imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
        imageSize = format.frameSize();
        framePainted = true;

        QAbstractVideoSurface::start(format);

        prepareGeometryChange();

        return true;
    } else {
        return false;
    }
}