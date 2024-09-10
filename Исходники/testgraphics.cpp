    void runTestsWithBmp(BitmapPtr pBmp, const string& sName)
    {
        BitmapPtr pMaskBmp = BitmapPtr(new Bitmap(pBmp->getSize(), I8));
        FilterFill<Pixel8>(0).applyInPlace(pMaskBmp);
        for (int y = 0; y < pBmp->getSize().y; y++) {
            pMaskBmp->setPixel(IntPoint(1, y), Pixel8(128));
            pMaskBmp->setPixel(IntPoint(2, y), Pixel8(255));
            pMaskBmp->setPixel(IntPoint(3, y), Pixel8(255));
        }

        BitmapPtr pDestBmp = FilterMask(pMaskBmp).apply(pBmp);
        string sFName = string("baseline/MaskResult")+sName+".png";
//        pDestBmp->save(sFName);
        sFName = getSrcDirName()+sFName;
        BitmapPtr pBaselineBmp = loadBitmap(sFName, pBmp->getPixelFormat());
        TEST(*pDestBmp == *pBaselineBmp);
    }