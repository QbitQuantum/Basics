void PsychGetPrecisionTimerSeconds(double *secs)
{
  double					ss, ticks, diff;
  static LARGE_INTEGER		counterFreq;
  LARGE_INTEGER				count;
  static double				oss;
  static double				oldticks;
  static double				lastSlowcheckTimeSecs;
  static double				lastSlowcheckTimeTicks;
  psych_uint32				tick1, tick2, hangcount;
  psych_uint64				curRawticks;
  
	// First time init of timeglue: Set up system for high precision timing,
	// and enable workarounds for broken systems:
  if (firstTime) {

		// Init state to defaults:
		oss=0.0;
		oldticks=0.0;
		lastSlowcheckTimeSecs = -1;
		lastSlowcheckTimeTicks = -1;
		
		// Switch the system into high resolution timing mode, i.e.,
		// 1 khZ timer interrupts aka 1 msec timer resolution, for both,
		// the Sleep() command and TimeGetTime() queries. This way, our hybrid
		// sleep-waiting algorithm for PsychWaitUntilSeconds() can work with
		// tight busy-wait transition thresholds and doesn't burn too much
		// CPU time. The timeGetTime() function then gets sufficient granularity -
		// 1 msecs - to be a good reference for our correctness/consistency
		// checks on the high precision timer, and it is a sufficient fallback
		// in case of broken timers.
		// The drawback is increased general interrupt load due to the 1 kHZ IRQ's...
    	if ((timeBeginPeriod(1)!=TIMERR_NOERROR) && (schedulingtrouble == FALSE)) {
		  	// High precision mode failed! Output warning on first failed invocation...
		  	schedulingtrouble = TRUE;
        	printf("PTBCRITICAL -ERROR: PsychTimeGlue - Win32 syscall timeBeginPeriod(1) failed!!! Timing will be inaccurate.\n");
        	printf("PTBCRITICAL -ERROR: Time measurement may be highly unreliable - or even false!!!\n");
        	printf("PTBCRITICAL -ERROR: FIX YOUR SYSTEM! In its current state its not useable for conduction of studies!!!\n");
        	printf("PTBCRITICAL -ERROR: Check the FAQ section of the Psychtoolbox Wiki for more information.\n");

		  	// Increase switching threshold to 10 msecs to take low timer resolution into account:
		  	sleepwait_threshold = 0.010;
    	}    

	 	// This command timeEndPeriod(1); should be used when flushing the MEX file, but
		// we don't do it. Once a PsychTimeGlue function was called, we leave Matlab at
		// high timing precision mode and rely on the OS to revert to standard Windoze
		// behaviour, once the Matlab application is quit/terminated.

		// Next step for broken systems: Bind our Matlab interpreter/PTB main thread to the
		// first cpu core in the system. The only known way to make sure we don't get time
		// readings from different TSCs due to our thread jumping between cpu's. TSC's on
		// a multi-core system are not guaranteed to be synchronized, so if TSC is our timebase,
		// this could lead to time inconsistencies - even time going backwards between queries!!!
		// Drawback: We may not make optimal use of a multi-core system. On Vista and later, we assume
		// everything will be fine, but still perform consistency checks at each call to PsychGetPrecisionTimerSeconds():
		if (!PsychIsMSVista()) {
			if (SetThreadAffinityMask(GetCurrentThread(), 1)==0) {
				// Binding failed! Output warning on first failed invocation...
				schedulingtrouble = TRUE;
				printf("PTBCRITICAL -ERROR: PsychTimeGlue - Win32 syscall SetThreadAffinityMask() failed!!! Timing could be inaccurate.\n");
				printf("PTBCRITICAL -ERROR: Time measurement may be highly unreliable - or even false!!!\n");
				printf("PTBCRITICAL -ERROR: FIX YOUR SYSTEM! In its current state its not useable for conduction of studies!!!\n");
				printf("PTBCRITICAL -ERROR: Check the FAQ section of the Psychtoolbox Wiki for more information.\n");
			}
		}
		
		// Sleep us at least 10 msecs, so the system will reschedule us, with the
		// thread affinity mask above applied. Don't know if this is needed, but
		// better safe than sorry:
		Sleep(10);
		
		// Spin-Wait until timeGetTime() has switched to 1 msec resolution:
		hangcount = 0;
		while(hangcount < 100) {
			tick1 = (psych_uint32) timeGetTime();
			while((tick2=(psych_uint32) timeGetTime()) == tick1);
			if ((tick2 > tick1) && (tick2 - tick1 == 1)) break;
			hangcount++;
		}

		if (hangcount >= 100) {
			// Totally foobared system! Output another warning but try to go on. Checks further below in code
			// will trigger and provide counter measures - as far as this is possible with such a screwed system :-(
			printf("PTB-CRITICAL WARNING! Timing code detected problems with the low precision TIMER in your system hardware!\n");
			printf("PTB-CRITICAL WARNING! It doesn't run at the requested rate of 1 tick per millisecond. Interrupt problems?!?\n");
			printf("PTB-CRITICAL WARNING! Your system is somewhat screwed up wrt. timing!\n");
			printf("PTB-CRITICAL WARNING! It is NOT RECOMMENDED to continue using this machine for studies that require high\n");
			printf("PTB-CRITICAL WARNING! timing precision in stimulus onset or response collection. No guarantees can be made\n");
			printf("PTB-CRITICAL WARNING! wrt. to timing or correctness of any timestamps or stimulus onsets!\n");
			printf("PTB-CRITICAL WARNING! Check the FAQ section of the Psychtoolbox Wiki for more information.\n\n");
		}

		// Ok, now timeGetTime() should have the requested 1 msec increment rate.

		// Ok, this is a dumb solution, but at least sort of robust. The
		// proper solution will have to wait for the next 'beta' release cycle.
		// We don't allow to use any timing function on a Windoze system that
		// has more than 48 days of uptime. Rationale: At 49.8 days, the 32 bit
		// tick counter will wrap around and leave our fallback- and reference
		// timebase in an undefined state. Implementing proper wraparound handling
		// for inifinite uptimes is not simple, due to PTB's modular nature and
		// some special flaws of Windoze. Anyway, 48 days uptime is unlikely
		// anyway, unless the user doesn't perform regular system updates...
		if (((double) timeGetTime() * 0.001) > (3600 * 24 * 48)) {
			// Uptime exceeds 48 days. Say user this is a no no:
			printf("PTB-ERROR: Your system is running since over 48 days without a reboot. Due to some\n");
			printf("PTB-ERROR: pretty disgusting design flaws in the Windows operating system, timing\n");
			printf("PTB-ERROR: will become unreliable or wrong at uptimes of more than 49 days.\n");
			printf("PTB-ERROR: Therefore PTB will not continue executing any time related function unless\n");
			printf("PTB-ERROR: you reboot your machine now.\n\n");
			PsychErrorExitMsg(PsychError_user, "Maximum allowable uptime for Windows exceeded. Please reboot your system.");
		} 

		// Is the high-precision timer supported?
    	counterExists = QueryPerformanceFrequency(&counterFreq);
		if (counterExists) {
			// Initialize old counter values to now:
			if (0 == QueryPerformanceCounter(&count)) {
				Timertrouble = TRUE;
				counterExists = FALSE;
				oss = 0;
				
				printf("PTB-CRITICAL WARNING! Timing code detected problems with the high precision TIMER in your system hardware!\n");
				printf("PTB-CRITICAL WARNING! Initial call to QueryPerformanceCounter() failed!\n");
				printf("PTB-CRITICAL WARNING! Will switch back to lower precision/resolution timer (only +/-1 millisecond accuracy at best).\n");				
				printf("PTB-CRITICAL WARNING! This can cause a cascade of errors, failures and problems in any timing related functions!!\n\n");				
				printf("PTB-CRITICAL WARNING! It is NOT RECOMMENDED to continue using this machine for studies that require any\n");
				printf("PTB-CRITICAL WARNING! timing precision in stimulus onset or response collection. No guarantees can be made\n");
				printf("PTB-CRITICAL WARNING! wrt. to timing or correctness of any timestamps or stimulus onsets!\n");
				printf("PTB-CRITICAL WARNING! Read 'help GetSecsTest' and run GetSecsTest for further diagnosis and troubleshooting.\n");
				printf("PTB-CRITICAL WARNING! It may also help to restart the machine to see if the problem is transient.\n");
				printf("PTB-CRITICAL WARNING! Also check the FAQ section of the Psychtoolbox Wiki for more information.\n\n");
			}
			else {
				oss = ((double)count.QuadPart)/((double)counterFreq.QuadPart);
			}
		}
		
		// Sleep us another 10 msecs to make sure there is a significant difference between
		// first invocation and successive invocations:
		Sleep(10);
  }
  
	// Need to acquire our timelock before we continue, for atomic timestamping and as we will soon access shared data structures:
	EnterCriticalSection(&time_lock);

	// Query system time of low resolution counter:
	curRawticks = timeGetTime();

	// Query Performance counter if it is supported:
	if ((counterExists) && (0 == QueryPerformanceCounter(&count))) {
			Timertrouble = TRUE;
			printf("PTB-CRITICAL WARNING! Timing code detected problems with the high precision TIMER in your system hardware!\n");
			printf("PTB-CRITICAL WARNING! A call to QueryPerformanceCounter() failed!\n");
			printf("PTB-CRITICAL WARNING! Will switch back to lower precision/resolution timer (only +/-1 millisecond accuracy at best).\n");
			printf("PTB-CRITICAL WARNING! It is NOT RECOMMENDED to continue using this machine for studies that require high\n");
			printf("PTB-CRITICAL WARNING! timing precision in stimulus onset or response collection. No guarantees can be made\n");
			printf("PTB-CRITICAL WARNING! wrt. to timing or correctness of any timestamps or stimulus onsets!\n");
			printf("PTB-CRITICAL WARNING! Read 'help GetSecsTest' and run GetSecsTest for further diagnosis and troubleshooting.\n");
			printf("PTB-CRITICAL WARNING! It may also help to restart the machine to see if the problem is transient.\n");
			printf("PTB-CRITICAL WARNING! Also check the FAQ section of the Psychtoolbox Wiki for more information.\n\n");
	}

	// Convert to ticks in seconds for further processing:
	ticks = ((double) (psych_int64) curRawticks) * 0.001;
	tickInSecsAtLastQuery = ticks;
	
  // Start actual processing of result of QueryPerformanceCounter(). We do this here,
  // deferred under protection of the time_lock lock. The Query has been done above,
  // outside of the critical section, so multiple threads can't collide on a contended
  // time_lock and get delayed needlessly:
  if (counterExists) {

   ss = ((double)count.QuadPart)/((double)counterFreq.QuadPart);
   timeInSecsAtLastQuery = ss;

	// Initialize base time for slow consistency checks at first invocation:
	if (firstTime) {
		lastSlowcheckTimeSecs = ss;
		lastSlowcheckTimeTicks = ticks;
	}

	// Compute difference (disagreement over elapsed time since last call) between high-precision
	// timer and low-precision timer:
	diff = ((ss - oss) - (ticks - oldticks));

	// We don't perform the inter-timer agreement check at first invokation - Thread scheduling etc. needs to settle,
	// as well as the timeBeginPeriod(1) call above...
	if (!Timertrouble && !firstTime) {
		// No timer problems yet. Perform checks:

		// Time running backwards?
        // We allow for a slack of 10 nanoseconds. Not sure if this is a good idea, as it weakens the test
        // to avoid aggressive fallback on flaky but sort of still useable hardware. Some modern cpu's showed
        // this effect, but the fallback would have been worse...
		if (ss < (oss - 1e-8)) {
			Timertrouble = TRUE;
			printf("PTB-CRITICAL WARNING! Timing code detected problems with the high precision TIMER in your system hardware!\n");
			printf("PTB-CRITICAL WARNING! Apparently time is reported as RUNNING BACKWARDS. (Timewarp Delta: %0.30f secs.)\n", ss - oss);
			printf("PTB-CRITICAL WARNING! One reason could be a multi-core system with unsynchronized TSC's and buggy platform drivers.\n");
			printf("PTB-CRITICAL WARNING! Will switch back to lower precision/resolution timer (only +/-1 millisecond accuracy at best).\n");
		}
		
		// The old and new high res. timer should not
		// disagree in their increment since last call by more than 250 msecs. If they do,
		// this means that the high precision timer leaped forward, which indicates a faulty
		// Southbridge controller in the machines host chipset - Not a good basis for high precision timing.
		// See Microsoft Knowledge base article Nr. 274323 for further explanation and a list of known bad
		// chipsets.
		// We actually allow for an additional slack of 0.000200 seconds or 200 ppm for each
		// elapsed second of the test interval. This to account for clock drift of up to 200 ppm
		// between both clocks. According to some docs, 200 ppm drift are possible under MS-Windows!
		if ( diff > ( 0.25 + ((ticks - oldticks) * 0.000200 ) ) ) {
			// Mismatch between performance counter and tick counter detected!
			// Performance counter is faulty! Report this to user, then continue
			// by use of the older tick counter as a band-aid.
			Timertrouble = TRUE;
			printf("PTB-CRITICAL WARNING! Timing code detected a FAULTY high precision TIMER in your system hardware!(Delta %0.30f secs).\n", diff);
			printf("PTB-CRITICAL WARNING! Seems the timer sometimes randomly jumps forward in time by over 250 msecs!");
			printf("PTB-CRITICAL WARNING! Will switch back to lower precision/resolution timer (only +/-1 millisecond accuracy at best).\n");
			printf("PTB-CRITICAL WARNING! For more information see Microsoft knowledge base article Nr. 274323.\n");
			printf("PTB-CRITICAL WARNING! http://support.microsoft.com/default.aspx?scid=KB;EN-US;Q274323&\n\n");
		}

		// We check for lags of QPC() wrt. to tick count at intervals of greater than 1 second, ie. only if
		// this query and the last one are at least 1 second spaced apart in time. This is kind of a low-pass
		// filter to account for the fact that the tick counter itself can sometimes lose a bit of time due
		// to lost timer interrupts, and then jump forward in time by a couple of milliseconds when some
		// system service detects the lost interrupts and accounts for them by incrementing time by multiple
		// ticks at a single IRQ. Here we check over a longer period to make it less likely that such transients
		// show up. We apply a much more generous lag threshold as well, so we can compensate for transient timer
		// jumps of up to 50 msecs.
		if ((ticks - lastSlowcheckTimeTicks) >= 1.0) {
			// Check for lags: A lag of multiple msec is normal and expected due to the measurement method.
			diff = ((ss - lastSlowcheckTimeSecs) - (ticks - lastSlowcheckTimeTicks));
						
			// Let's check for a lag exceeding 5% of the duration of the check interval, so we have a bit of headroom to the expected lag:
			if (diff < -0.05 * (ticks - lastSlowcheckTimeTicks)) {
				// Mismatch between performance counter and tick counter detected!
				// Performance counter is lagging behind realtime! Report this to user, then continue
				// by use of the older tick counter as a band-aid.
				Timertrouble = TRUE;
				printf("PTB-CRITICAL WARNING! Timing code detected a LAGGING high precision TIMER in your system hardware! (Delta %0.30f secs).\n", diff);
				printf("PTB-CRITICAL WARNING! Seems that the timer sometimes stops or slows down! This can happen on systems with\n");
				printf("PTB-CRITICAL WARNING! processor power management (cpu throttling) and defective platform drivers.\n");				
				printf("PTB-CRITICAL WARNING! Will switch back to lower precision/resolution timer (only +/-1 millisecond accuracy at best).\n");
				printf("PTB-CRITICAL WARNING! Please try if disabling all power management features of your system helps...\n");
			}
			
			// Update timestamps of last check:
			lastSlowcheckTimeSecs = ss;
			lastSlowcheckTimeTicks = ticks;
		}
		
		if (Timertrouble) {
            // Faulty high precision clock detected. We switch to the low-res clock for the rest of the session, in the hope that
            // the low-res clock is less broken than the high-res clock.
            //
            // We need to make the switch as seamless as possible. As the low-res and high-res clocks have different "zero seconds"
            // reference points, we need to compute the absolute offset between both and then apply that offset to the reported low
            // res clock time to compensate for it. This should reduce any jumps or jerks in the monotonic system time as perceived
            // by clients of this function, especially the PsychWaitUntilSeconds() and PsychWaitIntervalSeconds() functions, which
            // could hang for a very long time if the switch between high-res and low-res clock happens at the wrong moment.
            lowToHiBiasSecs = ss - ticks;

			// More info for user at first detection of trouble:
			printf("PTB-CRITICAL WARNING! It is NOT RECOMMENDED to continue using this machine for studies that require high\n");
			printf("PTB-CRITICAL WARNING! timing precision in stimulus onset or response collection. No guarantees can be made\n");
			printf("PTB-CRITICAL WARNING! wrt. to timing or correctness of any timestamps or stimulus onsets!\n");
			printf("PTB-CRITICAL WARNING! Read 'help GetSecsTest' and run GetSecsTest for further diagnosis and troubleshooting.\n");
			printf("PTB-CRITICAL WARNING! It may also help to restart the machine to see if the problem is transient.\n");
			printf("PTB-CRITICAL WARNING! Also check the FAQ section of the Psychtoolbox Wiki for more information.\n\n");			
		}
	}

	// All checks done: Prepare old values for new iteration:
	oss = ss;
	oldticks = ticks;
	
	// Ok, is the timer finally considered safe to use?
	if (!Timertrouble) {
		// All checks passed: ss is the valid return value:
		ss = ss;
	}
	else {
		// Performance counter works unreliably: Fall back to result of timeGetTime().
		// This only has 1 msec resolution at best, but at least it works (somewhat...).
        //
        // Correct for time bias between low-res clock and high-res clock to fake a time
        // that looks to clients as if it comes from the high-res clock, albeit with a lower
        // resolution of only 1 msec at best:
		ss = ticks + lowToHiBiasSecs;
	}	

	//  ========= End of high precision timestamping. =========
  }
  else {
	//  ========= Low precision fallback path for ancient machines: 1 khz tick counter: =========
	ss = ticks;
	timeInSecsAtLastQuery = -1;
  }

  // Finally assign time value:  
  *secs= ss;  

  // Clear the firstTime flag - this was the first time, maybe.
  firstTime = FALSE;

  // Need to release our timelock - Done with access to shared data:
  LeaveCriticalSection(&time_lock);

  return;
}