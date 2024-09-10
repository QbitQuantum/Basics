JOYCAPS *
QuaJoystickManager::GetJoyCaps(int32 *nJoyP)
{
	JOYINFO joyinfo; 
	uint32	nJoy;
//	uint32	wDeviceID; 
	bool	dev1Attached, dev2Attached; 
	 
	if((nJoy = joyGetNumDevs()) == 0) {
		*nJoyP = 0;
		return nullptr; 
	}
	fprintf(stderr, "%d total joysticks\n", nJoy);
	dev1Attached = joyGetPos(JOYSTICKID1,&joyinfo) != JOYERR_UNPLUGGED; 
	dev2Attached = (nJoy == 2) && joyGetPos(JOYSTICKID2,&joyinfo) != 
		JOYERR_UNPLUGGED; 
	if(!(dev1Attached || dev2Attached)) {   // decide which joystick to use 
		*nJoyP = 0;
		return nullptr;
	}
	JOYCAPS	*caps;
	int		nc = 0;
	/*
	caps = new JOYCAPS[(dev1Attached && dev2Attached)?2:1];
	if (dev1Attached) {
		MMRESULT	err = joyGetDevCaps(
							JOYSTICKID1, 
							&caps[nc],    
							sizeof(JOYCAPS));
		nc++;
	}
	if (dev2Attached) {
		MMRESULT	err = joyGetDevCaps(
							JOYSTICKID2, 
							&caps[nc],    
							sizeof(JOYCAPS));
		nc++;
	}
	*nJoyP = nc;

	*/
	JOYCAPS	c;
	int		i, n=0;
	for (i=0; i<nJoy; i++) {
		MMRESULT	err = joyGetDevCaps(
							i, 
							&c,    
							sizeof(JOYCAPS));
		if (c.wNumAxes == 0 && c.wNumButtons == 0) {
			break;
		}
		n++;
	}
	nJoy = n;
	caps = new JOYCAPS[nJoy];
	for (i=0; i<nJoy; i++) {
		MMRESULT	err = joyGetDevCaps(
							i, 
							&caps[i],    
							sizeof(JOYCAPS));
	}
	*nJoyP = nJoy;

	return caps;
}