bool GCodes::ActOnGcode(GCodeBuffer *gb)
{
  int code;
  float value;
  int iValue;
  char* str;
  bool result = true;
  bool error = false;
  bool resend = false;
  bool seen;
  char reply[STRING_LENGTH];

  reply[0] = 0;

  if(gb->Seen('G'))
  {
    code = gb->GetIValue();
    switch(code)
    {
    case 0: // There are no rapid moves...
    case 1: // Ordinary move
      result = SetUpMove(gb);
      break;
      
    case 4: // Dwell
      result = DoDwell(gb);
      break;
      
    case 10: // Set offsets
      result = SetOffsets(gb);
      break;
    
    case 20: // Inches (which century are we living in, here?)
      distanceScale = INCH_TO_MM;
      break;
    
    case 21: // mm
      distanceScale = 1.0;
      break;
    
    case 28: // Home
      if(NoHome())
      {
    	homeAxisMoveCount = 0;
        homeX = gb->Seen(gCodeLetters[X_AXIS]);
        homeY = gb->Seen(gCodeLetters[Y_AXIS]);
        homeZ = gb->Seen(gCodeLetters[Z_AXIS]);
        if(NoHome())
        {
          homeX = true;
          homeY = true;
          homeZ = true;
        }
      }
      result = DoHome();
      break;

    case 30: // Z probe/manually set at a position and set that as point P
    	result = SetSingleZProbeAtAPosition(gb);
    	break;

    case 31: // Return the probe value, or set probe variables
    	result = SetPrintZProbe(gb, reply);
    	break;

    case 32: // Probe Z at multiple positions and generate the bed transform
    	result = DoMultipleZProbe();
    	break;

    case 90: // Absolute coordinates
      drivesRelative = false;
      axesRelative = false;
      break;
      
    case 91: // Relative coordinates
      drivesRelative = true; // Non-axis movements (i.e. extruders)
      axesRelative = true;   // Axis movements (i.e. X, Y and Z)
      break;
      
    case 92: // Set position
      result = SetPositions(gb);
      break;
      
    default:
    	error = true;
    	snprintf(reply, STRING_LENGTH, "invalid G Code: %s", gb->Buffer());
    }
    if(result)
    	HandleReply(error, gb == serialGCode, reply, 'G', code, resend);
    return result;
  }
  
  if(gb->Seen('M'))
  {
    code = gb->GetIValue();
    switch(code)
    {
    case 0: // Stop
    case 1: // Sleep
      if(fileBeingPrinted != NULL)
      {
    	  fileToPrint = fileBeingPrinted;
    	  fileBeingPrinted = NULL;
      }
      if(!DisableDrives())
    	  return false;
      if(!StandbyHeaters())
    	  return false; // Should never happen
      break;
    
    case 18: // Motors off
      result = DisableDrives();
      break;
      
    case 20:  // Deprecated...
      if(platform->Emulating() == me || platform->Emulating() == reprapFirmware)
    	  snprintf(reply, STRING_LENGTH, "GCode files:\n%s", platform->GetMassStorage()->FileList(platform->GetGCodeDir(), gb == serialGCode));
      else
    	  snprintf(reply, STRING_LENGTH, "%s", platform->GetMassStorage()->FileList(platform->GetGCodeDir(), gb == serialGCode));
      break;

    case 21: // Initialise SD - ignore
    	break;

    case 23: // Set file to print
      QueueFileToPrint(gb->GetUnprecedentedString());
      if(platform->Emulating() == marlin)
    	  snprintf(reply, STRING_LENGTH, "%s", "File opened\nFile selected\n");
      break;
      
    case 24: // Print/resume-printing the selected file
      if(fileBeingPrinted != NULL)
    	  break;
      fileBeingPrinted = fileToPrint;
      fileToPrint = NULL;
      break;
      
    case 25: // Pause the print
    	fileToPrint = fileBeingPrinted;
    	fileBeingPrinted = NULL;
    	break;

    case 27: // Report print status - Depricated
    	if(this->PrintingAFile())
    		strncpy(reply, "SD printing.", STRING_LENGTH);
    	else
    		strncpy(reply, "Not SD printing.", STRING_LENGTH);
    	break;

    case 28: // Write to file
    	str = gb->GetUnprecedentedString();
    	OpenFileToWrite(platform->GetGCodeDir(), str, gb);
    	snprintf(reply, STRING_LENGTH, "Writing to file: %s", str);
    	break;

    case 29: // End of file being written; should be intercepted before getting here
    	platform->Message(HOST_MESSAGE, "GCode end-of-file being interpreted.\n");
    	break;

    case 82:
    	for(int8_t extruder = AXES; extruder < DRIVES; extruder++)
    		lastPos[extruder - AXES] = 0.0;
    	drivesRelative = false;
    	break;

    case 83:
    	for(int8_t extruder = AXES; extruder < DRIVES; extruder++)
    		lastPos[extruder - AXES] = 0.0;
    	drivesRelative = true;

    	break;

    case 84: // Motors off - deprecated, use M18
        result = DisableDrives();
        break;

    case 85: // Set inactive time
    	break;

    case 92: // Set/report steps/mm for some axes
    	seen = false;
    	for(int8_t drive = 0; drive < DRIVES; drive++)
    		if(gb->Seen(gCodeLetters[drive]))
    		{
    			platform->SetDriveStepsPerUnit(drive, gb->GetFValue());
    			seen = true;
    		}
    	reprap.GetMove()->SetStepHypotenuse();
    	if(!seen)
    		snprintf(reply, STRING_LENGTH, "Steps/mm: X: %d, Y: %d, Z: %d, E: %d",
    				(int)platform->DriveStepsPerUnit(X_AXIS), (int)platform->DriveStepsPerUnit(Y_AXIS),
    				(int)platform->DriveStepsPerUnit(Z_AXIS), (int)platform->DriveStepsPerUnit(AXES)); // FIXME - needs to do multiple extruders
        break;


    case 98:
    	if(gb->Seen('P'))
    		result = DoFileCannedCycles(gb->GetString());
    	break;

    case 99:
    	result = FileCannedCyclesReturn();
    	break;

    case 104: // Depricated
    	if(gb->Seen('S'))
    	{
    		reprap.GetHeat()->SetActiveTemperature(1, gb->GetFValue()); // 0 is the bed
    		reprap.GetHeat()->Activate(1);
    	}
    	break;

    case 105: // Deprecated...
    	strncpy(reply, "T:", STRING_LENGTH);
    	for(int8_t heater = HEATERS - 1; heater > 0; heater--)
    	{
    		strncat(reply, ftoa(0, reprap.GetHeat()->GetTemperature(heater), 1), STRING_LENGTH);
    		strncat(reply, " ", STRING_LENGTH);
    	}
    	strncat(reply, "B:", STRING_LENGTH);
    	strncat(reply, ftoa(0, reprap.GetHeat()->GetTemperature(0), 1), STRING_LENGTH);
    	break;
   
    case 106: // Fan on or off
    	if(gb->Seen('S'))
    		platform->CoolingFan(gb->GetFValue());
      break;
    
    case 107: // Fan off - depricated
    	platform->CoolingFan(0.0);
      break;
      
    case 110: // Set line numbers - line numbers are dealt with in the GCodeBuffer class, so ignore
    	break;

    case 111: // Debug level
    	if(gb->Seen('S'))
    		reprap.SetDebug(gb->GetIValue());
    	break;

    case 112: // Emergency stop - acted upon in Webserver
    	break;

    case 114: // Deprecated
    	str = GetCurrentCoordinates();
    	if(str != 0)
    	{
    		strncpy(reply, str, STRING_LENGTH);
    	} else
    		result = false;
    	break;

    case 115: // Print firmware version
    	snprintf(reply, STRING_LENGTH, "FIRMWARE_NAME:%s FIRMWARE_VERSION:%s ELECTRONICS:%s DATE:%s", NAME, VERSION, ELECTRONICS, DATE);
    	break;

    case 109: // Depricated
    	if(gb->Seen('S'))
    	{
    		reprap.GetHeat()->SetActiveTemperature(1, gb->GetFValue()); // 0 is the bed
    		reprap.GetHeat()->Activate(1);
    	}
    case 116: // Wait for everything, especially set temperatures
    	if(!AllMovesAreFinishedAndMoveBufferIsLoaded())
    		return false;
    	result = reprap.GetHeat()->AllHeatersAtSetTemperatures();
    	break;

    case 120:
    	result = Push();
    	break;

    case 121:
      result = Pop();
      break;
    
    case 122:
      reprap.Diagnostics();
      break;
      
    case 126: // Valve open
      platform->Message(HOST_MESSAGE, "M126 - valves not yet implemented\n");
      break;
      
    case 127: // Valve closed
      platform->Message(HOST_MESSAGE, "M127 - valves not yet implemented\n");
      break;
      
    case 135: // Set PID sample interval
    	break;

    case 140: // Set bed temperature
      if(gb->Seen('S'))
      {
        reprap.GetHeat()->SetActiveTemperature(0, gb->GetFValue());
        reprap.GetHeat()->Activate(0);
      }
      break;
    
    case 141: // Chamber temperature
      platform->Message(HOST_MESSAGE, "M141 - heated chamber not yet implemented\n");
      break;

    case 201: // Set axis accelerations
    	for(int8_t drive = 0; drive < DRIVES; drive++)
    	{
    		if(gb->Seen(gCodeLetters[drive]))
    		{
    			value = gb->GetFValue();
    		}else{
    			value = -1;
    		}
    		platform->SetAcceleration(drive, value);
    	}
    	break;

    case 203: // Set maximum feedrates
    	for(int8_t drive = 0; drive < DRIVES; drive++)
    	{
    		if(gb->Seen(gCodeLetters[drive]))
    		{
    			value = gb->GetFValue()*distanceScale*0.016666667; // G Code feedrates are in mm/minute; we need mm/sec;
    			platform->SetMaxFeedrate(drive, value);
    		}
    	}
    	break;

    case 205:  //M205 advanced settings:  minimum travel speed S=while printing T=travel only,  B=minimum segment time X= maximum xy jerk, Z=maximum Z jerk
    	break;

    case 206:  // Offset axes
    	result = OffsetAxes(gb);
    	break;

    case 208: // Set maximum axis lengths
    	for(int8_t axis = 0; axis < AXES; axis++)
    	{
    		if(gb->Seen(gCodeLetters[axis]))
    		{
    			value = gb->GetFValue()*distanceScale;
    			platform->SetAxisLength(axis, value);
    		}
    	}
    	break;

    case 210: // Set homing feedrates
    	for(int8_t axis = 0; axis < AXES; axis++)
    	{
    		if(gb->Seen(gCodeLetters[axis]))
    		{
    			value = gb->GetFValue()*distanceScale*0.016666667;
    			platform->SetHomeFeedRate(axis, value);
    		}
    	}
    	break;

    case 301: // Set PID values
    	break;

    case 302: // Allow cold extrudes
    	break;

    case 304: // Set thermistor parameters
    	break;

    case 503: // list variable settings
    	result = SendConfigToLine();
    	break;

    case 550: // Set machine name
        	if(gb->Seen('P'))
        		reprap.GetWebserver()->SetName(gb->GetString());
        	break;

    case 551: // Set password
    	if(gb->Seen('P'))
    		reprap.GetWebserver()->SetPassword(gb->GetString());
    	break;

    case 552: // Set/Get IP address
    	if(gb->Seen('P'))
    		SetEthernetAddress(gb, code);
    	else
    	{
    		byte *ip = platform->IPAddress();
    		snprintf(reply, STRING_LENGTH, "IP address: %d.%d.%d.%d\n ", ip[0], ip[1], ip[2], ip[3]);
    	}
    	break;

    case 553: // Set/Get netmask
    	if(gb->Seen('P'))
    		SetEthernetAddress(gb, code);
    	else
    	{
    		byte *nm = platform->NetMask();
    		snprintf(reply, STRING_LENGTH, "Net mask: %d.%d.%d.%d\n ", nm[0], nm[1], nm[2], nm[3]);
    	}
    	break;

    case 554: // Set/Get gateway
    	if(gb->Seen('P'))
    		SetEthernetAddress(gb, code);
    	else
    	{
    		byte *gw = platform->GateWay();
    		snprintf(reply, STRING_LENGTH, "Gateway: %d.%d.%d.%d\n ", gw[0], gw[1], gw[2], gw[3]);
    	}
    	break;

    case 555: // Set firmware type to emulate
    	if(gb->Seen('P'))
    		platform->SetEmulating((Compatibility)gb->GetIValue());
    	break;

    case 556: // Axis compensation
    	if(gb->Seen('S'))
    	{
    		value = gb->GetFValue();
    		for(int8_t axis = 0; axis < AXES; axis++)
    			if(gb->Seen(gCodeLetters[axis]))
    				reprap.GetMove()->SetAxisCompensation(axis, gb->GetFValue()/value);
    	}
    	break;

    case 557: // Set Z probe point coordinates
    	if(gb->Seen('P'))
    	{
    		iValue = gb->GetIValue();
    		if(gb->Seen(gCodeLetters[X_AXIS]))
    			reprap.GetMove()->SetXBedProbePoint(iValue, gb->GetFValue());
    		if(gb->Seen(gCodeLetters[Y_AXIS]))
    		    reprap.GetMove()->SetYBedProbePoint(iValue, gb->GetFValue());
    	}
    	break;

    case 558: // Set Z probe type
    	if(gb->Seen('P'))
    		platform->SetZProbeType(gb->GetIValue());
    	break;

    case 559: // Upload config.g
    	if(gb->Seen('P'))
    		str = gb->GetString();
    	else
    		str = platform->GetConfigFile();
        OpenFileToWrite(platform->GetSysDir(), str, gb);
        snprintf(reply, STRING_LENGTH, "Writing to file: %s", str);
    	break;

    case 560: // Upload reprap.htm
         str = INDEX_PAGE;
         OpenFileToWrite(platform->GetWebDir(), str, gb);
         snprintf(reply, STRING_LENGTH, "Writing to file: %s", str);
     	break;

    case 561:
    	reprap.GetMove()->SetIdentityTransform();
    	break;

    case 562: // Reset temperature fault - use with great caution
    	if(gb->Seen('P'))
    	{
    	    iValue = gb->GetIValue();
    	    reprap.GetHeat()->ResetFault(iValue);
    	}
    	break;

    case 876: // TEMPORARY - this will go away...
    	if(gb->Seen('P'))
    	{
    		iValue = gb->GetIValue();
    		if(iValue != 1)
    			platform->SetHeatOn(0);
    		else
    			platform->SetHeatOn(1);
    	}
    	break;

    case 900:
    	result = DoFileCannedCycles("homex.g");
    	break;

    case 901:
    	result = DoFileCannedCycles("homey.g");
    	break;



    case 906: // Set Motor currents
    	for(uint8_t i = 0; i < DRIVES; i++)
    	{
    		if(gb->Seen(gCodeLetters[i]))
    		{
    			value = gb->GetFValue(); // mA
    			platform->SetMotorCurrent(i, value);
    		}
    	}
    	break;

    case 998:
    	if(gb->Seen('P'))
    	{
    	    snprintf(reply, STRING_LENGTH, "%s", gb->GetIValue());
    	    resend = true;
    	}
    	break;
     
    default:
      error = true;
      snprintf(reply, STRING_LENGTH, "invalid M Code: %s", gb->Buffer());
    }
    if(result)
    	HandleReply(error, gb == serialGCode, reply, 'M', code, resend);
    return result;
  }
  
  if(gb->Seen('T'))
  {
    code = gb->GetIValue();
    if(code == selectedHead)
    {
    	if(result)
    		HandleReply(error, gb == serialGCode, reply, 'T', code, resend);
    	return result;
    }

    error = true;
    for(int8_t i = AXES; i < DRIVES; i++)
    {
    	if(selectedHead == i - AXES)
    		reprap.GetHeat()->Standby(selectedHead + 1); // + 1 because 0 is the Bed
    }
    for(int8_t i = AXES; i < DRIVES; i++)
    {    
      if(code == i - AXES)
      {
        selectedHead = code;
        reprap.GetHeat()->Activate(selectedHead + 1); // 0 is the Bed
        error = false;
      }
    }

    if(error)
      snprintf(reply, STRING_LENGTH, "Invalid T Code: %s", gb->Buffer());

    if(result)
    	HandleReply(error, gb == serialGCode, reply, 'T', code, resend);
    return result;
  }
  
  // An empty buffer jumps to here and gets discarded

  if(result)
  	HandleReply(error, gb == serialGCode, reply, 'X', code, resend);

  return result;
}