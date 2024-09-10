//
//  Run | MapInfo
//
void CTMSApp::OnRunMapinfo()
{
/*
//
//  Special section to correct order of magnitude problem at MCT
//
//  Kept here in case needed in future
//
  union
  {
    char String[4];
    long Integer;
  } LLEN;

  int rcode2;
  
  rcode2 = btrieve(B_GETFIRST, TMS_NODES, &NODES, &NODESKey0, 0);
  while(rcode2 == 0)
  {
    memcpy(&LLEN.String, &NODES.longitude, 4);
    LLEN.Integer /= 10;
    memcpy(&NODES.longitude, &LLEN.String, 4);
    memcpy(&LLEN.String, &NODES.latitude, 4);
    LLEN.Integer /= 10;
    memcpy(&NODES.latitude, &LLEN.String, 4);
    btrieve(B_UPDATE, TMS_NODES, &NODES, &NODESKey0, 0);
    rcode2 = btrieve(B_GETNEXT, TMS_NODES, &NODES, &NODESKey0, 0);
  }
  MessageBox("Done Conversion!", TMS, MB_OK);
//
//  End of special section
//
*/

/*
//
//  Special section to chop out some TIMECHEK records from DASH
//
  int rcode2;

  rcode2 = btrieve(B_GETFIRST, TMS_TIMECHECKS, &TIMECHECKS, &TIMECHECKSKey0, 0);
  while(rcode2 == 0)
  {
    if(TIMECHECKS.checkDate < 20040701)
    {
      btrieve(B_DELETE, TMS_TIMECHECKS, &TIMECHECKS, &TIMECHECKSKey0, 0);
    }
    rcode2 = btrieve(B_GETNEXT, TMS_TIMECHECKS, &TIMECHECKS, &TIMECHECKSKey0, 0);
  }
//
//  End of special section
//
*/

  UINT nRC;

  strcpy(tempString, szMappingProgram);
  strcat(tempString, " \"");
  strcat(tempString, szInstallDirectory);
  strcat(tempString, "\\TMS32.MBX\"");
  nRC = WinExec((LPSTR)tempString, SW_SHOW);
  if(nRC == 2 || nRC == 3)
    TMSError(NULL, MB_ICONSTOP, ERROR_096, (HANDLE)NULL);

  return;
}