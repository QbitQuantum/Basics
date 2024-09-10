void PiqslImageView::imageUpdated(int x, int y, int w, int h)
{
    int zoom = lround(m_zoom);
    update(lround(m_tlPos.x()) + zoom*x, lround(m_tlPos.y()) + zoom*y,
            zoom*w, zoom*h);
}