//-----------------------------------------------------------------------------
// Purpose: FIXME:  This should either be embedded or we should draw the caption
//  here
//-----------------------------------------------------------------------------
void CChoreoEventWidget::redraw( CChoreoWidgetDrawHelper& drawHelper )
{
	if ( !getVisible() )
		return;

	CChoreoEvent *event = GetEvent();
	if ( !event )
		return;

	int deflateborder = 1;
	int fontsize = 9;

	HDC dc = drawHelper.GrabDC();
	RECT rcClient = getBounds();

	RECT rcDC;
	drawHelper.GetClientRect( rcDC );

	RECT dummy;
	if ( !IntersectRect( &dummy, &rcDC, &rcClient ) )
		return;

	bool ramponly = m_pView->IsRampOnly();

	if ( IsSelected() && !ramponly )
	{
		InflateRect( &rcClient, 3, 1 );
		//rcClient.bottom -= 1;
		rcClient.right += 1;

		RECT rcFrame = rcClient;
		RECT rcBorder = rcClient;

		rcFrame.bottom = rcFrame.top + 17;
		rcBorder.bottom = rcFrame.top + 17;

		COLORREF clrSelection = RGB( 0, 63, 63 );
		COLORREF clrBorder = RGB( 100, 200, 255 );

		HBRUSH brBorder = CreateSolidBrush( clrBorder );
		HBRUSH brSelected = CreateHatchBrush( HS_FDIAGONAL, clrSelection );
		for ( int i = 0; i < 2; i++ )
		{
			FrameRect( dc, &rcFrame, brSelected );
			InflateRect( &rcFrame, -1, -1 );
		}
		FrameRect( dc, &rcBorder, brBorder );
		FrameRect( dc, &rcFrame, brBorder );

		DeleteObject( brSelected );
		DeleteObject( brBorder );
		rcClient.right -= 1;
		//rcClient.bottom += 1;
		InflateRect( &rcClient, -3, -1 );
	}	

	RECT rcEvent;
	rcEvent = rcClient;

	InflateRect( &rcEvent, 0, -deflateborder );

	rcEvent.bottom = rcEvent.top + 10;

	if ( event->GetType() == CChoreoEvent::SPEAK && m_pWaveFile && !event->HasEndTime() )
	{
		event->SetEndTime( event->GetStartTime() + m_pWaveFile->GetRunningLength() );
		rcEvent.right = ( int )( m_pWaveFile->GetRunningLength() * m_pView->GetPixelsPerSecond() );  
	}

	if ( event->HasEndTime() )
	{
		rcEvent.right = rcEvent.left + m_nDurationRightEdge;

		RECT rcEventLine = rcEvent;
		OffsetRect( &rcEventLine, 0, 1 );

		if ( event->GetType() == CChoreoEvent::SPEAK )
		{
			if ( m_pWaveFile )
			{
				HBRUSH brEvent = CreateSolidBrush( COLOR_CHOREO_EVENT );
				HBRUSH brBackground = CreateSolidBrush( COLOR_CHOREO_DARKBACKGROUND );

				if ( !ramponly )
				{
					FillRect( dc, &rcEventLine, brBackground );
				}

				// Only draw wav form here if selected
				if ( IsSelected() )
				{
					sound->RenderWavToDC( dc, rcEventLine, IsSelected() ? COLOR_CHOREO_EVENT_SELECTED : COLOR_CHOREO_EVENT, 0.0, m_pWaveFile->GetRunningLength(), m_pWaveFile );
				}

				//FrameRect( dc, &rcEventLine, brEvent );
				drawHelper.DrawColoredLine( COLOR_CHOREO_EVENT, PS_SOLID, 3,
					rcEventLine.left, rcEventLine.top, rcEventLine.left, rcEventLine.bottom );
				drawHelper.DrawColoredLine( COLOR_CHOREO_EVENT, PS_SOLID, 3,
					rcEventLine.right, rcEventLine.top, rcEventLine.right, rcEventLine.bottom );
				
				DeleteObject( brBackground );
				DeleteObject( brEvent );

				//rcEventLine.top -= 3;
				DrawRelativeTags( drawHelper, rcEventLine, m_pWaveFile->GetRunningLength(), event );
			}
		}
		else
		{
			COLORREF clrEvent = IsSelected() ? COLOR_CHOREO_EVENT_SELECTED : COLOR_CHOREO_EVENT;
			if ( event->GetType() == CChoreoEvent::SUBSCENE )
			{
				clrEvent = RGB( 200, 180, 200 );
			}

			HBRUSH brEvent = CreateSolidBrush( clrEvent );
		
			if ( !ramponly )
			{
				FillRect( dc, &rcEventLine, brEvent );
			}
		
			DeleteObject( brEvent );

			if ( ramponly && IsSelected() )
			{
				drawHelper.DrawOutlinedRect( RGB( 150, 180, 250 ), PS_SOLID, 1,
					rcEventLine );
			}
			else
			{
				drawHelper.DrawColoredLine( RGB( 127, 127, 127 ), PS_SOLID, 1, rcEventLine.left, rcEventLine.bottom,
					rcEventLine.left, rcEventLine.top );
				drawHelper.DrawColoredLine( RGB( 127, 127, 127 ), PS_SOLID, 1, rcEventLine.left, rcEventLine.top,
					rcEventLine.right, rcEventLine.top );
				drawHelper.DrawColoredLine( RGB( 31, 31, 31 ), PS_SOLID, 1, rcEventLine.right, rcEventLine.top,
					rcEventLine.right, rcEventLine.bottom );
				drawHelper.DrawColoredLine( RGB( 0, 0, 0 ), PS_SOLID, 1, rcEventLine.right, rcEventLine.bottom,
					rcEventLine.left, rcEventLine.bottom );
			}

			g_pRampTool->DrawSamplesSimple( drawHelper, event, false, RGB( 63, 63, 63 ), rcEventLine );

			DrawRelativeTags( drawHelper, rcEventLine, event->GetDuration(), event );
			DrawAbsoluteTags( drawHelper, rcEventLine, event->GetDuration(), event );

		}
	}
	else
	{
		RECT rcEventLine = rcEvent;
		OffsetRect( &rcEventLine, 0, 1 );

		drawHelper.DrawColoredLine( COLOR_CHOREO_EVENT, PS_SOLID, 3,
			rcEventLine.left - 1, rcEventLine.top, rcEventLine.left - 1, rcEventLine.bottom );
	}

	if ( event->IsUsingRelativeTag() )
	{
		RECT rcTagName;
		rcTagName = rcClient;

		int length = drawHelper.CalcTextWidth( "Arial", 9, FW_NORMAL, event->GetRelativeTagName() );

		rcTagName.right = rcTagName.left;
		rcTagName.left = rcTagName.right - length - 4;
		rcTagName.top += 3;
		rcTagName.bottom = rcTagName.top + 10;
		
		drawHelper.DrawColoredText( "Arial", 9, FW_NORMAL, RGB( 0, 100, 200 ), rcTagName, event->GetRelativeTagName() );

		drawHelper.DrawFilledRect( RGB( 0, 100, 250 ), rcTagName.right-1, rcTagName.top-2,
			rcTagName.right+2, rcTagName.bottom + 2 );

	}

	// Now draw the label
	RECT rcEventLabel;
	rcEventLabel = rcClient;

	InflateRect( &rcEventLabel, 0, -deflateborder );

	rcEventLabel.top += 15; // rcEventLabel.bottom - 2 * ( fontsize + 2 ) - 1;
	rcEventLabel.bottom = rcEventLabel.top + fontsize + 2;
	rcEventLabel.left += 1;

	//rcEventLabel.left -= 8;

	int leftAdd = 16;

	if ( CChoreoEventWidget::GetImage( event->GetType() ) )
	{
		mxbitmapdata_t *image = CChoreoEventWidget::GetImage( event->GetType() );
		if ( image )
		{
			DrawBitmapToDC( dc, rcEventLabel.left, rcEventLabel.top, leftAdd, leftAdd,
				*image );	
		}
	}

	if ( event->IsResumeCondition() )
	{
		RECT rc = rcEventLabel;
		OffsetRect( &rc, leftAdd, 0 );
		rc.right = rc.left + leftAdd;

		DrawBitmapToDC( dc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
			*CChoreoEventWidget::GetPauseImage() );
	}

	//rcEventLabel.left += 8;

	OffsetRect( &rcEventLabel, 18, 1 );
	
	int len = drawHelper.CalcTextWidth( "Arial", fontsize, FW_NORMAL, event->GetName() );

	rcEventLabel.right = rcEventLabel.left + len + 2;
	drawHelper.DrawColoredText( "Arial", fontsize, FW_NORMAL, RGB( 0, 0, 120 ), 
		rcEventLabel, event->GetName() );
}