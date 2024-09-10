    void SImageMaskWnd::MakeCacheApha(ISkinObj *pSkin)
    {
        SASSERT(m_bmpMask && m_bmpCache);
        CAutoRefPtr<IRenderTarget> pRTDst;
        GETRENDERFACTORY->CreateRenderTarget(&pRTDst,0,0);
        CAutoRefPtr<IRenderObj> pOldBmp;
        pRTDst->SelectObject(m_bmpCache,&pOldBmp);
        CRect rc(CPoint(0,0),m_bmpCache->Size());
        pSkin->Draw(pRTDst,&rc,0);
        pRTDst->SelectObject(pOldBmp);
        
        //从mask的指定channel中获得alpha通道
        LPBYTE pBitCache = (LPBYTE)m_bmpCache->LockPixelBits();
        LPBYTE pBitMask = (LPBYTE)m_bmpMask->LockPixelBits();
        LPBYTE pDst = pBitCache;
        LPBYTE pSrc = pBitMask + m_iMaskChannel;
        int nPixels = m_bmpCache->Width()*m_bmpCache->Height();
        for(int i=0;i<nPixels;i++)
        {
            BYTE byAlpha = *pSrc;
            pSrc += 4;

            *pDst++ = ((*pDst) * byAlpha)>>8;//做premutiply
            *pDst++ = ((*pDst) * byAlpha)>>8;//做premutiply
            *pDst++ = ((*pDst) * byAlpha)>>8;//做premutiply
            *pDst++ = byAlpha;
        }
        m_bmpCache->UnlockPixelBits(pBitCache);
        m_bmpMask->UnlockPixelBits(pBitMask);
    }