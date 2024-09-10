void QPainterFilterContext::initializeOnFrame(VideoFrame *vframe)
{
    if (!vframe) {
        if (!painter) {
            painter = new QPainter(); //warning: more than 1 painter on 1 device
        }
        if (!paint_device) {
            paint_device = painter->device();
        }
        if (!paint_device && !painter->isActive()) {
            qWarning("No paint device and painter is not active. No painting!");
            return;
        }
        if (!painter->isActive())
            painter->begin(paint_device);
        return;
    }
    VideoFormat format = vframe->format();
    if (!format.isValid()) {
        qWarning("Not a valid format");
        return;
    }
    if (format.imageFormat() == QImage::Format_Invalid) {
        format.setPixelFormat(VideoFormat::Format_RGB32);
        if (!cvt) {
            cvt = new VideoFrameConverter();
        }
        *vframe = cvt->convert(*vframe, format);
    }
    if (paint_device) {
        if (painter && painter->isActive()) {
            painter->end(); //destroy a paint device that is being painted is not allowed!
        }
        delete paint_device;
        paint_device = 0;
    }
    Q_ASSERT(video_width > 0 && video_height > 0);
    // direct draw on frame data, so use VideoFrame::constBits()
    paint_device = new QImage((uchar*)vframe->constBits(0), video_width, video_height, vframe->bytesPerLine(0), format.imageFormat());
    if (!painter)
        painter = new QPainter();
    own_painter = true;
    own_paint_device = true; //TODO: what about renderer is not a widget?
    painter->begin((QImage*)paint_device);
}