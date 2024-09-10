BitmapPtr FilterGrayscale::apply(BitmapPtr pBmpSrc) 
{
    PixelFormat PF = pBmpSrc->getPixelFormat();
    if (PF == I8) {
        return BitmapPtr(new Bitmap(*pBmpSrc));
    }
    BitmapPtr pBmpDest = BitmapPtr(new Bitmap(pBmpSrc->getSize(), I8,
             pBmpSrc->getName()));
    unsigned char * pSrcLine = pBmpSrc->getPixels();
    unsigned char * pDestLine = pBmpDest->getPixels();
    IntPoint size = pBmpDest->getSize();
    int bpp = pBmpSrc->getBytesPerPixel();
    for (int y = 0; y<size.y; ++y) {
        unsigned char * pSrcPixel = pSrcLine;
        unsigned char * pDstPixel = pDestLine;
        for (int x = 0; x < size.x; ++x) {
            // For the coefficients used, see http://www.inforamp.net/~poynton/
            // Appoximations curtesy of libpng :-).
            if (PF == R8G8B8A8 || PF == R8G8B8X8 || PF == R8G8B8) {
                *pDstPixel = (unsigned char)((pSrcPixel[REDPOS]*54+
                        pSrcPixel[GREENPOS]*183+
                        pSrcPixel[BLUEPOS]*19)/256);
                pSrcPixel += bpp;
                ++pDstPixel;
            } else {
                *pDstPixel = (unsigned char)((pSrcPixel[BLUEPOS]*54+
                        pSrcPixel[GREENPOS]*183+
                        pSrcPixel[REDPOS]*19)/256);
                pSrcPixel += bpp;
                ++pDstPixel;
            }
        }
        pSrcLine = pSrcLine + pBmpSrc->getStride();
        pDestLine = pDestLine + pBmpDest->getStride();
    }
    return pBmpDest;
}