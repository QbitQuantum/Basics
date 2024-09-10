void WVuMeter::setPixmaps(PixmapSource source,
                          bool bHorizontal, Paintable::DrawMode mode) {
    m_pPixmapVu = WPixmapStore::getPaintable(source, mode);
    if (m_pPixmapVu.isNull() || m_pPixmapVu->isNull()) {
        qDebug() << "WVuMeter: Error loading vu pixmap" << source.getPath();
    } else {
        m_bHorizontal = bHorizontal;
        if (m_bHorizontal) {
            m_iPixmapLength = m_pPixmapVu->width();
        } else {
            m_iPixmapLength = m_pPixmapVu->height();
        }
    }
}