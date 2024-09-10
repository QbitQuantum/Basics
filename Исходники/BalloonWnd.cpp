void CBalloonWnd::CalcAndMove( CRect rectParent )
{
	CRect rectBalloon, rectScreen;
	int nArrowSide;

	// Calc window pos
	GetClientRect( &rectBalloon );
	rectBalloon.InflateRect(0,0, B_MARGIN * 2, B_MARGIN * 2);
	
	// Resize parent window - margin
	rectParent.InflateRect( m_nAMargin, m_nAMargin );

	// Get screen size
	GetDesktopWindow()->GetWindowRect( &rectScreen );

	// Top
	if ( rectBalloon.Height() + B_ARROW <= rectParent.top )
	{
		// It's enough space
		nArrowSide = B_ARROWBOTTOM;

		rectBalloon.OffsetRect( 0, rectParent.top - rectBalloon.Height() - B_ARROW );
		rectBalloon.OffsetRect( rectParent.left - ( rectBalloon.Width() - rectParent.Width() ) * 0.5, 0) ;

		m_nHMargin = ( rectBalloon.Width() - m_nArrowSM ) * 0.5;

		goto CorrectPos;
	}

	// Right
	if ( rectBalloon.Width() + B_ARROW <= (rectScreen.right - rectParent.right) )
	{
		// OK
		nArrowSide = B_ARROWLEFT;
		
		rectBalloon.OffsetRect( 0, rectParent.top + ( (rectParent.Height() - rectBalloon.Height()) * 0.5 ) );
		rectBalloon.OffsetRect( rectParent.right, 0) ;
	
		m_nVMargin = ( rectBalloon.Height() - m_nArrowSM ) * 0.5;

		goto CorrectPos;
	}

	// Left
	if ( rectBalloon.Width() + B_ARROW <= rectParent.left )
	{
		// OK
		nArrowSide = B_ARROWRIGHT;

		rectBalloon.OffsetRect( 0, rectParent.top + ( ( rectParent.Height() - rectBalloon.Height()) * 0.5 ) );
		rectBalloon.OffsetRect( rectParent.left - rectBalloon.Width() - B_ARROW, 0) ;

		m_nVMargin = ( rectBalloon.Height() - m_nArrowSM ) * 0.5;

		goto CorrectPos;
	}
	
	// Bottom
	if ( rectBalloon.Height() + B_ARROW <= (rectScreen.bottom- rectParent.bottom) )
	{
		// OK
		nArrowSide = B_ARROWTOP;

		rectBalloon.OffsetRect( 0, rectParent.bottom + B_ARROW );
		rectBalloon.OffsetRect( rectParent.left - ( rectBalloon.Width() - rectParent.Width() ) * 0.5, 0) ;

		m_nHMargin = ( rectBalloon.Width() - m_nArrowSM ) * 0.5;

		goto CorrectPos;
	}

	// Nowhere is sufficient room
	nArrowSide = B_ARROWRIGHT;
	rectBalloon.OffsetRect( -rectBalloon.left, -rectBalloon.top );
	
	goto End;

CorrectPos:
	if ( rectBalloon.left < 0 )
	{
		m_nHMargin += -rectBalloon.left;
		rectBalloon.OffsetRect( -rectBalloon.left, 0 );
	}

	goto End;
	
End:
	m_nArrowSide = nArrowSide;
	SetSize();

	SetWindowPos(NULL, rectBalloon.left - B_ARROW, rectBalloon.top - B_ARROW, 0, 0,
		SWP_NOSIZE | SWP_NOZORDER );
}