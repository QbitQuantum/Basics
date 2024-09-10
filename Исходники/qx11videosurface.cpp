bool QX11VideoSurface::start(const QVideoSurfaceFormat &format)
{
    if (m_image)
        XFree(m_image);

    int xvFormatId = 0;
    for (int i = 0; i < m_supportedPixelFormats.count(); ++i) {
        if (m_supportedPixelFormats.at(i) == format.pixelFormat()) {
            xvFormatId = m_formatIds.at(i);
            break;
        }
    }

    if (xvFormatId == 0) {
        setError(UnsupportedFormatError);
    } else {
        XvImage *image = XvCreateImage(
                QX11Info::display(),
                m_portId,
                xvFormatId,
                0,
                format.frameWidth(),
                format.frameHeight());

        if (!image) {
            setError(ResourceError);
        } else {
            m_viewport = format.viewport();
            m_image = image;

            QVideoSurfaceFormat newFormat = format;
            newFormat.setProperty("portId", QVariant(quint64(m_portId)));
            newFormat.setProperty("xvFormatId", xvFormatId);
            newFormat.setProperty("dataSize", image->data_size);

            return QAbstractVideoSurface::start(newFormat);
        }
    }

    if (m_image) {
        m_image = 0;

        QAbstractVideoSurface::stop();
    }

    return false;
}