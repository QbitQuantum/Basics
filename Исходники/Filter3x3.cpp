BitmapPtr Filter3x3::apply(BitmapPtr pBmpSource) 
{
    IntPoint newSize(pBmpSource->getSize().x-2, pBmpSource->getSize().y-2);
    BitmapPtr pNewBmp(new Bitmap(newSize, pBmpSource->getPixelFormat(),
            pBmpSource->getName()+"_filtered"));
            
    for (int y = 0; y < newSize.y; y++) {
        const unsigned char * pSrc = pBmpSource->getPixels()+y*pBmpSource->getStride();
        unsigned char * pDest = pNewBmp->getPixels()+y*pNewBmp->getStride();
        switch (pBmpSource->getBytesPerPixel()) {
            case 4:
                convolveLine<Pixel32>(pSrc, pDest, newSize.x, pBmpSource->getStride());
                break;
            case 3:
                convolveLine<Pixel24>(pSrc, pDest, newSize.x, pBmpSource->getStride());
                break;
            default:
                AVG_ASSERT(false);
        }
    }
    return pNewBmp;
}