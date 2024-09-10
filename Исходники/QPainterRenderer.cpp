bool QPainterRenderer::preparePixmap(const VideoFrame &frame)
{
    DPTR_D(QPainterRenderer);
    // already locked in a larger scope of receive()
    QImage::Format imgfmt = frame.imageFormat();
    if (frame.constBits(0)) {
        d.video_frame = frame;
    } else {
        if (imgfmt == QImage::Format_Invalid) {
            d.video_frame = frame.to(VideoFormat::Format_RGB32);
            imgfmt = d.video_frame.imageFormat();
        } else {
            d.video_frame = frame.to(frame.pixelFormat());
        }
    }
    const bool swapRGB = (int)imgfmt < 0;
    if (swapRGB) {
        imgfmt = (QImage::Format)(-imgfmt);
    }
    // DO NOT use frameData().data() because it's temp ptr while d.image does not deep copy the data
    QImage image = QImage((uchar*)d.video_frame.constBits(), d.video_frame.width(), d.video_frame.height(), d.video_frame.bytesPerLine(), imgfmt);
    if (swapRGB)
        image = image.rgbSwapped();
    d.pixmap = QPixmap::fromImage(image);
    //Format_RGB32 is fast. see document
    return true;
}