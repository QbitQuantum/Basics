void CXTPSkinObjectFrame::DrawFrame(CDC* pDC)
{
    if (m_bLockFrameDraw)
        return;

    CXTPWindowRect rc(this);
    rc.OffsetRect(-rc.TopLeft());

    GetSchema()->DrawThemeFrame(pDC, this);

    if (m_spi[SB_VERT].fVisible || m_spi[SB_HORZ].fVisible)
    {
        if (m_spi[SB_VERT].fVisible)
        {
            if (!m_pSBTrack || !m_pSBTrack->bTrackThumb)
                SetupScrollInfo(&m_spi[SB_VERT]);

            CXTPBufferDCEx dcMem(*pDC, m_spi[SB_VERT].rc);
            DrawScrollBar(&dcMem, &m_spi[SB_VERT]);
        }

        if (m_spi[SB_HORZ].fVisible)
        {
            if (!m_pSBTrack || !m_pSBTrack->bTrackThumb)
                SetupScrollInfo(&m_spi[SB_HORZ]);

            CXTPBufferDCEx dcMem(*pDC, m_spi[SB_HORZ].rc);
            DrawScrollBar(&dcMem, &m_spi[SB_HORZ]);
        }

        if (m_spi[SB_HORZ].fVisible && m_spi[SB_VERT].fVisible)
        {
            CRect rcSizeGripper(m_spi[SB_HORZ].rc.right, m_spi[SB_VERT].rc.bottom,
                                m_spi[SB_VERT].rc.right, m_spi[SB_HORZ].rc.bottom);

            if (GetExStyle() & WS_EX_LEFTSCROLLBAR)
            {
                rcSizeGripper.left = m_spi[SB_VERT].rc.left;
                rcSizeGripper.right = m_spi[SB_HORZ].rc.left;
            }

            pDC->FillSolidRect(rcSizeGripper, GetSchema()->GetScrollBarSizeBoxColor(this));

            if (IsSizeBox())
            {
                CXTPSkinManagerClass* pClassScrollBar = GetSkinManager()->GetSkinClass(this, _T("SCROLLBAR"));
                pClassScrollBar->DrawThemeBackground(pDC, SBP_SIZEBOX, SZB_RIGHTALIGN, rcSizeGripper);
            }
        }
    }
}