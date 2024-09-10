void DefaultDecorator::DrawButton( uint32 nButton, const Color32_s & sFillColor )
{
	Layer *pcView = GetLayer();

	nButton = CheckIndex( nButton );
	Rect cFrame = m_cObjectFrame[nButton];
	bool bState = m_bObjectState[nButton];
	font_height fh;

	fh = pcView->GetFontHeight();
	Rect r;
	Point cScale( cFrame.Size() );

	if( cFrame.Width() < 1 )
		return;

	pcView->FillRect( cFrame, sFillColor );
	pcView->DrawFrame( cFrame, FRAME_TRANSPARENT | ( bState ? FRAME_RECESSED : FRAME_RAISED ) );

	switch ( nButton )
	{
	case WindowDecorator::HIT_DRAG:
		pcView->SetFgColor( 255, 255, 255, 0 );
		pcView->SetBgColor( sFillColor );
		pcView->MovePenTo( cFrame.left + 5, ( cFrame.Height() + 1.0f ) / 2 - ( fh.ascender + fh.descender ) / 2 + fh.ascender );
		pcView->DrawString( m_cTitle.c_str(), -1 );
		break;
	case WindowDecorator::HIT_CLOSE:
		SetRect( 0.33, 0.33, 0.67, 0.67 );
		pcView->DrawFrame( r, FRAME_TRANSPARENT | ( bState ? FRAME_RAISED : FRAME_RECESSED ) );
		break;
	case WindowDecorator::HIT_MINIMIZE:
		SetRect( 0.2, 0.2, 0.8, 0.8 );
		pcView->DrawFrame( r, FRAME_TRANSPARENT | ( bState ? FRAME_RAISED : FRAME_RECESSED ) );
		SetRect( 0.2, 0.6, 0.4, 0.8 );
		r.left++;
		r.right += 2;
		r.top--;
		r.bottom -= 2;
		pcView->DrawFrame( r, FRAME_TRANSPARENT | ( bState ? FRAME_RECESSED : FRAME_RAISED ) );
		break;
	case WindowDecorator::HIT_DEPTH:
		if( bState )
		{
			SetRect( 0.2, 0.2, 0.6, 0.6 );
			pcView->DrawFrame( r, FRAME_TRANSPARENT | ( FRAME_RAISED ) );
			SetRect( 0.4, 0.4, 0.8, 0.8 );
			pcView->FillRect( r, sFillColor );
			pcView->DrawFrame( r, FRAME_TRANSPARENT | ( FRAME_RAISED ) );
		}
		else
		{
			SetRect( 0.4, 0.4, 0.8, 0.8 );
			pcView->DrawFrame( r, FRAME_TRANSPARENT | ( FRAME_RECESSED ) );
			SetRect( 0.2, 0.2, 0.6, 0.6 );
			pcView->FillRect( r, sFillColor );
			pcView->DrawFrame( r, FRAME_TRANSPARENT | ( FRAME_RECESSED ) );
		}
		break;
	case WindowDecorator::HIT_ZOOM:
		SetRect( 0.2, 0.2, 0.8, 0.8 );
		pcView->DrawFrame( r, FRAME_TRANSPARENT | ( bState ? FRAME_RAISED : FRAME_RECESSED ) );
		SetRect( 0.2, 0.2, 0.6, 0.6 );
		r.left += 2;
		r.top += 2;
		pcView->DrawFrame( r, FRAME_TRANSPARENT | ( bState ? FRAME_RECESSED : FRAME_RAISED ) );
		break;
	}
}