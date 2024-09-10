void PrefsManager::SaveGlobalPrefsToDisk() const
{
	IniFile ini;

	ini.SetValue( "Options", "CelShadeModels",					m_bCelShadeModels );
	ini.SetValue( "Options", "ConstantUpdateDeltaSeconds",		m_fConstantUpdateDeltaSeconds );
	ini.SetValue( "Options", "DisplayWidth",					m_iDisplayWidth );
	ini.SetValue( "Options", "DisplayHeight",					m_iDisplayHeight );
	ini.SetValue( "Options", "DisplayColorDepth",				m_iDisplayColorDepth );
	ini.SetValue( "Options", "TextureColorDepth",				m_iTextureColorDepth );
	ini.SetValue( "Options", "MovieColorDepth",					m_iMovieColorDepth );
	ini.SetValue( "Options", "MaxTextureResolution",			m_iMaxTextureResolution );
	ini.SetValue( "Options", "RefreshRate",						m_iRefreshRate );
	ini.SetValue( "Options", "UseDedicatedMenuButtons",			m_bOnlyDedicatedMenuButtons );
	ini.SetValue( "Options", "ShowStats",						m_bShowStats );
	ini.SetValue( "Options", "ShowBanners",						m_bShowBanners );
	ini.SetValue( "Options", "BackgroundMode",					m_BackgroundMode);
	ini.SetValue( "Options", "NumBackgrounds",					m_iNumBackgrounds);
	ini.SetValue( "Options", "ShowDanger",						m_bShowDanger );
	ini.SetValue( "Options", "BGBrightness",					m_fBGBrightness );
	ini.SetValue( "Options", "MenuTimer",						m_bMenuTimer );
	ini.SetValue( "Options", "NumArcadeStages",					m_iNumArcadeStages );
	ini.SetValue( "Options", "EventMode",						m_bEventMode );
	ini.SetValue( "Options", "AutoPlay",						m_bAutoPlay );
	ini.SetValue( "Options", "JudgeWindowScale",				m_fJudgeWindowScale );
	ini.SetValue( "Options", "JudgeWindowAdd",					m_fJudgeWindowAdd );
	ini.SetValue( "Options", "JudgeWindowSecondsMarvelous",		m_fJudgeWindowSecondsMarvelous );
	ini.SetValue( "Options", "JudgeWindowSecondsPerfect",		m_fJudgeWindowSecondsPerfect );
	ini.SetValue( "Options", "JudgeWindowSecondsGreat",			m_fJudgeWindowSecondsGreat );
	ini.SetValue( "Options", "JudgeWindowSecondsGood",			m_fJudgeWindowSecondsGood );
	ini.SetValue( "Options", "JudgeWindowSecondsBoo",			m_fJudgeWindowSecondsBoo );
	ini.SetValue( "Options", "JudgeWindowSecondsOK",			m_fJudgeWindowSecondsOK );
	ini.SetValue( "Options", "JudgeWindowSecondsMine",			m_fJudgeWindowSecondsMine );
	ini.SetValue( "Options", "JudgeWindowSecondsAttack",		m_fJudgeWindowSecondsAttack );
	ini.SetValue( "Options", "LifeDifficultyScale",				m_fLifeDifficultyScale );
	ini.SetValue( "Options", "LifeDeltaPercentChangeMarvelous",	m_fLifeDeltaPercentChangeMarvelous );
	ini.SetValue( "Options", "LifeDeltaPercentChangePerfect",	m_fLifeDeltaPercentChangePerfect );
	ini.SetValue( "Options", "LifeDeltaPercentChangeGreat",		m_fLifeDeltaPercentChangeGreat );
	ini.SetValue( "Options", "LifeDeltaPercentChangeGood",		m_fLifeDeltaPercentChangeGood );
	ini.SetValue( "Options", "LifeDeltaPercentChangeBoo",		m_fLifeDeltaPercentChangeBoo );
	ini.SetValue( "Options", "LifeDeltaPercentChangeMiss",		m_fLifeDeltaPercentChangeMiss );
	ini.SetValue( "Options", "LifeDeltaPercentChangeHitMine",	m_fLifeDeltaPercentChangeHitMine );
	ini.SetValue( "Options", "LifeDeltaPercentChangeOK",		m_fLifeDeltaPercentChangeOK );
	ini.SetValue( "Options", "LifeDeltaPercentChangeNG",		m_fLifeDeltaPercentChangeNG );
	ini.SetValue( "Options", "TugMeterPercentChangeMarvelous",	m_fTugMeterPercentChangeMarvelous );
	ini.SetValue( "Options", "TugMeterPercentChangePerfect",	m_fTugMeterPercentChangePerfect );
	ini.SetValue( "Options", "TugMeterPercentChangeGreat",		m_fTugMeterPercentChangeGreat );
	ini.SetValue( "Options", "TugMeterPercentChangeGood",		m_fTugMeterPercentChangeGood );
	ini.SetValue( "Options", "TugMeterPercentChangeBoo",		m_fTugMeterPercentChangeBoo );
	ini.SetValue( "Options", "TugMeterPercentChangeMiss",		m_fTugMeterPercentChangeMiss );
	ini.SetValue( "Options", "TugMeterPercentChangeHitMine",	m_fTugMeterPercentChangeHitMine );
	ini.SetValue( "Options", "TugMeterPercentChangeOK",			m_fTugMeterPercentChangeOK );
	ini.SetValue( "Options", "TugMeterPercentChangeNG",			m_fTugMeterPercentChangeNG );
	ini.SetValue( "Options", "RegenComboAfterFail",				m_iRegenComboAfterFail );
	ini.SetValue( "Options", "RegenComboAfterMiss",				m_iRegenComboAfterMiss );
	ini.SetValue( "Options", "MaxRegenComboAfterFail",			m_iMaxRegenComboAfterFail );
	ini.SetValue( "Options", "MaxRegenComboAfterMiss",			m_iMaxRegenComboAfterMiss );
	ini.SetValue( "Options", "TwoPlayerRecovery",				m_bTwoPlayerRecovery );
	ini.SetValue( "Options", "MercifulDrain",					m_bMercifulDrain );
	ini.SetValue( "Options", "Minimum1FullSongInCourses",		m_bMinimum1FullSongInCourses );

	ini.SetValue( "Options", "PercentScoreWeightMarvelous",		m_iPercentScoreWeightMarvelous );
	ini.SetValue( "Options", "PercentScoreWeightPerfect",		m_iPercentScoreWeightPerfect );
	ini.SetValue( "Options", "PercentScoreWeightGreat",			m_iPercentScoreWeightGreat );
	ini.SetValue( "Options", "PercentScoreWeightGood",			m_iPercentScoreWeightGood );
	ini.SetValue( "Options", "PercentScoreWeightBoo",			m_iPercentScoreWeightBoo );
	ini.SetValue( "Options", "PercentScoreWeightMiss",			m_iPercentScoreWeightMiss );
	ini.SetValue( "Options", "PercentScoreWeightOK",			m_iPercentScoreWeightOK );
	ini.SetValue( "Options", "PercentScoreWeightNG",			m_iPercentScoreWeightNG );
	ini.SetValue( "Options", "PercentScoreWeightHitMine",		m_iPercentScoreWeightHitMine );
	ini.SetValue( "Options", "GradeWeightMarvelous",			m_iGradeWeightMarvelous );
	ini.SetValue( "Options", "GradeWeightPerfect",				m_iGradeWeightPerfect );
	ini.SetValue( "Options", "GradeWeightGreat",				m_iGradeWeightGreat );
	ini.SetValue( "Options", "GradeWeightGood",					m_iGradeWeightGood );
	ini.SetValue( "Options", "GradeWeightBoo",					m_iGradeWeightBoo );
	ini.SetValue( "Options", "GradeWeightMiss",					m_iGradeWeightMiss );
	ini.SetValue( "Options", "GradeWeightHitMine",				m_iGradeWeightHitMine );
	ini.SetValue( "Options", "GradeWeightOK",					m_iGradeWeightOK );
	ini.SetValue( "Options", "GradeWeightNG",					m_iGradeWeightNG );
	
	ini.SetValue( "Options", "NumGradeTiersUsed",				m_iNumGradeTiersUsed );
	for( int g=0; g<NUM_GRADE_TIERS; g++ )
	{
		Grade grade = (Grade)g;
		CString s = GradeToString( grade );
		ini.SetValue( "Options", "GradePercent"+s,				m_fGradePercent[g] );
	}
	ini.SetValue( "Options", "GradeTier02IsAllPerfects",		m_bGradeTier02IsAllPerfects );

	ini.SetValue( "Options", "SuperMeterPercentChangeMarvelous",m_fSuperMeterPercentChangeMarvelous );
	ini.SetValue( "Options", "SuperMeterPercentChangePerfect",	m_fSuperMeterPercentChangePerfect );
	ini.SetValue( "Options", "SuperMeterPercentChangeGreat",	m_fSuperMeterPercentChangeGreat );
	ini.SetValue( "Options", "SuperMeterPercentChangeGood",		m_fSuperMeterPercentChangeGood );
	ini.SetValue( "Options", "SuperMeterPercentChangeBoo",		m_fSuperMeterPercentChangeBoo );
	ini.SetValue( "Options", "SuperMeterPercentChangeMiss",		m_fSuperMeterPercentChangeMiss );
	ini.SetValue( "Options", "SuperMeterPercentChangeHitMine",	m_fSuperMeterPercentChangeHitMine );
	ini.SetValue( "Options", "SuperMeterPercentChangeOK",		m_fSuperMeterPercentChangeOK );
	ini.SetValue( "Options", "SuperMeterPercentChangeNG",		m_fSuperMeterPercentChangeNG );
	ini.SetValue( "Options", "MercifulSuperMeter",				m_bMercifulSuperMeter );

	ini.SetValue( "Options", "DelayedEscape",					m_bDelayedEscape );
	ini.SetValue( "Options", "HiddenSongs",						m_bHiddenSongs );
	ini.SetValue( "Options", "Vsync",							m_bVsync );
	ini.SetValue( "Options", "Interlaced",						m_bInterlaced );
	ini.SetValue( "Options", "PAL",								m_bPAL );
	ini.SetValue( "Options", "HowToPlay",						m_bInstructions );
	ini.SetValue( "Options", "Caution",							m_bShowDontDie );
	ini.SetValue( "Options", "ShowSelectGroup",					m_bShowSelectGroup );
	ini.SetValue( "Options", "ShowNative",						m_bShowNative );
	ini.SetValue( "Options", "ArcadeOptionsNavigation",			m_bArcadeOptionsNavigation );
	ini.SetValue( "Options", "DelayedTextureDelete",			m_bDelayedTextureDelete );
	ini.SetValue( "Options", "TexturePreload",					m_bTexturePreload );
	ini.SetValue( "Options", "DelayedScreenLoad",				m_bDelayedScreenLoad );
	ini.SetValue( "Options", "DelayedModelDelete",				m_bDelayedModelDelete );
	ini.SetValue( "Options", "BannerCache",						m_BannerCache );
	ini.SetValue( "Options", "PalettedBannerCache",				m_bPalettedBannerCache );
	ini.SetValue( "Options", "FastLoad",						m_bFastLoad );
	ini.SetValue( "Options", "MusicWheelUsesSections",			m_MusicWheelUsesSections );
	ini.SetValue( "Options", "MusicWheelSwitchSpeed",			m_iMusicWheelSwitchSpeed );
	ini.SetValue( "Options", "EasterEggs",						m_bEasterEggs );
	ini.SetValue( "Options", "MarvelousTiming",					m_iMarvelousTiming );
	ini.SetValue( "Options", "CoinMode",						m_iCoinMode );
	ini.SetValue( "Options", "CoinsPerCredit",					m_iCoinsPerCredit );
	ini.SetValue( "Options", "Premium",							m_Premium );
	ini.SetValue( "Options", "DelayedCreditsReconcile",			m_bDelayedCreditsReconcile );
	ini.SetValue( "Options", "BoostAppPriority",				m_iBoostAppPriority );
	ini.SetValue( "Options", "PickExtraStage",					m_bPickExtraStage );
	ini.SetValue( "Options", "ComboContinuesBetweenSongs",		m_bComboContinuesBetweenSongs );
	ini.SetValue( "Options", "LongVerSeconds",					m_fLongVerSongSeconds );
	ini.SetValue( "Options", "MarathonVerSeconds",				m_fMarathonVerSongSeconds );
	ini.SetValue( "Options", "ShowSongOptions",					m_ShowSongOptions );
	ini.SetValue( "Options", "AllowUnacceleratedRenderer",		m_bAllowUnacceleratedRenderer );
	ini.SetValue( "Options", "ThreadedInput",					m_bThreadedInput );
	ini.SetValue( "Options", "ThreadedMovieDecode",				m_bThreadedMovieDecode );
	ini.SetValue( "Options", "ScreenTestMode",					m_bScreenTestMode );
	ini.SetValue( "Options", "MachineName",						m_sMachineName );
	ini.SetValue( "Options", "IgnoredMessageWindows",			m_sIgnoredMessageWindows );
	ini.SetValue( "Options", "SoloSingle",						m_bSoloSingle );
	ini.SetValue( "Options", "DancePointsForOni",				m_bDancePointsForOni );
	ini.SetValue( "Options", "PercentageScoring",				m_bPercentageScoring );
	ini.SetValue( "Options", "MinPercentageForMachineSongHighScore",	m_fMinPercentageForMachineSongHighScore );
	ini.SetValue( "Options", "MinPercentageForMachineCourseHighScore",	m_fMinPercentageForMachineCourseHighScore );
	ini.SetValue( "Options", "Disqualification",				m_bDisqualification );
	ini.SetValue( "Options", "ShowLyrics",						m_bShowLyrics );
	ini.SetValue( "Options", "AutogenSteps",					m_bAutogenSteps );
	ini.SetValue( "Options", "AutogenGroupCourses",				m_bAutogenGroupCourses );
	ini.SetValue( "Options", "BreakComboToGetItem",				m_bBreakComboToGetItem );
	ini.SetValue( "Options", "LockCourseDifficulties",			m_bLockCourseDifficulties );
	ini.SetValue( "Options", "ShowDancingCharacters",			m_ShowDancingCharacters );
	ini.SetValue( "Options", "UseUnlockSystem",					m_bUseUnlockSystem );
	ini.SetValue( "Options", "FirstRun",						m_bFirstRun );
	ini.SetValue( "Options", "AutoMapJoysticks",				m_bAutoMapOnJoyChange );
	ini.SetValue( "Options", "CpuClock",						m_iCpuClock );
	ini.SetValue( "Options", "CoursesToShowRanking",			m_sCoursesToShowRanking );
	ini.SetValue( "Options", "GetRankingName",					m_iGetRankingName );
	ini.SetValue( "Options", "SmoothLines",						m_bSmoothLines );
	ini.SetValue( "Options", "GlobalOffsetSeconds",				m_fGlobalOffsetSeconds );

	ini.SetValue( "Options", "CourseSortOrder",					m_iCourseSortOrder );
	ini.SetValue( "Options", "MoveRandomToEnd",					m_bMoveRandomToEnd );
	ini.SetValue( "Options", "SubSortByNumSteps",				m_bSubSortByNumSteps );

	ini.SetValue( "Options", "ScoringType",						m_iScoringType );

	ini.SetValue( "Options", "ProgressiveLifebar",				m_iProgressiveLifebar );
	ini.SetValue( "Options", "ProgressiveStageLifebar",			m_iProgressiveStageLifebar );
	ini.SetValue( "Options", "ProgressiveNonstopLifebar",		m_iProgressiveNonstopLifebar );
	ini.SetValue( "Options", "ShowBeginnerHelper",				m_bShowBeginnerHelper );
	ini.SetValue( "Options", "Language",						m_sLanguage );
	ini.SetValue( "Options", "EndlessBreakEnabled",				m_bEndlessBreakEnabled );
	ini.SetValue( "Options", "EndlessStagesUntilBreak",			m_iEndlessNumStagesUntilBreak );
	ini.SetValue( "Options", "EndlessBreakLength",				m_iEndlessBreakLength );
	ini.SetValue( "Options", "DisableScreenSaver",				m_bDisableScreenSaver );

	ini.SetValue( "Options", "ProductID",						m_iProductID );
	FOREACH_PlayerNumber( p )
		ini.SetValue( "Options", ssprintf("DefaultLocalProfileIDP%d",p+1),	m_sDefaultLocalProfileID[p] );

	ini.SetValue( "Options", "CenterImageTranslateX",			m_iCenterImageTranslateX );
	ini.SetValue( "Options", "CenterImageTranslateY",			m_iCenterImageTranslateY );
	ini.SetValue( "Options", "CenterImageScaleX",				m_fCenterImageScaleX );
	ini.SetValue( "Options", "CenterImageScaleY",				m_fCenterImageScaleY );
	ini.SetValue( "Options", "AttractSoundFrequency",			m_iAttractSoundFrequency );
	ini.SetValue( "Options", "AllowExtraStage",					m_bAllowExtraStage );
	ini.SetValue( "Options", "HideDefaultNoteSkin",				m_bHideDefaultNoteSkin );
	ini.SetValue( "Options", "MaxHighScoresPerListForMachine",	m_iMaxHighScoresPerListForMachine );
	ini.SetValue( "Options", "MaxHighScoresPerListForPlayer",	m_iMaxHighScoresPerListForPlayer );
	ini.SetValue( "Options", "PadStickSeconds",					m_fPadStickSeconds );
	ini.SetValue( "Options", "ForceMipMaps",					m_bForceMipMaps );
	ini.SetValue( "Options", "TrilinearFiltering",				m_bTrilinearFiltering );
	ini.SetValue( "Options", "AnisotropicFiltering",			m_bAnisotropicFiltering );
	ini.SetValue( "Options", "AutoRestart",						g_bAutoRestart );
	
	ini.SetValue( "Options", "SoundWriteAhead",					m_iSoundWriteAhead );

	/* Only write these if they aren't the default.  This ensures that we can change
	 * the default and have it take effect for everyone (except people who
	 * tweaked this value). */
	if(m_fSoundVolume != DEFAULT_SOUND_VOLUME)
		ini.SetValue( "Options", "SoundVolume",					m_fSoundVolume );

	ini.SetValue( "Options", "AdditionalSongFolders", 			m_sAdditionalSongFolders);
	ini.SetValue( "Options", "AdditionalFolders", 				m_sAdditionalFolders);

	ini.SetValue( "Debug", "LogToDisk",							m_bLogToDisk );
	ini.SetValue( "Debug", "ForceLogFlush",						m_bForceLogFlush );
	ini.SetValue( "Debug", "ShowLogOutput",						m_bShowLogOutput );
	ini.SetValue( "Debug", "Timestamping",						m_bTimestamping );
	ini.SetValue( "Debug", "LogSkips",							m_bLogSkips );
	ini.SetValue( "Debug", "LogCheckpoints",					m_bLogCheckpoints );
	ini.SetValue( "Debug", "ShowLoadingWindow",					m_bShowLoadingWindow );

	FOREACH_CONST( IPreference*, *g_pvpSubscribers, p ) (*p)->WriteTo( ini );

	ini.WriteFile( STEPMANIA_INI_PATH );
}