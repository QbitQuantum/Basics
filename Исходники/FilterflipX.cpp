BitmapPtr FilterFlipX::apply(BitmapPtr pBmpSource) 
{
    IntPoint Size = pBmpSource->getSize();
    BitmapPtr pBmpDest(new Bitmap(Size, pBmpSource->getPixelFormat(), 
            pBmpSource->getName()));

    unsigned char* pSrcLine = pBmpSource->getPixels();
    unsigned char* pDestLine = pBmpDest->getPixels();
    
    for (int y = 0; y < Size.y; y++) {
        switch (pBmpSource->getBytesPerPixel()) {
            case 1: {
                    unsigned char * pSrc = pSrcLine;
                    unsigned char * pDest = pDestLine+Size.x-1;
                    for (int x = 0; x < Size.x; x++) {
                        *pDest = *pSrc;
                        pSrc++;
                        pDest--;
                    }
                }
                break;
            case 4: {
                    Pixel32 * pSrc = (Pixel32*)pSrcLine;
                    Pixel32 * pDest = (Pixel32*)pDestLine+Size.x-1;
                    for (int x = 0; x < Size.x; x++) {
                        *pDest = *pSrc;
                        pSrc++;
                        pDest--;
                    }
                }
                break;
            default: 
                AVG_ASSERT(false);
        } 
        pSrcLine += pBmpSource->getStride();
        pDestLine += pBmpDest->getStride();
    }
    return pBmpDest;
}