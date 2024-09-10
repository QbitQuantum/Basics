void TDrawer::DrawReturnArrow(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TRect aWorldPointRect,
                              TRect aBitMapRect)
{
    //根据WorldPointRect大小 和 aBitMapRect的大小 设置新的returnRect的大小
    TPoint center;
    center.SetXY((aWorldPointRect.iBr.iX + aWorldPointRect.iTl.iX) / 2, (aWorldPointRect.iBr.iY
                 + aWorldPointRect.iTl.iY) / 2);
    TInt iHalfHigh = (aBitMapRect.iBr.iY - aBitMapRect.iTl.iY) / 2;
    TInt iHalfWidth = (aBitMapRect.iBr.iX - aBitMapRect.iTl.iX) / 2;
    TRect centerRect;
    centerRect.SetRect(center.iX - iHalfWidth, center.iY - iHalfHigh, center.iX + iHalfWidth, center.iY + iHalfHigh);

    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize desSize = aBackUpBitmap->SizeInPixels();
    TSize srcSize = aResourceBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    addr22 = addr2 + (centerRect.iTl.iY - 1) * desSize.iWidth + centerRect.iTl.iX;
    TSize newSize = centerRect.Size();
    addr11 = addr1 + aBitMapRect.iTl.iY * srcSize.iWidth + aBitMapRect.iTl.iX;
    //每画完一行，arrd11要前进的距离
    TInt iWidthSpan = srcSize.iWidth - newSize.iWidth;
    TInt iScreenWidthSpan = desSize.iWidth - newSize.iWidth;
    for (TInt j = 0; j < newSize.iHeight; j++)
    {
        for (TInt i = 0; i < newSize.iWidth; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11++;
        }
        addr11 = addr11 + iWidthSpan;
        addr22 = addr22 + iScreenWidthSpan;
    }
    backUpUtil.End();
    objectUtil.End();
}