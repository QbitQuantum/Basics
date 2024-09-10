void MyProbe::processFrame(QVideoFrame frame)
{
    // convert input to cv::mat here
    if (!frame.isValid())
        return;

    if (frame.map(QAbstractVideoBuffer::ReadOnly))
    {
        if (frame.pixelFormat() == QVideoFrame::Format_YUV420P ||
                frame.pixelFormat() == QVideoFrame::Format_NV12 ||
                frame.pixelFormat() == QVideoFrame::Format_NV21)
        {
            if (processMutex.tryLock())
            {
                // extracts gray channel from yuv image
                img = QImage(frame.bits(), frame.width(), frame.height(),
                             frame.bytesPerLine(), QImage::Format_Grayscale8).copy();
                processMutex.unlock();
                emit finished();
            }
        }
        else if (frame.pixelFormat() == QVideoFrame::Format_BGR32)
        {
            if (processMutex.tryLock())
            {
                QImage img_tmp;
                // extracts gray channel from yuv image
                img_tmp = QImage(frame.bits(), frame.width(), frame.height(),
                                 frame.bytesPerLine(), QImage::Format_ARGB32).copy();
                img = img_tmp.convertToFormat(QImage::Format_Grayscale8);
                processMutex.unlock();
                emit finished();
            }
        }
        else
            return;

        frame.unmap();
        return;
    }
    else
        return;
}