void ContinueExecution()
{
	static BOOL pageflipping    = 0; //?

	const double fUsecPerSec        = 1.e6;
#if 1
	const UINT nExecutionPeriodUsec = 1000;		// 1.0ms
//	const UINT nExecutionPeriodUsec = 100;		// 0.1ms
	const double fExecutionPeriodClks = g_fCurrentCLK6502 * ((double)nExecutionPeriodUsec / fUsecPerSec);
#else
	const double fExecutionPeriodClks = 1800.0;
	const UINT nExecutionPeriodUsec = (UINT) (fUsecPerSec * (fExecutionPeriodClks / g_fCurrentCLK6502));
#endif

	//

	bool bScrollLock_FullSpeed = g_uScrollLockToggle
									? g_bScrollLock_FullSpeed
									: (GetKeyState(VK_SCROLL) < 0);

	g_bFullSpeed = ( (g_dwSpeed == SPEED_MAX) || 
					 bScrollLock_FullSpeed ||
					 (DiskIsSpinning() && enhancedisk && !Spkr_IsActive() && !MB_IsActive()) );

	if(g_bFullSpeed)
	{
		// Don't call Spkr_Mute() - will get speaker clicks
		MB_Mute();
		SysClk_StopTimer();

		g_nCpuCyclesFeedback = 0;	// For the case when this is a big -ve number
	}
	else
	{
		// Don't call Spkr_Demute()
		MB_Demute();
		SysClk_StartTimerUsec(nExecutionPeriodUsec);
	}

	//

	int nCyclesToExecute = (int) fExecutionPeriodClks + g_nCpuCyclesFeedback;
	if(nCyclesToExecute < 0)
		nCyclesToExecute = 0;

	DWORD dwExecutedCycles = CpuExecute(nCyclesToExecute);

	g_dwCyclesThisFrame += dwExecutedCycles;

	//

	cyclenum = dwExecutedCycles;

	DiskUpdatePosition(dwExecutedCycles);
	JoyUpdatePosition();
	VideoUpdateVbl(g_dwCyclesThisFrame);

	SpkrUpdate(cyclenum);
	sg_SSC.CommUpdate(cyclenum);
	PrintUpdate(cyclenum);

	//

	const DWORD CLKS_PER_MS = (DWORD)g_fCurrentCLK6502 / 1000;

	emulmsec_frac += dwExecutedCycles;
	if(emulmsec_frac > CLKS_PER_MS)
	{
		emulmsec += emulmsec_frac / CLKS_PER_MS;
		emulmsec_frac %= CLKS_PER_MS;
	}

	//
	// DETERMINE WHETHER THE SCREEN WAS UPDATED, THE DISK WAS SPINNING,
	// OR THE KEYBOARD I/O PORTS WERE BEING EXCESSIVELY QUERIED THIS CLOCKTICK
	VideoCheckPage(0);
	BOOL screenupdated = VideoHasRefreshed();
	BOOL systemidle    = 0;	//(KeybGetNumQueries() > (clockgran << 2));	//  && (!ranfinegrain);	// TO DO

	if(screenupdated)
		pageflipping = 3;

	//

	if(g_dwCyclesThisFrame >= dwClksPerFrame)
	{
		g_dwCyclesThisFrame -= dwClksPerFrame;

		if(g_nAppMode != MODE_LOGO)
		{
			VideoUpdateFlash();

			static BOOL  anyupdates     = 0;
			static DWORD lastcycles     = 0;
			static BOOL  lastupdates[2] = {0,0};

			anyupdates |= screenupdated;

			//

			lastcycles = cumulativecycles;
			if ((!anyupdates) && (!lastupdates[0]) && (!lastupdates[1]) && VideoApparentlyDirty())
			{
				VideoCheckPage(1);
				static DWORD lasttime = 0;
				DWORD currtime = GetTickCount();
				if ((!g_bFullSpeed) ||
					(currtime-lasttime >= (DWORD)((graphicsmode || !systemidle) ? 100 : 25)))
				{
					VideoRefreshScreen();
					lasttime = currtime;
				}
				screenupdated = 1;
			}

			lastupdates[1] = lastupdates[0];
			lastupdates[0] = anyupdates;
			anyupdates     = 0;

			if (pageflipping)
				pageflipping--;
		}

		MB_EndOfVideoFrame();
	}

	//

	if(!g_bFullSpeed)
	{
		SysClk_WaitTimer();

#if DBG_CALC_FREQ
		if(g_nPerfFreq)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&nTime1);
			LONGLONG nTimeDiff = nTime1 - nTime0;
			double fTime = (double)nTimeDiff / (double)(LONGLONG)g_nPerfFreq;

			g_fDbg[g_nIdx] = fTime;
			g_nIdx = (g_nIdx+1) & (MAX_CNT-1);
			g_fMeanPeriod = 0.0;
			for(UINT n=0; n<MAX_CNT; n++)
				g_fMeanPeriod += g_fDbg[n];
			g_fMeanPeriod /= (double)MAX_CNT;
			g_fMeanFreq = 1.0 / g_fMeanPeriod;
		}
#endif
	}
}