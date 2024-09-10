void TrackerThread::drawHistogram(BitmapPtr pDestBmp, BitmapPtr pSrcBmp)
{
    HistogramPtr pHist = pSrcBmp->getHistogram(4);
    AVG_ASSERT(pDestBmp->getPixelFormat() == I8);
    // Normalize Histogram to 0..255
    int max1 = 0;
    int max2 = 0;
    for (int i = 0; i < 256; ++i) {
        if ((*pHist)[i] > max1) {
            max2 = max1;
            max1 = (*pHist)[i];
        } else if ((*pHist)[i] > max2) {
            max2 = (*pHist)[i];
        }
    }
    if (max2 == 0) {
        max2= 1;
    }
    for (int i = 0; i < 256; ++i) {
        (*pHist)[i] = int((*pHist)[i]*256.0/max2)+1;
    }
    
    FilterFill<Pixel8>(0).applyInPlace(pDestBmp);
    int stride = pDestBmp->getStride();
    int endRow = 256;
    if (pDestBmp->getSize().y < 256) {
        endRow = pDestBmp->getSize().y;
    }
    int width = pDestBmp->getSize().x;
    for (int i = 0; i < endRow; ++i) {
        int endCol =(*pHist)[i];
        if (endCol > width) { 
            endCol = width;
        }
        unsigned char * pDest = pDestBmp->getPixels()+stride*i;
        memset(pDest, 255, endCol);
    }
}