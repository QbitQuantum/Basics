void SjOscWindow::OnTimer(wxTimerEvent&)
{
	SJ_FORCE_IN_HERE_ONLY_ONCE;

	if( m_oscModule )
	{
		// volume stuff
		long                volume, maxVolume = 1;
		bool                volumeBeat;

		// other objects
		long                i;
		bool                titleChanged, forceOscAnim, forceSpectrAnim;
		wxString            newTitle;

		// get data
		g_mainFrame->m_player.GetVisData(m_bufferStart, m_sampleCount*SJ_WW_CH*SJ_WW_BYTERES, 0);

		// get window client size, correct offscreen DC if needed
		wxSize clientSize = m_oscModule->m_oscWindow->GetClientSize();
		if( clientSize.x != m_offscreenBitmap.GetWidth() || clientSize.y != m_offscreenBitmap.GetHeight() )
		{
			m_offscreenBitmap.Create(clientSize.x, clientSize.y);
			m_offscreenDc.SelectObject(m_offscreenBitmap);
		}

		// calculate the points for the lines, collect volume
		m_oscilloscope->Calc(clientSize, m_bufferStart, volume);
		if( m_oscModule->m_showFlags&SJ_OSC_SHOW_SPECTRUM )
		{
			m_spectrum->Calc(clientSize, m_bufferStart);
		}

		// get data that are shared between the threads
		{
			titleChanged = m_oscModule->m_titleChanged;
			m_oscModule->m_titleChanged = FALSE;
			if( titleChanged )
			{
				newTitle = m_oscModule->m_trackName;
				if( newTitle.IsEmpty() )
				{
					newTitle = SJ_PROGRAM_NAME;
				}
				else if( !m_oscModule->m_leadArtistName.IsEmpty() )
				{
					newTitle.Prepend(m_oscModule->m_leadArtistName + wxT(" - "));
				}
			}

			forceOscAnim = m_oscModule->m_forceOscAnim;
			m_oscModule->m_forceOscAnim = FALSE;

			forceSpectrAnim = m_oscModule->m_forceSpectrAnim;
			m_oscModule->m_forceSpectrAnim = FALSE;
		}

		// calculate volume, volume is theoretically max. 255, normally lesser
		if( titleChanged )              { maxVolume = 1;        }
		if( volume > maxVolume )        { maxVolume = volume;   }

		volumeBeat = (volume > maxVolume/2);

		// erase screen
		m_offscreenDc.SetPen(*wxTRANSPARENT_PEN);
		{
			// blue gradient background
			#define BG_STEPS 88
			int rowH = (clientSize.y/BG_STEPS)+1;
			for( i = 0; i < BG_STEPS; i++ )
			{
				m_bgBrush.SetColour(0, 0, i);
				m_offscreenDc.SetBrush(m_bgBrush);
				m_offscreenDc.DrawRectangle(0, i*rowH, clientSize.x, rowH);
			}
		}

		// draw text (very background)
		{
			m_offscreenDc.SetBackgroundMode(wxTRANSPARENT);
			m_offscreenDc.SetTextForeground(m_textColour);
			m_title->Draw(m_offscreenDc, clientSize, titleChanged, newTitle);
		}

		// draw figures (they lay in backgroud)
		if( m_oscModule->m_showFlags&SJ_OSC_SHOW_FIGURES )
		{
			long bgLight = 100;

			// draw hands (optional)
			m_hands->Draw(m_offscreenDc, clientSize, volume, bgLight, titleChanged);

			// draw rotor (optional)
			m_rotor->Draw(m_offscreenDc, clientSize, m_starfield->IsRunning(), titleChanged, volume, bgLight);

			// draw firework (optional)
			m_firework->Draw(m_offscreenDc, clientSize, titleChanged, m_starfield->IsRunning(), volumeBeat, bgLight);
		}

		// draw starfield (optional)
		m_starfield->Draw(m_offscreenDc, clientSize, false, titleChanged, (m_oscModule->m_showFlags&SJ_OSC_SHOW_STARFIELD)!=0);

		// draw spectrum and/or oscilloscope (for both, the spectrum lays over the oscillosope)
		m_offscreenDc.SetPen(m_fgPen);

		if( m_oscModule->m_showFlags&SJ_OSC_SHOW_OSC )
		{
			m_oscilloscope->Draw(m_offscreenDc, forceOscAnim);
		}

		if( m_oscModule->m_showFlags&SJ_OSC_SHOW_SPECTRUM )
		{
			m_spectrum->Draw(m_offscreenDc, volumeBeat,
						  (m_oscModule->m_showFlags&SJ_OSC_SHOW_FIGURES)? true : false,
						  forceSpectrAnim);
		}

		// draw offscreen bitmap to screen
		wxClientDC dc(this);
		dc.Blit(0, 0, m_offscreenBitmap.GetWidth(), m_offscreenBitmap.GetHeight(), &m_offscreenDc, 0, 0);
	}
}