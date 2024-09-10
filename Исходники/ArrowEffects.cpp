float ArrowEffects::GetXPos( const PlayerState* pPlayerState, int iColNum, float fYOffset ) 
{
	float fPixelOffsetFromCenter = 0; // fill this in below

	const Style* pStyle = GAMESTATE->GetCurrentStyle(pPlayerState->m_PlayerNumber);
	const float* fEffects = pPlayerState->m_PlayerOptions.GetCurrent().m_fEffects;

	// TODO: Don't index by PlayerNumber.
	const Style::ColumnInfo* pCols = pStyle->m_ColumnInfo[pPlayerState->m_PlayerNumber];
	PerPlayerData &data = g_EffectData[pPlayerState->m_PlayerNumber];

	if( fEffects[PlayerOptions::EFFECT_TORNADO] != 0 )
	{
		const float fRealPixelOffset = pCols[iColNum].fXOffset * pPlayerState->m_NotefieldZoom;
		const float fPositionBetween = SCALE( fRealPixelOffset, data.m_fMinTornadoX[iColNum], data.m_fMaxTornadoX[iColNum], 
						     TORNADO_POSITION_SCALE_TO_LOW, TORNADO_POSITION_SCALE_TO_HIGH );
		float fRads = acosf( fPositionBetween );
		fRads += fYOffset * TORNADO_OFFSET_FREQUENCY / SCREEN_HEIGHT;

		const float fAdjustedPixelOffset = SCALE( RageFastCos(fRads), TORNADO_OFFSET_SCALE_FROM_LOW, TORNADO_OFFSET_SCALE_FROM_HIGH, 
							 data.m_fMinTornadoX[iColNum], data.m_fMaxTornadoX[iColNum] );

		fPixelOffsetFromCenter += (fAdjustedPixelOffset - fRealPixelOffset) * fEffects[PlayerOptions::EFFECT_TORNADO];
	}

	if( fEffects[PlayerOptions::EFFECT_DRUNK] != 0 )
		fPixelOffsetFromCenter += fEffects[PlayerOptions::EFFECT_DRUNK] * 
			( RageFastCos( RageTimer::GetTimeSinceStartFast() + iColNum*DRUNK_COLUMN_FREQUENCY
				      + fYOffset*DRUNK_OFFSET_FREQUENCY/SCREEN_HEIGHT) * ARROW_SIZE*DRUNK_ARROW_MAGNITUDE );
	if( fEffects[PlayerOptions::EFFECT_FLIP] != 0 )
	{
		const int iFirstCol = 0;
		const int iLastCol = pStyle->m_iColsPerPlayer-1;
		const int iNewCol = SCALE( iColNum, iFirstCol, iLastCol, iLastCol, iFirstCol );
		const float fOldPixelOffset = pCols[iColNum].fXOffset * pPlayerState->m_NotefieldZoom;
		const float fNewPixelOffset = pCols[iNewCol].fXOffset * pPlayerState->m_NotefieldZoom;
		const float fDistance = fNewPixelOffset - fOldPixelOffset;
		fPixelOffsetFromCenter += fDistance * fEffects[PlayerOptions::EFFECT_FLIP];
	}
	if( fEffects[PlayerOptions::EFFECT_INVERT] != 0 )
		fPixelOffsetFromCenter += data.m_fInvertDistance[iColNum] * fEffects[PlayerOptions::EFFECT_INVERT];

	if( fEffects[PlayerOptions::EFFECT_BEAT] != 0 )
	{
		const float fShift = data.m_fBeatFactor*RageFastSin( fYOffset / BEAT_OFFSET_HEIGHT + PI/BEAT_PI_HEIGHT );
		fPixelOffsetFromCenter += fEffects[PlayerOptions::EFFECT_BEAT] * fShift;
	}

	if( fEffects[PlayerOptions::EFFECT_XMODE] != 0 )
	{
		// based off of code by v1toko for StepNXA, except it should work on
		// any gametype now.
		switch( pStyle->m_StyleType )
		{
			case StyleType_OnePlayerTwoSides:
			case StyleType_TwoPlayersSharedSides: // fall through?
				{
					// find the middle, and split based on iColNum
					// it's unknown if this will work for routine.
					const int iMiddleColumn = static_cast<int>(floor(pStyle->m_iColsPerPlayer/2.0f));
					if( iColNum > iMiddleColumn-1 )
						fPixelOffsetFromCenter += fEffects[PlayerOptions::EFFECT_XMODE]*-(fYOffset);
					else
						fPixelOffsetFromCenter += fEffects[PlayerOptions::EFFECT_XMODE]*fYOffset;
				}
				break;
			case StyleType_OnePlayerOneSide:
			case StyleType_TwoPlayersTwoSides: // fall through
				{
					// the code was the same for both of these cases in StepNXA.
					if( pPlayerState->m_PlayerNumber == PLAYER_2 )
						fPixelOffsetFromCenter += fEffects[PlayerOptions::EFFECT_XMODE]*-(fYOffset);
					else
						fPixelOffsetFromCenter += fEffects[PlayerOptions::EFFECT_XMODE]*fYOffset;
				}
				break;
			DEFAULT_FAIL(pStyle->m_StyleType);
		}
	}

	fPixelOffsetFromCenter += pCols[iColNum].fXOffset * pPlayerState->m_NotefieldZoom;

	if( fEffects[PlayerOptions::EFFECT_TINY] != 0 )
	{
		// Allow Tiny to pull tracks together, but not to push them apart.
		float fTinyPercent = fEffects[PlayerOptions::EFFECT_TINY];
		fTinyPercent = min( powf(TINY_PERCENT_BASE, fTinyPercent), (float)TINY_PERCENT_GATE );
		fPixelOffsetFromCenter *= fTinyPercent;
	}

	return fPixelOffsetFromCenter;
}