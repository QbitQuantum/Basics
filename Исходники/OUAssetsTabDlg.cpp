CBitmap* OUAssetsTabDlg::ScaleBitmap(CImage* pImg, int maxwidth, int maxheight)
{
    /** 计算新大小和位置 */
    int nWidth = pImg->GetWidth();
    int nHeight = pImg->GetHeight();
    int nNewWidth = nWidth, nNewHeight = nHeight;
    int x, y;
    if(nWidth > maxwidth || nHeight > maxheight)
    {
        int nWidth1, nWidth2;
        int nHeight1, nHeight2;

        nWidth1 = maxwidth, nHeight1 = (float)(((float)maxwidth / (float)(nWidth)) * (float)nHeight);
        nHeight2 = maxheight, nWidth2 = (float)(((float)maxheight / (float)(nHeight)) * (float)nWidth);

        if(nHeight1 > maxheight) nNewWidth = nWidth2, nNewHeight = nHeight2;
        else
        if(nWidth2 > maxwidth) nNewWidth = nWidth1, nNewHeight = nHeight1;
        else
        {
            nNewWidth = max(nWidth1, nWidth2);
            nNewHeight = max(nHeight1, nHeight2);
        }
    }
    x = (maxwidth - nNewWidth) >> 1;
    y = (maxheight - nNewHeight) >> 1;

    CBitmap* pImgCpy = new CBitmap();
    pImgCpy->DeleteObject();
    pImgCpy->Attach(pImg->operator HBITMAP());

    CDC* pMDC1 = new CDC();
    CDC* pMDC2 = new CDC();
    CBitmap* pOldBt1;
    CBitmap* pOldBt2;
    CBitmap* pBmPtr = new CBitmap();
    CClientDC dc(this);

    pMDC2->CreateCompatibleDC(&dc);
    pOldBt2 = pMDC2->SelectObject(pImgCpy);

    pMDC1->CreateCompatibleDC(&dc);
    pBmPtr->CreateCompatibleBitmap(&dc, maxwidth, maxheight);
    pOldBt1 = pMDC1->SelectObject(pBmPtr);

    BITMAP bm;
    GetObject(*pImgCpy, sizeof(bm), &bm);
    pMDC1->StretchBlt(x, y, nNewWidth, nNewHeight, pMDC2, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    pMDC1->SelectObject(pOldBt1);
    pMDC1->DeleteDC();
    pMDC2->SelectObject(pOldBt2);
    pMDC2->DeleteDC();

    return pBmPtr;
}