void joy_init(void) {

	JOYINFO		ji;
	int			i;

	if ((!joyGetNumDevs()) ||
		(joyGetPos(JOYSTICKID1, &ji) == JOYERR_UNPLUGGED)) {
//		xmenu_setjoystick(np2cfg.JOYSTICK | 2);					// ver0.28
		np2oscfg.JOYPAD1 |= 2;
	}
	for (i=0; i<4; i++) {										// ver0.28
		joypad1btn[i] = 0xff ^
				((np2oscfg.JOY1BTN[i] & 3) << ((np2oscfg.JOY1BTN[i] & 4)?4:6));
	}
}