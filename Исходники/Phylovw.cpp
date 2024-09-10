void
CPhylogenView::SetSelected(int Selection, int CheckScroll )
{
    CGenedocDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    m_LastKeySelect = Selection;
    CPhyloGenBase * pPGB;

    POSITION Pos;
    Pos = pDoc->m_pPGBase->m_PhyloList.GetHeadPosition();
    while ( Pos != NULL ) {
        pPGB = (CPhyloGenBase *)pDoc->m_pPGBase->m_PhyloList.GetNext(Pos);
        if ( !Selection-- ) break;
    }
    CDC* pDC = GetDC();

    CRect fRect = pPGB->m_ClientRect;

    if ( CheckScroll ) {

        // Check if Scroll Call need to be made.
        CRect tRect ( m_ScrollPos, m_ViewSize );
        CPoint Position1 = fRect.TopLeft();
        Position1.x = 0;
        CPoint Position2 = fRect.BottomRight();
        Position2.x = 0;

        if ( (!tRect.PtInRect ( Position1 )) || (!tRect.PtInRect ( Position2 )) ) {
            CPoint tPos = m_ScrollPos;
            int YPos = Position1.y;
            if ( (YPos - (m_ViewSize.cy / 2)) < 0 ) {
                YPos = 0;
            } else {
                YPos = (YPos - (m_ViewSize.cy / 2));
            }
            tPos.y = YPos < (m_MaxScrolls.cy - m_ViewSize.cy) ? YPos: (m_MaxScrolls.cy - m_ViewSize.cy);
            tPos.x = Position1.x < (m_MaxScrolls.cx - m_ViewSize.cx) ? Position1.x: (m_MaxScrolls.cx - m_ViewSize.cx);
            ScrollToPosition ( tPos );
            m_ScrollPos = GetScrollPosition();
        }
    }

    CClientDC dc(this);
    OnPrepareDC(&dc);
    pPGB->m_Selected = 1;
    dc.LPtoDP( &fRect );
    pDC->DrawFocusRect( fRect );
    ReleaseDC( pDC );

}