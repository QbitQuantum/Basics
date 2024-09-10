bool MyVideoSurface::start(const QVideoSurfaceFormat &format)
{
    QImage::Format imageFormat =
        QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());

    if (imageFormat == QImage::Format_Invalid)
        imageFormat = QImage::Format_RGB32;

    const QSize frameSize = format.frameSize();

    if ((imageFormat != QImage::Format_Invalid) && !frameSize.isEmpty()) {
        QAbstractVideoSurface::start(format);

        emit frameSizeChanged(frameSize);

        return true;
    }

    return false;
}