void ScreenEvaluation::Init()
{
	LOG->Trace( "ScreenEvaluation::Init()" );

	// debugging
	// Only fill StageStats with fake info if we're the InitialScreen
	// (i.e. StageStats not already filled)
	if( PREFSMAN->m_sTestInitialScreen.Get() == m_sName )
	{
		PROFILEMAN->LoadFirstAvailableProfile(PLAYER_1);
		PROFILEMAN->LoadFirstAvailableProfile(PLAYER_2);

		STATSMAN->m_vPlayedStageStats.clear();
		STATSMAN->m_vPlayedStageStats.push_back( StageStats() );
		StageStats &ss = STATSMAN->m_vPlayedStageStats.back();

		GAMESTATE->m_PlayMode.Set( PLAY_MODE_REGULAR );
		GAMESTATE->SetCurrentStyle( GAMEMAN->GameAndStringToStyle(GAMEMAN->GetDefaultGame(),"versus"), PLAYER_INVALID );
		ss.m_playMode = GAMESTATE->m_PlayMode;
		ss.m_Stage = Stage_1st;
		enum_add( ss.m_Stage, rand()%3 );
		ss.m_EarnedExtraStage = (EarnedExtraStage)(rand() % NUM_EarnedExtraStage);
		GAMESTATE->SetMasterPlayerNumber(PLAYER_1);
		GAMESTATE->m_pCurSong.Set( SONGMAN->GetRandomSong() );
		ss.m_vpPlayedSongs.push_back( GAMESTATE->m_pCurSong );
		ss.m_vpPossibleSongs.push_back( GAMESTATE->m_pCurSong );
		GAMESTATE->m_pCurCourse.Set( SONGMAN->GetRandomCourse() );
		GAMESTATE->m_iCurrentStageIndex = 0;
		FOREACH_ENUM( PlayerNumber, p )
			GAMESTATE->m_iPlayerStageTokens[p] = 1;

		FOREACH_PlayerNumber( p )
		{
			ss.m_player[p].m_pStyle = GAMESTATE->GetCurrentStyle(p);
			if( RandomInt(2) )
				PO_GROUP_ASSIGN_N( GAMESTATE->m_pPlayerState[p]->m_PlayerOptions, ModsLevel_Stage, m_bTransforms, PlayerOptions::TRANSFORM_ECHO, true );	// show "disqualified"
			SO_GROUP_ASSIGN( GAMESTATE->m_SongOptions, ModsLevel_Stage, m_fMusicRate, 1.1f );

			GAMESTATE->JoinPlayer( p );
			GAMESTATE->m_pCurSteps[p].Set( GAMESTATE->m_pCurSong->GetAllSteps()[0] );
			if( GAMESTATE->m_pCurCourse )
			{
				vector<Trail*> apTrails;
				GAMESTATE->m_pCurCourse->GetAllTrails( apTrails );
				if( apTrails.size() )
					GAMESTATE->m_pCurTrail[p].Set( apTrails[0] );
			}
			ss.m_player[p].m_vpPossibleSteps.push_back( GAMESTATE->m_pCurSteps[PLAYER_1] );
			ss.m_player[p].m_iStepsPlayed = 1;

			PO_GROUP_ASSIGN( GAMESTATE->m_pPlayerState[p]->m_PlayerOptions, ModsLevel_Stage, m_fScrollSpeed, 2.0f );
			PO_GROUP_CALL( GAMESTATE->m_pPlayerState[p]->m_PlayerOptions, ModsLevel_Stage, ChooseRandomModifiers );
		}

		for( float f = 0; f < 100.0f; f += 1.0f )
		{
			float fP1 = fmodf(f/100*4+.3f,1);
			ss.m_player[PLAYER_1].SetLifeRecordAt( fP1, f );
			ss.m_player[PLAYER_2].SetLifeRecordAt( 1-fP1, f );
		}

		FOREACH_PlayerNumber( p )
		{
			float fSeconds = GAMESTATE->m_pCurSong->GetStepsSeconds();
			ss.m_player[p].m_iActualDancePoints = RandomInt( 3 );
			ss.m_player[p].m_iPossibleDancePoints = 2;
			if( RandomInt(2) )
				ss.m_player[p].m_iCurCombo = RandomInt(15000);
			else
				ss.m_player[p].m_iCurCombo = 0;
			ss.m_player[p].UpdateComboList( 0, true );

			ss.m_player[p].m_iCurCombo += 50;
			ss.m_player[p].UpdateComboList( 0.10f * fSeconds, false );

			ss.m_player[p].m_iCurCombo = 0;
			ss.m_player[p].UpdateComboList( 0.15f * fSeconds, false );
			ss.m_player[p].m_iCurCombo = 1;
			ss.m_player[p].UpdateComboList( 0.25f * fSeconds, false );
			ss.m_player[p].m_iCurCombo = 50;
			ss.m_player[p].UpdateComboList( 0.35f * fSeconds, false );
			ss.m_player[p].m_iCurCombo = 0;
			ss.m_player[p].UpdateComboList( 0.45f * fSeconds, false );
			ss.m_player[p].m_iCurCombo = 1;
			ss.m_player[p].UpdateComboList( 0.50f * fSeconds, false );
			ss.m_player[p].m_iCurCombo = 100;
			ss.m_player[p].UpdateComboList( 1.00f * fSeconds, false );
			if( RandomInt(5) == 0 )
			{
				ss.m_player[p].m_bFailed = true;
			}
			ss.m_player[p].m_iTapNoteScores[TNS_W1] = RandomInt( 3 );
			ss.m_player[p].m_iTapNoteScores[TNS_W2] = RandomInt( 3 );
			ss.m_player[p].m_iTapNoteScores[TNS_W3] = RandomInt( 3 );
			ss.m_player[p].m_iPossibleGradePoints = 4*ScoreKeeperNormal::TapNoteScoreToGradePoints(TNS_W1, false);
			ss.m_player[p].m_fLifeRemainingSeconds = randomf( 90, 580 );
			ss.m_player[p].m_iScore = rand() % (900*1000*1000);
			ss.m_player[p].m_iPersonalHighScoreIndex = (rand() % 3) - 1;
			ss.m_player[p].m_iMachineHighScoreIndex = (rand() % 3) - 1;
			ss.m_player[p].m_PeakComboAward = (PeakComboAward)(rand()%NUM_PeakComboAward);
			ss.m_player[p].m_StageAward = (StageAward)(rand()%NUM_StageAward);

			FOREACH_ENUM( RadarCategory, rc )
			{
				switch( rc )
				{
					case RadarCategory_Stream:
					case RadarCategory_Voltage:
					case RadarCategory_Air:
					case RadarCategory_Freeze:
					case RadarCategory_Chaos:
						ss.m_player[p].m_radarPossible[rc] = randomf( 0, 1 );
						ss.m_player[p].m_radarActual[rc] = randomf( 0, ss.m_player[p].m_radarPossible[rc] );
						break;
					case RadarCategory_TapsAndHolds:
					case RadarCategory_Jumps:
					case RadarCategory_Holds:
					case RadarCategory_Mines:
					case RadarCategory_Hands:
					case RadarCategory_Rolls:
					case RadarCategory_Lifts:
					case RadarCategory_Fakes:
						ss.m_player[p].m_radarPossible[rc] = 1 + (rand() % 200);
						ss.m_player[p].m_radarActual[rc] = rand() % (int)(ss.m_player[p].m_radarPossible[rc]);
						break;
					default: break;
				}

				;	// filled in by ScreenGameplay on start of notes
			}
		}
	}