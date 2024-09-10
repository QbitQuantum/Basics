bool
EWDevice::DeclareInner(const struct Declaration *decl,
                       OperationEnvironment &env)
{
  char sTmp[72];

  ewDecelTpIndex = 0;

  if (!TryConnect())
    return false;

  WriteWithChecksum(port, "#SPI"); // send SetPilotInfo
  env.Sleep(50);

  char sPilot[13], sGliderType[9], sGliderID[9];
  convert_string(sPilot, sizeof(sPilot), decl->PilotName);
  convert_string(sGliderType, sizeof(sGliderType), decl->AircraftType);
  convert_string(sGliderID, sizeof(sGliderID), decl->AircraftReg);

  // build string (field 4-5 are GPS info, no idea what to write)
  sprintf(sTmp, "%-12s%-8s%-8s%-12s%-12s%-6s\r",
          sPilot,
          sGliderType,
          sGliderID,
          "", // GPS Model
          "", // GPS Serial No.
          "" // Flight Date,
                                                  // format unknown,
                                                  // left blank (GPS
                                                  // has a RTC)
  );
  port->Write(sTmp);

  if (!port->ExpectString("OK\r"))
    return false;

  /*
  sprintf(sTmp, "#SUI%02d", 0);           // send pilot name
  WriteWithChecksum(port, sTmp);
  env.Sleep(50);
  port->Write(PilotsName);
  port->Write('\r');

  if (!port->ExpectString("OK\r"))
    return false;

  sprintf(sTmp, "#SUI%02d", 1);           // send type of aircraft
  WriteWithChecksum(port, sTmp);
  env.Sleep(50);
  port->Write(Class);
  port->Write('\r');

  if (!port->ExpectString("OK\r"))
    nDeclErrorCode = 1;

  sprintf(sTmp, "#SUI%02d", 2);           // send aircraft ID
  WriteWithChecksum(port, sTmp);
  env.Sleep(50);
  port->Write(ID);
  port->Write('\r');

  if (!port->ExpectString("OK\r"))
    return false;
  */

  for (int i=0; i<6; i++){                        // clear all 6 TP's
    sprintf(sTmp, "#CTP%02d", i);
    WriteWithChecksum(port, sTmp);
    if (!port->ExpectString("OK\r"))
      return false;
  }
  for (unsigned j = 0; j < decl->size(); ++j)
    if (!AddWayPoint(decl->get_waypoint(j)))
      return false;

  return true;
}