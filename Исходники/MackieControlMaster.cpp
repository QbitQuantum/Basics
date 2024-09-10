CMackieControlMaster::CMackieControlMaster()
{
//	TRACE("CMackieControlMaster::CMackieControlMaster()\n");

	m_bExpectedDeviceType = 0x14;

	m_bWasInEQFreqGainMode = false;

	m_eCurrentTransportDir = DIR_FORWARD;
	m_fTransportTimeout = 0;

	m_bKeyRepeatKey = 0;
	m_fKeyRepeatTimeout = 0;
	
	int n = 0;

	// Wire everything up together
	for (n = 0; n < NUM_VSELECT_DISPLAY_CELLS; n++)
		m_cVSelectDisplay[n].Setup(this, 0x0A + NUM_VSELECT_DISPLAY_CELLS - n - 1);

	for (n = 0; n < NUM_TIME_CODE_DISPLAY_CELLS; n++)
		m_cTimeCodeDisplay[n].Setup(this, NUM_TIME_CODE_DISPLAY_CELLS - n - 1);

	m_HwMasterFader.Setup(this, 8);

	CCriticalSectionAuto csa(m_cState.GetCS());

	// Default user key and foot bindings
	m_cState.SetUserFunctionKey(0, CMD_VIEW_NEW_EXPLORER);
	m_cState.SetUserFunctionKey(1, CMD_VIEW_NEW_LOOP_CONSTR);
	m_cState.SetUserFunctionKey(2, CMD_VIEW_CONSOLE);
	m_cState.SetUserFunctionKey(3, CMD_VIEW_NEW_EVENT_LIST);
	m_cState.SetUserFunctionKey(4, CMD_VIEW_NEW_PIANO_ROLL);
	m_cState.SetUserFunctionKey(5, CMD_VIEW_VIDEO);
	m_cState.SetUserFunctionKey(6, CMD_VIEW_NEW_STAFF);
	m_cState.SetUserFunctionKey(7, CMD_VIEW_NEW_LYRICS);
	m_cState.SetUserFootSwitch(0, CMD_REALTIME_PLAY);
	m_cState.SetUserFootSwitch(1, CMD_REALTIME_RECORD);

	TIMECAPS timeDevCaps;
	timeGetDevCaps(&timeDevCaps, sizeof(timeDevCaps));
	TRACE("timeDevCaps.wPeriodMin = %d\n", timeDevCaps.wPeriodMin);
	m_wTransportTimerPeriod = max(timeDevCaps.wPeriodMin, 10);
	m_wKeyRepeatTimerPeriod = max(timeDevCaps.wPeriodMin, 10);
	m_bTransportTimerActive = false;
	m_bKeyRepeatTimerActive = false;
}