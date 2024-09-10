BitmapPtr FilterFlip::apply(BitmapPtr pBmpSource) 
{
    IntPoint size = pBmpSource->getSize();
    BitmapPtr pBmpDest(new Bitmap(size, pBmpSource->getPixelFormat(), 
            pBmpSource->getName()));

    unsigned char* pSrcLine = pBmpSource->getPixels();
    unsigned char* pDestLine = pBmpDest->getPixels()+(size.y-1)*pBmpDest->getStride();
    int lineLen = pBmpSource->getBytesPerPixel()*size.x;

    for (int y = 0; y < size.y; y++) {
        memcpy(pDestLine, pSrcLine, lineLen);
        pSrcLine += pBmpSource->getStride();
        pDestLine -= pBmpDest->getStride();
    }
    return pBmpDest;
}