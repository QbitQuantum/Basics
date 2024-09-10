BitmapPtr FilterResizeBilinear::apply(BitmapPtr pBmpSrc)
{
    int bpp = pBmpSrc->getBytesPerPixel();
    AVG_ASSERT(bpp==4 || bpp==3 || bpp==1);

    BitmapPtr pBmpDest = BitmapPtr(new Bitmap(m_NewSize, 
            pBmpSrc->getPixelFormat(), pBmpSrc->getName()+"_resized"));

    BilinearContribDef f(0.64);
    switch (bpp) {
        case 4:
            {
                TwoPassScale<CDataRGBA_UBYTE> sS(f);
                sS.Scale((CDataRGBA_UBYTE::PixelClass *) pBmpSrc->getPixels(), 
                        pBmpSrc->getSize(), pBmpSrc->getStride(), 
                        (CDataRGBA_UBYTE::PixelClass *) pBmpDest->getPixels(),
                        pBmpDest->getSize(), pBmpDest->getStride());
            }
            break;
        case 3:
            {
                TwoPassScale <CDataRGB_UBYTE> sS(f);
                sS.Scale((CDataRGB_UBYTE::PixelClass *) pBmpSrc->getPixels(), 
                        pBmpSrc->getSize(), pBmpSrc->getStride(), 
                        (CDataRGB_UBYTE::PixelClass *) pBmpDest->getPixels(),
                        pBmpDest->getSize(), pBmpDest->getStride());
            }
            break;
        case 1:
            {
                TwoPassScale <CDataA_UBYTE> sS(f);
                sS.Scale((CDataA_UBYTE::PixelClass *) pBmpSrc->getPixels(), 
                        pBmpSrc->getSize(), pBmpSrc->getStride(), 
                        (CDataA_UBYTE::PixelClass *) pBmpDest->getPixels(),
                        pBmpDest->getSize(), pBmpDest->getStride());
            }
            break;
        default:
            AVG_ASSERT(false);
    }
    return pBmpDest;
}