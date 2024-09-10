void  VSyncWin::VSyncLoop()
{
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	DWM_TIMING_INFO vblankTime;
	// Make sure to init the cbSize, otherwise GetCompositionTiming will fail
	vblankTime.cbSize = sizeof(DWM_TIMING_INFO);

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	TimeStamp vsync = Now();
	// On Windows 10, DwmGetCompositionInfo returns the upcoming vsync.
	// See GetAdjustedVsyncTimestamp.
	// On start, set mPrevVsync to the "next" vsync
	// So we'll use this timestamp on the 2nd loop iteration.
	mPrevVsync = vsync + mSoftwareVsyncRate;

	for (;;) {

#if !USING_DWM_FLUSH
		TimeStamp here = Now();

		::QueryPerformanceCounter(&gSS);
		//Sleep(1);
		//Sleep(200);

		
		m_pOutput->WaitForVBlank();

		
		//Sleep(1);
		
		m_pSwapChain->Present(0, 0);
		//DwmFlush();

		//Gdi: NtGdiDdDDIWaitForVerticalBlankEvent()
		//TimerBlit();
		//gS = gSS;
		//::PostMessageA(gHwnd, WM_BLIT_REQUEST, 0, 0);
		//TimerBlit();
		FILE *f;
		fopen_s(&f, "C:\\VSyncThread", "rb");
		//char buf[200];
		LARGE_INTEGER fi;
		char buf[200];
		::QueryPerformanceFrequency(&fi);
		sprintf_s(buf, "\n+++++ %d", int((Now() - here) * 1000000 / fi.QuadPart));
		OutputDebugStringA(buf);
#else
		::QueryPerformanceCounter(&gS);

		gTS = vsync;


		/*mWork = CreateThreadpoolWork(BlittingThread,
		(void*)&gTS,
		&mCallBackEnviron);

		SubmitThreadpoolWork(mWork);*/

		//mVSyncTimeStamp.store(vsync);
		
		char buf[1000];
		LARGE_INTEGER fi;
		//::QueryPerformanceFrequency(&fi);
		//sprintf_s(buf, "\n+++++%d", int((vsync - here) * 1000000 / fi.QuadPart));
		//OutputDebugStringA(buf);

		// Use a combination of DwmFlush + DwmGetCompositionTimingInfoPtr
		// Using WaitForVBlank, the whole system dies :/
		//m_pSwapChain->Present(0, 0);
		//::PostMessageA(gHwnd, WM_BLIT_REQUEST, 0, 0);
		//m_pSwapChain->Present(1, 0);
		//TimerBlit();
		
		HRESULT hr;
		
		hr = DwmFlush();//WinUtils::dwmFlushProcPtr();
		if (!SUCCEEDED(hr)) {
		//	// We don't actually know how long we had to wait on DWMFlush
		//	// Instead of trying to calculate how long DwmFlush actually took
		//	// Fallback to software vsync.
		//	//-->ScheduleSoftwareVsync(Now());

			return;
		}

		//dwmflush does not exactly return at next vblank 
		//TimerBlit();

		hr = DwmGetCompositionTimingInfo(0, &vblankTime);


		/*vsync = SUCCEEDED(hr) ?
		GetAdjustedVsyncTimeStamp(frequency, vblankTime.qpcVBlank) :
		Now();*/
		vsync = vblankTime.qpcVBlank;// +vblankTime.qpcRefreshPeriod;
		mVSyncTimeStamp.store(vsync);
		mBlit = true;
		////char buf[200];
		//LARGE_INTEGER l;
		//

		//QueryPerformanceFrequency(&l);
		////if (((vsync - Now()) * 1000000 / l.QuadPart) > 10000)
		//	//continue;
		///*LARGE_INTEGER le, lf;
		//QueryPerformanceCounter(&le);
		//QueryPerformanceFrequency(&lf);*/
		//sprintf_s(buf, "\nvblank Time  Now =  %u", (vsync - Now()) * 1000000 / l.QuadPart);
		//OutputDebugStringA(buf);
		//sprintf_s(buf, "\n****** ---- %llu --", vsync);
		//OutputDebugStringA(buf);
		/*sprintf_s(buf, "\nv Timed %d ", ((le.QuadPart - gS.QuadPart) * 1000000 / lf.QuadPart));
		OutputDebugStringA(buf);*/
#endif
	} // end for

}