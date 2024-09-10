GS_VOID CPokeMiniEmulatorDlg::PaintScreen()
{
    const GS_BYTE *pSrcRow = (const GS_BYTE *)m_pPaintDev->pData;
    GS_BYTE *pDstRow = (GS_BYTE *)m_screenDev.pData;
    for (GS_UINT h = 0; h < m_screenDev.height; ++h)
    {
        const GS_BYTE *pSrc = pSrcRow;
        GS_BYTE *pDst = pDstRow;
        for (GS_UINT w = 0; w < m_screenDev.width; ++w)
        {
            memcpy(pDst, &(m_colorTable[*pSrc]), 4);
            pSrc += 1;
            pDst += 4;
        }

        pSrcRow += m_pPaintDev->rowBytes;
        pDstRow += m_screenDev.rowBytes;
    }

    {
        CDC *pDC = m_screen.GetDC();
        CRect dcRect;
        m_screen.GetWindowRect(&dcRect);

        CBitmap newbmp;
        newbmp.CreateBitmap(m_screenDev.width, m_screenDev.height, 1, 32, m_screenDev.pData);

        CDC srcDC;
        srcDC.CreateCompatibleDC(pDC);
        CBitmap *pOldBmp = srcDC.SelectObject(&newbmp);

        pDC->StretchBlt(0, 0, dcRect.Width(), dcRect.Height(), &srcDC, 0, 0, m_screenDev.width, m_screenDev.height, SRCCOPY);

        srcDC.SelectObject(pOldBmp);
        srcDC.DeleteDC();
        newbmp.DeleteObject();
        m_screen.ReleaseDC(pDC);
    }
}