DWORD CalculationThread (LPVOID lpvoid) {
	(void)lpvoid;
  bool needcalculationsslow;

  NMEA_INFO     tmpGPS;
  DERIVED_INFO  tmpCALCULATED;
  FILETIME CreationTime, ExitTime, StartKernelTime, EndKernelTime, StartUserTime, EndUserTime ;
  needcalculationsslow = false;

  // let's not create a deadlock here, setting the go after another race condition
  goCalculationThread=true; // 091119 CHECK
  // wait for proper startup signal
  while (!MapWindow::IsDisplayRunning()) {
    Sleep(100);
  }

  // while (!goCalculating) Sleep(100);
  Sleep(1000); // 091213  BUGFIX need to syncronize !!! TOFIX02 TODO

  while (!MapWindow::CLOSETHREAD) {

    WaitForSingleObject(dataTriggerEvent, 5000);
    ResetEvent(dataTriggerEvent);
    if (MapWindow::CLOSETHREAD) break; // drop out on exit

    GetThreadTimes( hCalculationThread, &CreationTime, &ExitTime,&StartKernelTime,&StartUserTime);

    // make local copy before editing...
    LockFlightData();
      FLARM_RefreshSlots(&GPS_INFO);
      memcpy(&tmpGPS,&GPS_INFO,sizeof(NMEA_INFO));
      memcpy(&tmpCALCULATED,&CALCULATED_INFO,sizeof(DERIVED_INFO));
    UnlockFlightData();

    DoCalculationsVario(&tmpGPS,&tmpCALCULATED);
    if (!tmpGPS.VarioAvailable) {
    	TriggerVarioUpdate(); // emulate vario update
    } 
    
    if(DoCalculations(&tmpGPS,&tmpCALCULATED)){
	#if (WINDOWSPC>0) && !TESTBENCH
	#else
        if (!INPAN)
	#endif
	{
           MapWindow::MapDirty = true;
	}
        needcalculationsslow = true;

        if (tmpCALCULATED.Circling)
          MapWindow::mode.Fly(MapWindow::Mode::MODE_FLY_CIRCLING);
        else if (tmpCALCULATED.FinalGlide)
          MapWindow::mode.Fly(MapWindow::Mode::MODE_FLY_FINAL_GLIDE);
        else
          MapWindow::mode.Fly(MapWindow::Mode::MODE_FLY_CRUISE);
    }
        
    if (MapWindow::CLOSETHREAD) break; // drop out on exit

    // This is activating another run for Thread Draw
    TriggerRedraws(&tmpGPS, &tmpCALCULATED);

    if (MapWindow::CLOSETHREAD) break; // drop out on exit

    if (SIMMODE) {
	if (needcalculationsslow || ( ReplayLogger::IsEnabled() ) ) { 
		DoCalculationsSlow(&tmpGPS,&tmpCALCULATED);
		needcalculationsslow = false;
	}
    } else {
	if (needcalculationsslow) {
		DoCalculationsSlow(&tmpGPS,&tmpCALCULATED);
		needcalculationsslow = false;
	}
    }

    if (MapWindow::CLOSETHREAD) break; // drop out on exit

    // values changed, so copy them back now: ONLY CALCULATED INFO
    // should be changed in DoCalculations, so we only need to write
    // that one back (otherwise we may write over new data)
    LockFlightData();
    memcpy(&CALCULATED_INFO,&tmpCALCULATED,sizeof(DERIVED_INFO));
    UnlockFlightData();

    // update live tracker with new values
    // this is a nonblocking call, live tracker runs on different thread
     LiveTrackerUpdate(&tmpGPS, &tmpCALCULATED);

    if (FlightDataRecorderActive) UpdateFlightDataRecorder(&tmpGPS,&tmpCALCULATED);
   
    
    if ( (GetThreadTimes( hCalculationThread, &CreationTime, &ExitTime,&EndKernelTime,&EndUserTime)) == 0) {
               Cpu_Calc=9999;
    } else {
               Cpustats(&Cpu_Calc,&StartKernelTime, &EndKernelTime, &StartUserTime, &EndUserTime);
    }
  }
  return 0;
}