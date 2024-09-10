AREXPORT bool ArJoyHandler::init(void)
{

  myPhysMax = 1;
  myLastZ = 0;

  // first see if we can talk to the first joystick
  if (joyGetDevCaps(JOYSTICKID1,&myJoyCaps,sizeof(myJoyCaps)) == 
      JOYERR_NOERROR &&
      joyGetPos(JOYSTICKID1,&myJoyInfo) != JOYERR_UNPLUGGED) 
  {
    myJoyID = JOYSTICKID1;

    // So far, it seems that the x range is the same as that of y and
    // z, so only one is used
    myPhysMax  = myJoyCaps.wXmax - myJoyCaps.wXmin;
	/*
	ArLog::log(ArLog::Normal, "caps 0x%x numAxes %d maxAxes %d %s",
			myJoyCaps.wCaps, myJoyCaps.wNumAxes, myJoyCaps.wMaxAxes, myJoyCaps.szPname);
	ArLog::log(ArLog::Normal, 
		"xMin %d xMax %d yMin %d yMax %d zMin %d zMax %d rMin %d rMax %d uMin %d uMax %d",
			myJoyCaps.wXmin, myJoyCaps.wXmax, myJoyCaps.wYmin, myJoyCaps.wYmax, 
			myJoyCaps.wRmin, myJoyCaps.wRmax, myJoyCaps.wZmin, 
			myJoyCaps.wZmax, myJoyCaps.wUmin, myJoyCaps.wUmax); 
	*/
    myInitialized = true;
    startCal();
    endCal();
    return true;
  } 
  // we couldn't talk to the first one so try the second one
  else if (joyGetDevCaps(JOYSTICKID2,&myJoyCaps,sizeof(myJoyCaps)) == 
      JOYERR_NOERROR &&
      joyGetPos(JOYSTICKID2,&myJoyInfo) != JOYERR_UNPLUGGED) 
  {
    myJoyID = JOYSTICKID2;

    // So far, it seems that the x range is the same as that of y and
    // z, so only one is used
    myPhysMax = myJoyCaps.wXmax - myJoyCaps.wXmin;
	/*
	ArLog::log(ArLog::Normal, "2 caps 0x%x numAxes %d maxAxes %d %s",
			myJoyCaps.wCaps, myJoyCaps.wNumAxes, myJoyCaps.wMaxAxes, myJoyCaps.szPname);
	ArLog::log(ArLog::Normal, 
		"2 xMin %d xMax %d yMin %d yMax %d zMin %d zMax %d rMin %d rMax %d uMin %d uMax %d",
			myJoyCaps.wXmin, myJoyCaps.wXmax, myJoyCaps.wYmin, myJoyCaps.wYmax, 
			myJoyCaps.wRmin, myJoyCaps.wRmax, myJoyCaps.wZmin, 
			myJoyCaps.wZmax, myJoyCaps.wUmin, myJoyCaps.wUmax); 
    */
    myInitialized = true;
    startCal();
    endCal();
    return true;
  } 
  // we couldn't talk to either one
  else
  {
    myInitialized = false;
    return false;
  }

  // Just to prevent any possible divide-by-zeros...
  if (myPhysMax == 0) {
    myPhysMax = 1;
  }

  getData();
}