int joy95_init_stick(int joy, int spjoy)
{
	UINT 			joyid;
	MMRESULT 	mmresult;
	char 			joyname[256];

	if (!joy_installed) 		  
		return 0;

	switch (SpecialDevice)
	{
		case TACTILE_CYBERNET:
		//@@	joystick.present_mask = JOY_1_X_AXIS | JOY_1_Y_AXIS | JOY_1_Z_AXIS | JOY_1_POV;
		//@@	joystick.has_pov = 1;
			break;

		case TACTILE_IMMERSION:
			mprintf((0, "Joystick name= I-Force compatible device.\n"));
			break;
	}

//	if (spjoy) return 1;

	joystick.joyid = 0;

	if (joy == 1) joystick.joyid = joyid = JOYSTICKID1;
	else 
		return 0;

	mmresult = joyGetDevCaps(joyid, &WinJoyCaps, sizeof(WinJoyCaps));
	if (mmresult != JOYERR_NOERROR) {
		mprintf((1, "Attempt to get Joystick %d caps failed.\n", joy));
 		return 0;
	}
   mprintf ((0,"Joystick name=%s\n",WinJoyCaps.szPname));

//	Tell our Window App. about this joystick.
	joySetThreshold(joyid, WinJoyCaps.wXmax/256);
	mmresult = joySetCapture(GetLibraryWindow(), 
						joyid, 
						JOY_POLL_RATE, 
						FALSE);

	if (mmresult != JOYERR_NOERROR) {
 		mprintf((1, "Unable to capture joystick %d. Error=%d\n", joy,mmresult));
		return 0;
	}

//	Get raw axis' min and max.
	joystick.threshold 			= WinJoyCaps.wXmax/256;
	joystick.max_timer 			= WinJoyCaps.wPeriodMax;

	joystick.threshold 			= WinJoyCaps.wXmax/256;
	joystick.max_timer 			= WinJoyCaps.wPeriodMax;
	joystick.axis_min[0]			= WinJoyCaps.wXmin;
	joystick.axis_min[1]			= WinJoyCaps.wYmin;
	joystick.axis_min[2]			= WinJoyCaps.wZmin;
	joystick.axis_min[4]			= WinJoyCaps.wRmin;
	joystick.axis_min[5]			= WinJoyCaps.wUmin;
	joystick.axis_min[6]			= WinJoyCaps.wVmin;
	joystick.axis_max[0]			= WinJoyCaps.wXmax;
	joystick.axis_max[1]			= WinJoyCaps.wYmax;
	joystick.axis_max[2]			= WinJoyCaps.wZmax;
	joystick.axis_max[4]			= WinJoyCaps.wRmax;
	joystick.axis_max[5]			= WinJoyCaps.wUmax;
	joystick.axis_max[6]			= WinJoyCaps.wVmax;
	joystick.axis_center[0]			= (WinJoyCaps.wXmax-WinJoyCaps.wXmin)/2;
	joystick.axis_center[1]			= (WinJoyCaps.wYmax-WinJoyCaps.wYmin)/2;
	joystick.axis_center[2]			= (WinJoyCaps.wZmax-WinJoyCaps.wZmin)/2;
	joystick.axis_center[4]			= (WinJoyCaps.wRmax-WinJoyCaps.wRmin)/2;
	joystick.axis_center[5]			= (WinJoyCaps.wUmax-WinJoyCaps.wUmin)/2;
	joystick.axis_center[6]			= (WinJoyCaps.wVmax-WinJoyCaps.wVmin)/2;

	joystick.present_mask = JOY_1_X_AXIS | JOY_1_Y_AXIS;
	
	if (WinJoyCaps.wCaps & JOYCAPS_HASPOV) {
		joystick.has_pov = 1;
		joystick.present_mask |= JOY_1_POV;
	}
	else joystick.has_pov = 0;

	if (WinJoyCaps.wCaps & JOYCAPS_HASZ) 
		joystick.present_mask |= JOY_1_Z_AXIS;
	if (WinJoyCaps.wCaps & JOYCAPS_HASR) 
		joystick.present_mask |= JOY_1_R_AXIS;
	if (WinJoyCaps.wCaps & JOYCAPS_HASU)
		joystick.present_mask |= JOY_1_U_AXIS;
	if (WinJoyCaps.wCaps & JOYCAPS_HASV) 
		joystick.present_mask |= JOY_1_V_AXIS;

	joy95_get_name(JOYSTICKID1, joyname, 255);
	if (!strcmpi(joyname, "CH Flightstick Pro") || FindArg("-ordinaljoy")) {
		CHStickHack = 1;
	}
	else CHStickHack = 0;

			
	return 1;
}