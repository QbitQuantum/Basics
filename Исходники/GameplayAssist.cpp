void GameplayAssist::PlayTicks( const NoteData &nd, const PlayerState *ps )
{
	using std::max;
	bool bClap = GAMESTATE->m_SongOptions.GetCurrent().m_bAssistClap;
	bool bMetronome = GAMESTATE->m_SongOptions.GetCurrent().m_bAssistMetronome;
	if( !bClap  &&  !bMetronome )
		return;

	// don't play sounds for dead players
	if( ps->m_HealthState == HealthState_Dead )
		return;

	/* Sound cards have a latency between when a sample is Play()ed and when the sound
	 * will start coming out the speaker.  Compensate for this by boosting fPositionSeconds
	 * ahead.  This is just to make sure that we request the sound early enough for it to
	 * come out on time; the actual precise timing is handled by SetStartTime. */
	SongPosition &position = GAMESTATE->m_pPlayerState[ps->m_PlayerNumber]->m_Position;
	float fPositionSeconds = position.m_fMusicSeconds;

	//float fPositionSeconds = GAMESTATE->m_Position.m_fMusicSeconds;
	fPositionSeconds += SOUNDMAN->GetPlayLatency() + (float)CommonMetrics::TICK_EARLY_SECONDS + 0.250f;
	const TimingData &timing = *GAMESTATE->m_pCurSteps[ps->m_PlayerNumber]->GetTimingData();
	const float fSongBeat = timing.GetBeatFromElapsedTimeNoOffset( fPositionSeconds );

	const int iSongRow = max( 0, BeatToNoteRowNotRounded( fSongBeat ) );
	static int iRowLastCrossed = -1;
	if( iSongRow < iRowLastCrossed )
		iRowLastCrossed = iSongRow;

	if( bClap )
	{
		int iClapRow = -1;
		// for each index we crossed since the last update:
		FOREACH_NONEMPTY_ROW_ALL_TRACKS_RANGE( nd, r, iRowLastCrossed+1, iSongRow+1 )
			if( nd.IsThereATapOrHoldHeadAtRow( r ) )
				iClapRow = r;

		if( iClapRow != -1 && timing.IsJudgableAtRow(iClapRow))
		{
			const float fTickBeat = NoteRowToBeat( iClapRow );
			const float fTickSecond = timing.GetElapsedTimeFromBeatNoOffset( fTickBeat );
			float fSecondsUntil = fTickSecond - position.m_fMusicSeconds;
			fSecondsUntil /= GAMESTATE->m_SongOptions.GetCurrent().m_fMusicRate; /* 2x music rate means the time until the tick is halved */

			RageSoundParams p;
			p.m_StartTime = position.m_LastBeatUpdate  + (fSecondsUntil - (float)CommonMetrics::TICK_EARLY_SECONDS);
			m_soundAssistClap.Play(false, &p);
		}
	}

	if( bMetronome && iRowLastCrossed != -1 )
	{
		//iRowLastCrossed+1, iSongRow+1

		int iLastCrossedMeasureIndex;
		int iLastCrossedBeatIndex;
		int iLastCrossedRowsRemainder;
		timing.NoteRowToMeasureAndBeat( iRowLastCrossed, iLastCrossedMeasureIndex, iLastCrossedBeatIndex, iLastCrossedRowsRemainder );

		int iCurrentMeasureIndex;
		int iCurrentBeatIndex;
		int iCurrentRowsRemainder;
		timing.NoteRowToMeasureAndBeat( iSongRow, iCurrentMeasureIndex, iCurrentBeatIndex, iCurrentRowsRemainder );

		int iMetronomeRow = -1;
		bool bIsMeasure = false;

		if( iLastCrossedMeasureIndex != iCurrentMeasureIndex  ||  iLastCrossedBeatIndex != iCurrentBeatIndex )
		{
			iMetronomeRow = iSongRow - iCurrentRowsRemainder;
			bIsMeasure = iCurrentBeatIndex == 0  &&  iCurrentRowsRemainder == 0;
		}

		if( iMetronomeRow != -1 )
		{
			const float fTickBeat = NoteRowToBeat( iMetronomeRow );
			const float fTickSecond = timing.GetElapsedTimeFromBeatNoOffset( fTickBeat );
			float fSecondsUntil = fTickSecond - position.m_fMusicSeconds;
			fSecondsUntil /= GAMESTATE->m_SongOptions.GetCurrent().m_fMusicRate; /* 2x music rate means the time until the tick is halved */

			RageSoundParams p;
			p.m_StartTime = position.m_LastBeatUpdate  + (fSecondsUntil - (float)CommonMetrics::TICK_EARLY_SECONDS);
			if( bIsMeasure )
				m_soundAssistMetronomeMeasure.Play(false, &p);
			else
				m_soundAssistMetronomeBeat.Play(false, &p);
		}
	}

	iRowLastCrossed = iSongRow;
}