void CHMMDemoView::OnDraw(CDC* pDC)
{
    CHMMDemoDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    HDC dstDC = pDC->m_hDC;
    CImage& frame = m_camera.GetFrame();

    CRect r;
    GetClipBox( dstDC, &r );

    if( m_imageList && m_imageList->GetCount() > 1 ) //several images was selected
    {
        pDC->Draw3dRect(0,0,frame.Width(),frame.Height(),RGB(0,0,0),RGB(128,128,128));
    }

    frame.Show( dstDC, r.left, r.top, r.Width(), r.Height(), r.left, r.top );

    if( m_sel.Width() != 0 && m_sel.Height() != 0 )
    {
        HGDIOBJ old = SelectObject( dstDC, GetStockObject( WHITE_PEN ));
        POINT pt[] = {
            { m_sel.left - r.left, m_sel.top - r.top },
            { m_sel.right - r.left - 1, m_sel.top - r.top },
            { m_sel.right - r.left - 1, m_sel.bottom - r.top - 1},
            { m_sel.left - r.left, m_sel.bottom - r.top - 1},
            { m_sel.left - r.left, m_sel.top - r.top }
        };

        Polyline( dstDC, pt, 5 );
        SelectObject( dstDC, old );
    }

    //::ReleaseDC( m_hWnd, dstDC );
}