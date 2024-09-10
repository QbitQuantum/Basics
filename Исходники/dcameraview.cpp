void DCameraView::paint(const QVideoFrame &frame)
{
    QPainter painter(this);

    QImage image(
                frame.bits(),
                frame.width(),
                frame.height(),
                frame.bytesPerLine(),
                QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));

    painter.drawImage(0, 0, image.mirrored(m_mirroredHorizontal, m_mirroredVertical));
}