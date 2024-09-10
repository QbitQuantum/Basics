void QXcbShmImage::preparePaint(const QRegion &region)
{
    // to prevent X from reading from the image region while we're writing to it
    if (m_dirty.intersects(region)) {
        connection()->sync();
        m_dirty = QRegion();
    }
}