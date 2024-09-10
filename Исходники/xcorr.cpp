void FrameProcessor::processFrame(QVideoFrame frame )
{
    double tot = 0;

    do {

        if (!frame.map(QAbstractVideoBuffer::ReadOnly)){
            qDebug() << "Unable to map frame!";
            break;
        }

        if (frame.pixelFormat() == QVideoFrame::Format_YUV420P ||
            frame.pixelFormat() == QVideoFrame::Format_NV12) {
            // Process YUV data
            uchar *b = frame.bits();
            for (int y = 0; y < frame.height(); y++) {
                uchar *lastPixel = b + frame.width();
                for (uchar *curPixel = b; curPixel < lastPixel; curPixel++){
                    if(*curPixel != 16 ) tot += *curPixel;
                    //histogram[(*curPixel * levels) >> 8] += 1.0;
                }
                b += frame.bytesPerLine();
            }
        } else {
            QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
            if (imageFormat != QImage::Format_Invalid) {
                // Process RGB data
                QImage image(frame.bits(), frame.width(), frame.height(), imageFormat);
                image = image.convertToFormat(QImage::Format_RGB32);

                const QRgb* b = (const QRgb*)image.bits();
                for (int y = 0; y < image.height(); y++) {
                    const QRgb *lastPixel = b + frame.width();
                    for (const QRgb *curPixel = b; curPixel < lastPixel; curPixel++){
                        //histogram[(qGray(*curPixel) * levels) >> 8] += 1.0;
                        if(*curPixel != 16 ) tot+= qGray(*curPixel);
                    }
                    b = (const QRgb*)((uchar*)b + image.bytesPerLine());
                }
            }
        }

        frame.unmap();
    } while (false);

    // Compute mean
    int mean = tot/frame.width()/frame.height();
    int timestamp = frame.startTime()/1000;
    emit dataReady(timestamp,mean);
}