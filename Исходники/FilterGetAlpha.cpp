BitmapPtr FilterGetAlpha::apply(BitmapPtr pBmpSrc) 
{
    PixelFormat pf = pBmpSrc->getPixelFormat();
    AVG_ASSERT(pf == R8G8B8A8 || pf == B8G8R8A8);
    BitmapPtr pBmpDest = BitmapPtr(new Bitmap(pBmpSrc->getSize(), I8,
             pBmpSrc->getName()+"alpha"));
    unsigned char * pSrcLine = pBmpSrc->getPixels();
    unsigned char * pDestLine = pBmpDest->getPixels();
    IntPoint size = pBmpDest->getSize();
    for (int y = 0; y < size.y; ++y) {
        unsigned char * pSrcPixel = pSrcLine;
        unsigned char * pDstPixel = pDestLine;
        for (int x = 0; x < size.x; ++x) {
            *pDstPixel = pSrcPixel[ALPHAPOS];
            pSrcPixel += 4;
            ++pDstPixel;
        }
        pSrcLine = pSrcLine + pBmpSrc->getStride();
        pDestLine = pDestLine + pBmpDest->getStride();
    }
    return pBmpDest;
}