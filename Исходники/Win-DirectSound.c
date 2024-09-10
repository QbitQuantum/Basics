Boolean DirectSoundInit( MADDriverRec* WinMADDriver)
{
	OnOff					= false;
	
	WIN95BUFFERSIZE = WinMADDriver->BufSize;
	WIN95BUFFERSIZE *= 2L;								// double buffer system
	
	currentBuf 		= calloc( WIN95BUFFERSIZE, 1);
	
	hwnd = GetForegroundWindow();	//GetForegroundWindow();
	if( !hwnd) return false;
	
	if(DS_OK == DirectSoundCreate(NULL, &WinMADDriver->lpDirectSound, NULL))
	{
		if( !AppCreateWritePrimaryBuffer( WinMADDriver->lpDirectSound, &WinMADDriver->lpDirectSoundBuffer, hwnd, WinMADDriver))
		{
			WinMADDriver->lpDirectSound = 0L;
			return false;
		}
		if( !WinMADDriver->lpDirectSoundBuffer) return false;
		
		// Creation succeeded.
		WinMADDriver->lpDirectSound->lpVtbl->SetCooperativeLevel(WinMADDriver->lpDirectSound, hwnd, DSSCL_NORMAL);
		
		WinMADDriver->lpSwSamp = 0L;
		if( !LoadSamp(WinMADDriver->lpDirectSound, &WinMADDriver->lpSwSamp, 0L, WIN95BUFFERSIZE, DSBCAPS_LOCSOFTWARE, WinMADDriver))
		{
			//DEBUG debugger( "Error 2\n");		//DSBCAPS_LOCSOFTWARE
			WinMADDriver->lpDirectSound = 0L;
			return false;
		}
		
		if( !WinMADDriver->lpSwSamp) return false;
		
		WinMADDriver->lpSwSamp->lpVtbl->Play(WinMADDriver->lpSwSamp, 0, 0, DSBPLAY_LOOPING);
		
		///////////
		
		timeBeginPeriod(20);      /* set the minimum resolution */
		
		/*  Set up the callback event.  The callback function
		 *  MUST be in a FIXED CODE DLL!!! -> not in Win95
		 */
		 
		// debugger( "timeSetEvent\n");
		 
		gwID = timeSetEvent(	  40,   												/* how often                 */
													  40,   							/* timer resolution          */
													  TimeProc,  						/* callback function         */
													  (unsigned long) WinMADDriver,		/* info to pass to callback  */
													  TIME_PERIODIC); 					/* oneshot or periodic?      */
		
		if( gwID == 0) return false;
		else return true;
	}
	
	WinMADDriver->lpDirectSound = 0L;
	
	return false;
}