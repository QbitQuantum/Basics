void ImageSource::processFrame(QVideoFrame frame)
{
  qDebug() << recorder->duration();
  if (sendFrame) {
    if (frame.map(QAbstractVideoBuffer::ReadOnly)) {
      if (frame.pixelFormat() == QVideoFrame::Format_NV21) {
        QImage img(frame.size(), QImage::Format_RGB32);
        qt_convert_NV21_to_ARGB32((uchar*)frame.bits(), (quint32*)img.bits(), frame.width(), frame.height());
        img.save(QString("/sdcard/DCIM/DashCam/Images/%1.jpg").arg(QDateTime::currentDateTime().toString(Qt::ISODate)), "JPG");
        emit newFrame(img);
        qDebug() << "Saving Frame" << counter;
        sendFrame = false;
      }
      frame.unmap();
    }
  }

  if (startRecording) {
    QTimer::singleShot(300000, this, SLOT(newVideo()));
    recorder->setOutputLocation(QUrl::fromLocalFile(QString("/sdcard/DCIM/DashCam/Video/%1.mp4").arg(QDateTime::currentDateTime().toString(Qt::ISODate))));
    recorder->record();

    qDebug() << recorder->supportedResolutions();
    qDebug() << recorder->state();
    qDebug() << recorder->status();
    qDebug() << recorder->error();
    startRecording = false;
  }
}