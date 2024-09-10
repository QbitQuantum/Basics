/* objects can be buttons, axis, sliders etc... */
bool CALLBACK DIEnumDeviceObjectsProc( 
       LPCDIDEVICEOBJECTINSTANCE lpddoi, /* the object instance */
       LPVOID pvRef) /* pointer to void we passed in from calling block */
{ 

  int joysticknum, axis, dir;

  /* you have to use these or you get a warning */
  GUID AxisGUID[MAX_JOYSTICK_AXIS - 1];
  GUID ButtonGUID  = GUID_Button;
  GUID POVGUID     = GUID_POV;
  GUID CompareGUID = lpddoi->guidType; /* pointer to the current object GUID type */
  
  /* pvRef is a pointer to a passed in object from our calling code */
  /* here we passed in the current joystick number */
  joysticknum = *((int *)(pvRef));

  /* types of axis's we have to support */
  AxisGUID[0] = GUID_XAxis;
  AxisGUID[1] = GUID_YAxis;
  AxisGUID[2] = GUID_ZAxis;
  AxisGUID[3] = GUID_RxAxis;
  AxisGUID[4] = GUID_RyAxis;
  AxisGUID[5] = GUID_RzAxis;
  AxisGUID[6] = GUID_Slider; // This holds an array of up to 2 sliders

  /* loop over the AxisGUID[] Array */
  /* find out if current object is one of type in AxisGUID[] */
  for (axis = 0; axis < MAX_JOYSTICK_AXIS - 1; axis++)
  {

    /* if the object is not equal to AxisGUID[axis] then continue */
    if ( ! IsEqualGuid( &AxisGUID[axis], &CompareGUID ))
      continue;

    /* allocate the memory */
    JoystickInfo[joysticknum].Axis[axis].name = (char*) malloc (MAX_JOYNAME+1);
  
    /* assign all /0's to the stack */
    memset (JoystickInfo[joysticknum].Axis[axis].name, 0, (MAX_JOYNAME+1));

    /* if object provides a name */
    if (lpddoi->tszName && *lpddoi->tszName)
      /* use the special name */
      strncpy( JoystickInfo[joysticknum].Axis[axis].name, lpddoi->tszName, MAX_JOYNAME );
    else
      /* use generic name */
      snprintf( JoystickInfo[joysticknum].Axis[axis].name, MAX_JOYNAME, "Axis %d", axis );

    /* this current axis exists */
    JoystickInfo[joysticknum].Axis[axis].exists = true;

    /* up the count */
    /* NumAxis==1 means JoystickInfo[0] is set */
    JoystickInfo[joysticknum].NumAxis++;

    /* were done we found out what object we were dealing with */
    return DIENUM_CONTINUE; 

  }

  /* if the object is a button */
  if (IsEqualGuid( &ButtonGUID, &CompareGUID ))
  {

    /* allocate the memory */
    JoystickInfo[joysticknum].Button[
		JoystickInfo[joysticknum].NumButtons
	].name = (char *) malloc (MAX_JOYNAME+1);
  
    /* assign all /0's to the stack */
    memset (
       JoystickInfo[joysticknum].Button[JoystickInfo[joysticknum].NumButtons].name,
       0,
       (MAX_JOYNAME+1)
    );

    /* if object provides a name */
    if (lpddoi->tszName && *lpddoi->tszName)
      /* use the special name */
      strncpy(
         JoystickInfo[joysticknum].Button[JoystickInfo[joysticknum].NumButtons].name,
         lpddoi->tszName,
         MAX_JOYNAME
      );
    else
      /* use generic name */
      snprintf(
         JoystickInfo[joysticknum].Button[
			 JoystickInfo[joysticknum].NumButtons
		 ].name,
         MAX_JOYNAME,
         "Button %d",
         JoystickInfo[joysticknum].NumButtons
      );

    /* up the count */
    JoystickInfo[joysticknum].NumButtons++;

    /* were done with this object go to next one */
    return DIENUM_CONTINUE;

  }

  /* if the object is a POV aka Hat Switch */
  if (IsEqualGuid( &POVGUID, &CompareGUID ))
  {
    
    /* allocate the memory */
    JoystickInfo[joysticknum].POV[JoystickInfo[joysticknum].NumPOVs].name = 
        (char *) malloc (MAX_JOYNAME+1);
  
    /* assign all /0's to the stack */
    memset (
       JoystickInfo[joysticknum].POV[JoystickInfo[joysticknum].NumPOVs].name,
       0,
       (MAX_JOYNAME+1)
    );

    /* if object provides a name */
    if (lpddoi->tszName && *lpddoi->tszName)
      /* use the special name */
      strncpy(
         JoystickInfo[joysticknum].POV[JoystickInfo[joysticknum].NumPOVs].name,
         lpddoi->tszName,
         MAX_JOYNAME
      );
    else
      /* use generic name */
      snprintf(
         JoystickInfo[joysticknum].POV[JoystickInfo[joysticknum].NumPOVs].name,
         MAX_JOYNAME,
         "Hat %d",
         JoystickInfo[joysticknum].NumPOVs
      );

    /* set the name of the direction */
    for ( dir = 0; dir < MAX_POV_DIRECTIONS; dir++ )
    {

      /* allocate the memory */
      JoystickInfo[joysticknum].POV[JoystickInfo[joysticknum].NumPOVs].dirname[ dir ] = 
          (char *) malloc (MAX_JOYNAME+1);
  
      /* assign all /0's to the stack */
      memset (
         JoystickInfo[joysticknum].POV[JoystickInfo[joysticknum].NumPOVs].dirname[ dir ],
         0,
         (MAX_JOYNAME+1)
      );

      /* use generic name */
      snprintf(
         JoystickInfo[joysticknum].POV[JoystickInfo[joysticknum].NumPOVs].dirname[ dir ],
         MAX_JOYNAME,
         "%s %d",
         JoystickInfo[joysticknum].POV[JoystickInfo[joysticknum].NumPOVs].name,
         JoystickInfo[joysticknum].NumPOVs
      );
    }
  
    /* up the count */
    JoystickInfo[joysticknum].NumPOVs++;

    /* were done with this object go to next */
    return DIENUM_CONTINUE; 

  }

  /* default we couldn't find out what this object is so continue */
  return DIENUM_CONTINUE; 

}