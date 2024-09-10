static void resetIO(unsigned long cyclesPerScreen, unsigned char isRsid) {
    memSet(&io_area[0], 0x0, IO_AREA_SIZE);

	// Master_Blaster_intro.sid actually checks this:
	io_area[0x0c01]= 0xff;	 	// Port B, keyboard matrix rows and joystick #1

	// CIA 1 defaults	(by default C64 is configured with CIA1 timer / not raster irq)
	setIO(0xdc0d, 0x81);	// interrupt control	(interrupt through timer A)
	setIO(0xdc0e, 0x01); 	// control timer A: start - must already be started (e.g. Phobia, GianaSisters, etc expect it)
	setIO(0xdc0f, 0x08); 	// control timer B (start/stop) means auto-restart
	setIO(0xdc04, cyclesPerScreen&0xff); 	// timer A (1x pro screen refresh)
	setIO(0xdc05, cyclesPerScreen>>8);
	
	if (isRsid) {	
		// by default C64 is configured with CIA1 timer / not raster irq
		setIO(0xd01a, 0x00); 	// raster irq not active
		setIO(0xd011, 0x1B);
		setIO(0xd012, 0x00); 	// raster at line x

		// CIA 2 defaults
		setIO(0xdd0e, 0x08); 	// control timer 2A (start/stop)
		setIO(0xdd0f, 0x08); 	// control timer 2B (start/stop)		
	}

	resetCiaTimer();
	resetVic();
	
	io_area[0x0418]= 0xf;					// turn on full volume	
	sidPoke(0x18, 0xf);  
}