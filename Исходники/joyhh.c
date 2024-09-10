int joy_init(int joyid) //HH: added joyid parameter
{
	int i;
        int temp_axis[JOY_NUM_AXES];       //changed - orulz
	JOYCAPS pjc;

	if (FindArg( "-nojoystick" ))
		return 0;

	atexit(joy_close);	//HH: we are a bit lazy :). Errors are ignored, so we are even double-lazy :)

	joy_flush();
	memset(&joystick, 0, sizeof(joystick));

	for (i=0; i<MAX_BUTTONS; i++)
		joystick.buttons[i].last_state = 0;

	if ( !joy_installed )   {
                joy_present = 0;
                joy_installed = 1;
                joystick.max_timer = 65536;
                joystick.read_count = 0;
                joystick.last_value = 0;
	}


	joystick.present_mask = JOY_ALL_AXIS;		// Assume they're all present
        joystick.present_mask = joystick_read_raw_axis( JOY_ALL_AXIS, temp_axis );

	if ( joystick.present_mask & 3 )
		joy_present = 1;
	else
		joy_present = 0;

	
	//HH: Main Win32 joystick initialization, incl. reading cal. stuff

	if (joyGetDevCaps(joyid, &pjc, sizeof(pjc))!=JOYERR_NOERROR) {
		return 0;
	}

	if (joySetThreshold(joyid, pjc.wXmax/256)!=JOYERR_NOERROR) {
		return 0;
	}

        joystick.max_timer      = pjc.wPeriodMax;
	joystick.axis_min[0]	= pjc.wXmin;
	joystick.axis_min[1]	= pjc.wYmin;
//orulz:
//        joystick.axis_min[2]    = pjc.wZmin;
//        //HH: joystick.axis_min[3]  = pov-stuff
//        joystick.axis_min[4]    = pjc.wRmin;
//        joystick.axis_min[5]    = pjc.wUmin;
//        joystick.axis_min[6]    = pjc.wVmin;
        joystick.axis_min[2]    = pjc.wRmin;
        joystick.axis_min[3]    = pjc.wZmin;
        joystick.axis_min[4]    = pjc.wUmin;
        joystick.axis_min[5]    = pjc.wVmin;

	joystick.axis_max[0]	= pjc.wXmax;
	joystick.axis_max[1]	= pjc.wYmax;
//orulz:
//        joystick.axis_max[2]    = pjc.wZmax;
//        //HH: joystick.axis_max[3]  = pov-stuff
//        joystick.axis_max[4]    = pjc.wRmax;
//        joystick.axis_max[5]    = pjc.wUmax;
//        joystick.axis_max[6]    = pjc.wVmax;
        joystick.axis_max[2]    = pjc.wRmax;
        joystick.axis_max[3]    = pjc.wZmax;
        joystick.axis_max[4]    = pjc.wUmax;
        joystick.axis_max[5]    = pjc.wVmax;

        joystick.axis_center[0]	= hh_average(pjc.wXmax,pjc.wXmin);
	joystick.axis_center[1]	= hh_average(pjc.wYmax,pjc.wYmin);
//orulz:
//        joystick.axis_center[2] = hh_average(pjc.wZmax,pjc.wZmin);
//        joystick.axis_center[3] = JOY_POVCENTERED;
//        joystick.axis_center[4] = hh_average(pjc.wRmax,pjc.wRmin);
//        joystick.axis_center[5] = hh_average(pjc.wUmax,pjc.wUmin);
//        joystick.axis_center[6] = hh_average(pjc.wVmax,pjc.wVmin);
        joystick.axis_center[2] = hh_average(pjc.wRmax,pjc.wRmin);
        joystick.axis_center[3] = hh_average(pjc.wZmax,pjc.wZmin);
        joystick.axis_center[4] = hh_average(pjc.wUmax,pjc.wUmin);
        joystick.axis_center[5] = hh_average(pjc.wVmax,pjc.wVmin);

	joystick.present_mask = JOY_1_X_AXIS | JOY_1_Y_AXIS;
	if (pjc.wCaps & JOYCAPS_HASZ)	joystick.present_mask |= JOY_1_Z_AXIS;
//        if (pjc.wCaps & JOYCAPS_HASPOV) joystick.present_mask |= JOY_1_POV;
	if (pjc.wCaps & JOYCAPS_HASR)	joystick.present_mask |= JOY_1_R_AXIS;
	if (pjc.wCaps & JOYCAPS_HASU)	joystick.present_mask |= JOY_1_U_AXIS;
	if (pjc.wCaps & JOYCAPS_HASV)	joystick.present_mask |= JOY_1_V_AXIS;

	return joy_present;
}