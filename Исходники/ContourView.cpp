void CContourView::OnMouseMove( UINT nFlags, CPoint point )
{
    // TODO: Add your message handler code here and/or call default
    CDC*  dc;
    RECT therect;
    CString buffer;
    POINT pt( point );
    double zval;

    dc = this->GetDC();
    this->GetClientRect( &therect );
    dc->DPtoLP( &therect );

    dc->DPtoLP( &pt );
    buffer.Format( "                                                                                                                 " );
    TextOut( dc->m_hDC, therect.left, therect.top, buffer, buffer.GetLength() );
    if ( m_pTriangle->IsInControlDots( pt, zval ) == true )
        buffer.Format( "x=%7d  y=%7d  z=%7.2f", pt.x, pt.y, zval );
    else
        buffer.Format( "x=%7d  y=%7d", pt.x, pt.y );
    TextOut( dc->m_hDC, therect.left, therect.top, buffer, buffer.GetLength() );


    CLogScrollView::OnMouseMove( nFlags, point );
}