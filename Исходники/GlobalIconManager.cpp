/************************************************************************
drawTransparent 주어진 인자를 바탕으로 투명한 그림을 그린다.
@PARAM  : 
    pDC         그림을 그릴 DC
    bmp         투명으로 그려질 이미지의 원본
    ptOrigin    그려질 기준점
    bExtract    이미지에서 투명색을 추출할 것인가?
    ptExtractPoint  투명색을 추출할 위치는 어디인가?
    maskClr     추출하지 않을 경우 투명색은 어떤 색인가?
@RETURN : 
@REMARK : 
@AUTHOR : youngchang ([email protected])
@HISTORY :
    2006/03/21:CREATED
************************************************************************/
void        CFishBMPManager::drawTransparent(CDC* pDC, CBitmap* bmp, CPoint ptOrigin, BOOL bExtract, CPoint ptExtractPoint, COLORREF maskClr)
{
    if (bExtract)
    {
        CDC extDC;
        extDC.CreateCompatibleDC(pDC);
        extDC.SelectObject(bmp);
        maskClr =   extDC.GetPixel(ptExtractPoint);
    }
    //////////////////////////////////////////////////////////////////////////
    // device context creation to draw transparently
    CDC memDC, maskDC, buffDC, copyDC;
    memDC.CreateCompatibleDC(pDC);
    maskDC.CreateCompatibleDC(pDC);
    buffDC.CreateCompatibleDC(pDC);
    copyDC.CreateCompatibleDC(pDC);
    
    BITMAP bm;
    bmp->GetBitmap(&bm);
    
    CBitmap buffBitmap;
    buffBitmap.CreateCompatibleBitmap( pDC, bm.bmWidth, bm.bmHeight);
    CBitmap* oldbuffBitmap = buffDC.SelectObject( &buffBitmap );
    
    CBitmap maskBitmap; 
    maskBitmap.CreateBitmap( bm.bmWidth, bm.bmHeight, 1, 1, NULL );
    CBitmap* oldmaskBitmap = maskDC.SelectObject( &maskBitmap );
    
    buffDC.FillSolidRect( &CRect(0, 0, bm.bmWidth, bm.bmHeight), maskClr);

    memDC.SelectObject(bmp);
    buffDC.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);

//    pImageList->DrawIndirect(&buffDC, nIndex, CPoint(0,0), sizeImage, CPoint(0, 0));

    maskDC.BitBlt( 0, 0, bm.bmWidth, bm.bmHeight, &buffDC, 0, 0, SRCCOPY );
    
    // draw icon transparently after making mask bitmap img.
    CBitmap copyBitmap;
    copyBitmap.CreateCompatibleBitmap( pDC, bm.bmWidth, bm.bmHeight);
    CBitmap* oldcopyBitmap = copyDC.SelectObject( &copyBitmap );
    copyDC.BitBlt( 0, 0, bm.bmWidth, bm.bmHeight, pDC, ptOrigin.x, ptOrigin.y, SRCCOPY );
    copyDC.BitBlt( 0, 0, bm.bmWidth, bm.bmHeight, &maskDC, 0, 0, SRCAND );
    buffDC.BitBlt( 0, 0, bm.bmWidth, bm.bmHeight, &maskDC, 0, 0, SRCMASK );
    copyDC.BitBlt( 0, 0, bm.bmWidth, bm.bmHeight, &buffDC, 0, 0, SRCPAINT );
    pDC->BitBlt(ptOrigin.x, ptOrigin.y, bm.bmWidth, bm.bmHeight, &copyDC, 0, 0, SRCCOPY );   
    return;
}