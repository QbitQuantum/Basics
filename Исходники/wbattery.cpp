void WBattery::setPixmap(PaintablePointer* ppPixmap, const PixmapSource& source,
                         Paintable::DrawMode mode) {
    PaintablePointer pPixmap = WPixmapStore::getPaintable(source, mode);
    if (pPixmap.isNull() || pPixmap->isNull()) {
        qDebug() << this << "Error loading pixmap:" << source.getPath();
    } else {
        *ppPixmap = pPixmap;
        setFixedSize(pPixmap->size());
    }
}