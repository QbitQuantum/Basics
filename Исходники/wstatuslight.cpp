void WStatusLight::setPixmap(int iState, PixmapSource source,
                             Paintable::DrawMode mode) {
    if (iState < 0 || iState >= m_pixmaps.size()) {
        return;
    }

    PaintablePointer pPixmap = WPixmapStore::getPaintable(source, mode);
    if (!pPixmap.isNull() && !pPixmap->isNull()) {
        m_pixmaps[iState] = pPixmap;
        if (mode == Paintable::FIXED) {
            setFixedSize(pPixmap->size());
        }
    } else {
        qDebug() << "WStatusLight: Error loading pixmap:" << source.getPath() << iState;
        m_pixmaps[iState].clear();
    }
}