void CLineNumberStatic::OnPaint() 
/* ============================================================
	Function :		CLineNumberStatic::OnPaint
	Description :	Handler for WM_PAINT. 
 
	Return :		void
	Parameters :	none

	Usage :			Called from Windows.

   ============================================================*/
{

	CPaintDC dcPaint( this );

	CRect rect;
	GetClientRect( &rect );

	// We double buffer the drawing - 
	// preparing the memory CDC
	CDC dc;
	dc.CreateCompatibleDC( &dcPaint );
	int saved = dc.SaveDC();

	// Create GDI and select objects
	CBitmap bmp;
	CPen pen;
	bmp.CreateCompatibleBitmap( &dcPaint, rect.Width(), rect.Height() );
	pen.CreatePen( PS_SOLID, 1, m_fgcol );
	dc.SelectObject( &bmp );
	dc.SelectObject( &pen );

	// Painting the background
	dc.FillSolidRect( &rect, m_bgcol );
	dc.MoveTo( rect.right - 1, 0 );
	dc.LineTo( rect.right - 1, rect.bottom );

	// Setting other attributes
	dc.SetTextColor( m_fgcol );
	dc.SetBkColor( m_bgcol );
	dc.SelectObject( GetParent()->GetFont() );

	// Output the line numbers
	if( m_bottomline )
	{
		int lineheight = dc.GetTextExtent( _T( "0" ) ).cy;
		for( int t = m_topline ; t < m_bottomline ; t++ )
		{
			CString output;
			output.Format( m_format, t+1);
			int topposition = m_topmargin + lineheight * ( t - m_topline );
			dc.TextOut( 2, topposition, output );
		}
	}

	dcPaint.BitBlt( 0, 0, rect. right, rect.bottom, &dc, 0, 0, SRCCOPY );
	dc.RestoreDC( saved );

}