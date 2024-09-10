bool CaptureBuffer::present(const QVideoFrame &frame) {

    QList<QVideoFrame::PixelFormat> formatos = supportedPixelFormats();

    if (!formatos.contains(frame.pixelFormat())) {
        return false;
    } else {

        // Copia del frame
        QVideoFrame f(frame);
        // Permitir copiar del buffer
        f.map(QAbstractVideoBuffer::ReadOnly);
        // Obtener imagen a partir del frame
        QImage imagen = QImage(f.bits(),
                               f.width(),
                               f.height(),
                               f.bytesPerLine(),
                               QVideoFrame::imageFormatFromPixelFormat(f.pixelFormat()));
        // Bloquear buffer
        f.unmap();
        // Emitir señal
        emit transmitirImagen(imagen);

        return true;
    }
}