void Song::processNextBuffer()
{
	// if not playing, nothing to do
	if( m_playing == false )
	{
		return;
	}

	TrackList trackList;
	int tcoNum = -1; // track content object number

	// determine the list of tracks to play and the track content object
	// (TCO) number
	switch( m_playMode )
	{
		case Mode_PlaySong:
			trackList = tracks();
			// at song-start we have to reset the LFOs
			if( m_playPos[Mode_PlaySong] == 0 )
			{
				EnvelopeAndLfoParameters::instances()->reset();
			}
			break;

		case Mode_PlayBB:
			if( Engine::getBBTrackContainer()->numOfBBs() > 0 )
			{
				tcoNum = Engine::getBBTrackContainer()->
								currentBB();
				trackList.push_back( BBTrack::findBBTrack(
								tcoNum ) );
			}
			break;

		case Mode_PlayPattern:
			if( m_patternToPlay != NULL )
			{
				tcoNum = m_patternToPlay->getTrack()->
						getTCONum( m_patternToPlay );
				trackList.push_back(
						m_patternToPlay->getTrack() );
			}
			break;

		default:
			return;

	}

	// if we have no tracks to play, nothing to do
	if( trackList.empty() == true )
	{
		return;
	}

	// check for looping-mode and act if necessary
	TimeLineWidget * tl = m_playPos[m_playMode].m_timeLine;
	bool checkLoop =
		tl != NULL && m_exporting == false && tl->loopPointsEnabled();

	if( checkLoop )
	{
		// if looping-mode is enabled and we are outside of the looping
		// range, go to the beginning of the range
		if( m_playPos[m_playMode] < tl->loopBegin() ||
					m_playPos[m_playMode] >= tl->loopEnd() )
		{
			setToTime(tl->loopBegin());
			m_playPos[m_playMode].setTicks(
						tl->loopBegin().getTicks() );
			emit updateSampleTracks();
		}
	}

	f_cnt_t framesPlayed = 0;
	const float framesPerTick = Engine::framesPerTick();

	while( framesPlayed < Engine::mixer()->framesPerPeriod() )
	{
		m_vstSyncController.update();

		float currentFrame = m_playPos[m_playMode].currentFrame();
		// did we play a tick?
		if( currentFrame >= framesPerTick )
		{
			int ticks = m_playPos[m_playMode].getTicks() +
				( int )( currentFrame / framesPerTick );

			m_vstSyncController.setAbsolutePosition( ticks );

			// did we play a whole tact?
			if( ticks >= MidiTime::ticksPerTact() )
			{
				// per default we just continue playing even if
				// there's no more stuff to play
				// (song-play-mode)
				int maxTact = m_playPos[m_playMode].getTact()
									+ 2;

				// then decide whether to go over to next tact
				// or to loop back to first tact
				if( m_playMode == Mode_PlayBB )
				{
					maxTact = Engine::getBBTrackContainer()
							->lengthOfCurrentBB();
				}
				else if( m_playMode == Mode_PlayPattern &&
					m_loopPattern == true &&
					tl != NULL &&
					tl->loopPointsEnabled() == false )
				{
					maxTact = m_patternToPlay->length()
								.getTact();
				}

				// end of played object reached?
				if( m_playPos[m_playMode].getTact() + 1
								>= maxTact )
				{
					// then start from beginning and keep
					// offset
					ticks %= ( maxTact * MidiTime::ticksPerTact() );

					// wrap milli second counter
					setToTimeByTicks(ticks);

					m_vstSyncController.setAbsolutePosition( ticks );
				}
			}
			m_playPos[m_playMode].setTicks( ticks );

			if( checkLoop )
			{
				m_vstSyncController.startCycle(
					tl->loopBegin().getTicks(), tl->loopEnd().getTicks() );

				// if looping-mode is enabled and we have got
				// past the looping range, return to the
				// beginning of the range
				if( m_playPos[m_playMode] >= tl->loopEnd() )
				{
					m_playPos[m_playMode].setTicks( tl->loopBegin().getTicks() );
					setToTime(tl->loopBegin());
				}
				else if( m_playPos[m_playMode] == tl->loopEnd() - 1 )
				{
					emit updateSampleTracks();
				}
			}
			else
			{
				m_vstSyncController.stopCycle();
			}

			currentFrame = fmodf( currentFrame, framesPerTick );
			m_playPos[m_playMode].setCurrentFrame( currentFrame );
		}

		f_cnt_t framesToPlay =
			Engine::mixer()->framesPerPeriod() - framesPlayed;

		f_cnt_t framesLeft = ( f_cnt_t )framesPerTick -
						( f_cnt_t )currentFrame;
		// skip last frame fraction
		if( framesLeft == 0 )
		{
			++framesPlayed;
			m_playPos[m_playMode].setCurrentFrame( currentFrame
								+ 1.0f );
			continue;
		}
		// do we have samples left in this tick but these are less
		// than samples we have to play?
		if( framesLeft < framesToPlay )
		{
			// then set framesToPlay to remaining samples, the
			// rest will be played in next loop
			framesToPlay = framesLeft;
		}

		if( ( f_cnt_t ) currentFrame == 0 )
		{
			processAutomations(trackList, m_playPos[m_playMode], framesToPlay);

			// loop through all tracks and play them
			for( int i = 0; i < trackList.size(); ++i )
			{
				trackList[i]->play( m_playPos[m_playMode],
						framesToPlay,
						framesPlayed, tcoNum );
			}
		}

		// update frame-counters
		framesPlayed += framesToPlay;
		m_playPos[m_playMode].setCurrentFrame( framesToPlay +
								currentFrame );
		m_elapsedMilliSeconds += MidiTime::ticksToMilliseconds( framesToPlay / framesPerTick, getTempo());
		m_elapsedTacts = m_playPos[Mode_PlaySong].getTact();
		m_elapsedTicks = ( m_playPos[Mode_PlaySong].getTicks() % ticksPerTact() ) / 48;
	}
}