void WSliderComposed::setHandlePixmap(bool bHorizontal, PixmapSource sourceHandle) {
    m_bHorizontal = bHorizontal;
    m_pHandle = WPixmapStore::getPaintable(sourceHandle,
                                           Paintable::STRETCH);
    if (!m_pHandle) {
        qDebug() << "WSliderComposed: Error loading handle pixmap:" << sourceHandle.getPath();
    } else {
        m_iHandleLength = m_bHorizontal ?
                m_pHandle->width() : m_pHandle->height();

        // Value is unused in WSliderComposed.
        onConnectedControlChanged(getControlParameter(), 0);
        update();
    }
}