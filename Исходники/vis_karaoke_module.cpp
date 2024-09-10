void SjKaraokeWindow::OnTimer(wxTimerEvent&)
{
	wxASSERT( wxThread::IsMain() );

	/**********************************************************************
	 * PREPARE DRAWING
	 **********************************************************************/

	if( m_karaokeModule == NULL || m_karaokeModule->m_bg == NULL ) return;
	if( m_inPaint ) return;
	m_inPaint = true;

	#ifdef __WXMAC__
	m_pleaseUpdateAll = true; // partly updates do not work well on Mac OS X
	#endif

	// does the size of the window have changed?
	if( m_clientSize != GetClientSize() || m_bgChanged )
	{
		// yes: save the new size
		m_clientSize = GetClientSize();
		m_pleaseUpdateAll = true;

		// (re-)create the offscreen DC
		m_offscreenBitmap.Create(m_clientSize.x, m_clientSize.y);
		m_offscreenDc.SelectObject(m_offscreenBitmap);

		// force reloading of the background image
		m_karaokeModule->m_bg->SetSize(m_clientSize);
		m_bgChanged = false;
	}

	// check what to show
	int karaokeEnded = 1;
	if( m_karaokeMaster.HasKaraoke() )
	{
		long totalMs, elapsedMs, remainingMs;
		g_mainFrame->m_player.GetTime(totalMs, elapsedMs, remainingMs);
		if( elapsedMs >= 0 ) // -1=error, 0=normal position 0:00
		{
			karaokeEnded = m_karaokeMaster.SetPosition(elapsedMs)? 0 : 1;
		}
	}

	if( karaokeEnded != m_karaokeEnded )
	{
		if( karaokeEnded )
		{
			if( m_sjScreen == NULL )
				m_sjScreen = new SjSjScreen(wxT("SILVERJUKE KARAOKE"),
				                            g_mainFrame->IsKioskStarted()? wxT("www.silverjuke.net") : wxT(""), 8000);
		}
		else
		{
			if( m_sjScreen )
			{
				delete m_sjScreen;
				m_sjScreen = NULL;
			}
		}

		m_pleaseUpdateAll = true;
		m_karaokeEnded = karaokeEnded;
	}

	// set the DC to use
	wxClientDC clientDcDontUse(this);
	wxDC* dc;
	if( m_pleaseUpdateAll )
	{
		dc = &m_offscreenDc;
	}
	else
	{
		dc = &clientDcDontUse;
	}

	/**********************************************************************
	 * DRAW!
	 **********************************************************************/

	// redraw background?
	if( m_pleaseUpdateAll )
	{
		m_karaokeModule->m_bg->DrawBackground(*dc);
	}

	// redraw karaoke?
	if( karaokeEnded )
	{
		if(  m_sjScreen
		        && !m_sjScreen->Render(*dc, *(m_karaokeModule->m_bg), m_pleaseUpdateAll)
		        && !m_karaokeMaster.HasKaraoke() )
		{
			delete m_sjScreen;
			m_sjScreen = NULL;
			if( !g_mainFrame->IsKioskStarted() /*no error messages in kiosk mode!*/
			        && !g_mainFrame->IsStopped() )
			{
				m_sjScreen = new SjSjScreen(_("No lyrics found."), wxT(""), 0);
			}
		}
	}
	else
	{
		m_karaokeMaster.Render(*dc, *(m_karaokeModule->m_bg), m_pleaseUpdateAll);
	}

	/**********************************************************************
	 * DRAWING DONE
	 **********************************************************************/

	// BLIT if we are drawing offscreen
	if( m_pleaseUpdateAll )
	{
		clientDcDontUse.Blit(0, 0, m_clientSize.x, m_clientSize.y, &m_offscreenDc, 0, 0);
	}

	// really done!
	m_pleaseUpdateAll = false;
	m_inPaint = false;
}