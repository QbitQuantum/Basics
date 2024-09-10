void FilterClearBorder::applyInPlace(BitmapPtr pBmp)
{
    AVG_ASSERT(pBmp->getPixelFormat() == I8);
    AVG_ASSERT(m_NumPixels < pBmp->getSize().x);
    AVG_ASSERT(m_NumPixels < pBmp->getSize().y);
    if (m_NumPixels != 0) {
        int stride = pBmp->getStride();
        unsigned char * pPixels = pBmp->getPixels();
        IntPoint size = pBmp->getSize();
        IntPoint activeSize = pBmp->getSize()-IntPoint(2*m_NumPixels, 2*m_NumPixels);
        for (int y=m_NumPixels-1; y >= 0; --y) {
            memset(pPixels+stride*y+m_NumPixels, 0, activeSize.x);
        }
        for (int y=size.y-m_NumPixels; y < size.y; ++y) {
            memset(pPixels+stride*y+m_NumPixels, 0, activeSize.x);
        }

        for (int y = 0; y < size.y; ++y) {
            memset(pPixels+stride*y, 0, m_NumPixels);
            memset(pPixels+stride*y+size.x-m_NumPixels, 0, m_NumPixels);
        }
    }
}