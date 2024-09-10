BitmapPtr FilterBlur::apply(BitmapPtr pBmpSrc)
{
    AVG_ASSERT(pBmpSrc->getPixelFormat() == I8);
    
    IntPoint Size(pBmpSrc->getSize().x-2, pBmpSrc->getSize().y-2);
    BitmapPtr pDestBmp = BitmapPtr(new Bitmap(Size, I8, pBmpSrc->getName()));
    int srcStride = pBmpSrc->getStride();
    int destStride = pDestBmp->getStride();
    unsigned char * pSrcLine = pBmpSrc->getPixels()+srcStride+1;
    unsigned char * pDestLine = pDestBmp->getPixels();
    for (int y = 0; y < Size.y; ++y) {
        unsigned char * pSrcPixel = pSrcLine;
        unsigned char * pDestPixel = pDestLine;
        for (int x = 0; x < Size.x; ++x) {
            *pDestPixel = (*(pSrcPixel-1) + *(pSrcPixel)*4 + *(pSrcPixel+1)
                    +*(pSrcPixel-srcStride)+*(pSrcPixel+srcStride)+4)/8;
            ++pSrcPixel;
            ++pDestPixel;
        }
        pSrcLine += srcStride;
        pDestLine += destStride;
    }
    return pDestBmp;
}