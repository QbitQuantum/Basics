    void convertAllFrames() {
        mProgressBar->setMaximum(mFrames.length() - 1);
        int count = 0;

        foreach(QVideoFrame frame, mFrames) {
            mProgressBar->setValue(count++);
            QImage image;
            if (frame.pixelFormat() == QVideoFrame::Format_RGB32) {
                // Copy const QVideoFrame to mutable QVideoFrame.
                QVideoFrame nonConstFrame = frame;
                // Unlock for reading the stack frame (increment ref pointer)
                nonConstFrame.map(QAbstractVideoBuffer::ReadOnly);
                // Create new image from the frame bits
                image = QImage(
                        nonConstFrame.bits(),
                        nonConstFrame.width(),
                        nonConstFrame.height(),
                        nonConstFrame.bytesPerLine(),
                        QVideoFrame::imageFormatFromPixelFormat(nonConstFrame.pixelFormat()));
                nonConstFrame.unmap();
            } else {
                image = QImage(frame.size(), QImage::Format_RGB32);
                mFrameConverter->convertFrame(frame, &image);
            }

            QString imgFileName = QString("%1.%2.png").arg(mFileName).arg(++mCount, 2, 10, QChar('0'));
            //QFile file(imgFileName);
            //file.open(QFile::WriteOnly);

            bool saved = image.save(imgFileName, "png");
            if (saved) {
                log->info("File: %1 saved", imgFileName);
            } else {
                log->info("File: %1 not saved", imgFileName);
            }

        }