void CAddConnectionSD::OnOK() 
{
  CString s;
  short   nI, nJ;
  float   distance;
  BOOL    bAddToList, bFound;
  long    connectionTime;
  long    fromNodeRecordID, toNodeRecordID;
  int     rcode2;
//
//  Cycle through all the rows
//
  for(nI = 1; nI <= 96; nI++)
  {
//
//  A blank from time of day means we're done
//
    s = pSDIGridGRID->GetCellContents(nI, 1);
    if(s == "")
    {
      break;
    }
//
//  Make this time of day and the next one upper case
//
    s.MakeUpper();
    pSDIGridGRID->SetCellContents(nI, 1, (LPCTSTR)s);
    s = pSDIGridGRID->GetCellContents(nI, 2);
    s.MakeUpper();
    pSDIGridGRID->SetCellContents(nI, 2, (LPCTSTR)s);
//
//  We're not interested in the average speed
//
//  Get the connection time
//
    s = pSDIGridGRID->GetCellContents(nI, 4);
    connectionTime = atol(s) * 60;
    if(s.Remove('+'))
    {
      connectionTime += 30;
    }
//
//  Get the from and to nodes
//
    nJ = pComboBoxFROMNODE->GetCurSel();
    if(nJ == CB_ERR)
    {
      return;
    }
    fromNodeRecordID = pComboBoxFROMNODE->GetItemData(nJ);
//
//  To Node
//
    nJ = pComboBoxTONODE->GetCurSel();
    if(nJ == CB_ERR)
    {
      return;
    }
    toNodeRecordID = pComboBoxTONODE->GetItemData(nJ);
//
//  Build the record
//
    CONNECTIONSKey1.fromNODESrecordID = fromNodeRecordID;
    CONNECTIONSKey1.toNODESrecordID = toNodeRecordID;
    CONNECTIONSKey1.fromTimeOfDay = NO_TIME;
    rcode2 = btrieve(B_GETGREATEROREQUAL, TMS_CONNECTIONS, &CONNECTIONS, &CONNECTIONSKey1, 1);
    bAddToList = (rcode2 != 0 ||
          CONNECTIONS.fromNODESrecordID != fromNodeRecordID ||
          CONNECTIONS.toNODESrecordID != toNodeRecordID) &&
          CONN.numConnections < MAXCONNECTIONSKEPT - 1;
    rcode2 = btrieve(B_GETLAST, TMS_CONNECTIONS, &CONNECTIONS, &CONNECTIONSKey0, 0);
    CONNECTIONS.recordID = AssignRecID(rcode2, CONNECTIONS.recordID);
//
//  From Node
//
    CONNECTIONS.fromNODESrecordID = fromNodeRecordID;
//
//  To Node
//
    CONNECTIONS.toNODESrecordID = toNodeRecordID;
//
//  Connection Time - Converted to seconds above
//
    CONNECTIONS.connectionTime = connectionTime;
//
//  Distance
//
    pEditDISTANCE->GetWindowText(s);
    distance = (float)atof(s);
    CONNECTIONS.distance = distance;
//
//  From/to Route
//
    if(pButtonALLROUTES->GetCheck())
    {
      CONNECTIONS.fromROUTESrecordID = NO_RECORD;
      CONNECTIONS.toROUTESrecordID = NO_RECORD;
    }
    else
    {
      nJ = pComboBoxROUTE->GetCurSel();
      if(nJ == CB_ERR)
      {
        CONNECTIONS.fromROUTESrecordID = NO_RECORD;
        CONNECTIONS.toROUTESrecordID = NO_RECORD;
      }
      else
      {
        CONNECTIONS.fromROUTESrecordID = pComboBoxROUTE->GetItemData(nJ);
        CONNECTIONS.toROUTESrecordID = pComboBoxROUTE->GetItemData(nJ);
      }
    }
//
//  From/to Service
//
    if(pButtonALLSERVICES->GetCheck())
    {
      CONNECTIONS.fromSERVICESrecordID = NO_RECORD;
      CONNECTIONS.toSERVICESrecordID = NO_RECORD;
    }
    else
    {
      nJ = pComboBoxSERVICE->GetCurSel();
      if(nJ == CB_ERR)
      {
        CONNECTIONS.fromSERVICESrecordID = NO_RECORD;
        CONNECTIONS.toSERVICESrecordID = NO_RECORD;
      }
      else
      {
        CONNECTIONS.fromSERVICESrecordID = pComboBoxSERVICE->GetItemData(nJ);
        CONNECTIONS.toSERVICESrecordID = pComboBoxSERVICE->GetItemData(nJ);
      }
    }
//
//  From/to Pattern
//
    if(pButtonALLPATTERNS->GetCheck())
    {
      CONNECTIONS.fromPATTERNNAMESrecordID = NO_RECORD;
      CONNECTIONS.toPATTERNNAMESrecordID = NO_RECORD;
    }
    else
    {
      nJ = pComboBoxPATTERN->GetCurSel();
      if(nJ == CB_ERR)
      {
        CONNECTIONS.fromPATTERNNAMESrecordID = NO_RECORD;
        CONNECTIONS.toPATTERNNAMESrecordID = NO_RECORD;
      }
      else
      {
        CONNECTIONS.fromPATTERNNAMESrecordID = pComboBoxPATTERN->GetItemData(nJ);
        CONNECTIONS.toPATTERNNAMESrecordID = pComboBoxPATTERN->GetItemData(nJ);
      }
    }
//
//  From time of day
//
    s = pSDIGridGRID->GetCellContents(nI, 1);
    if(s.IsEmpty())
    {
      CONNECTIONS.fromTimeOfDay = NO_TIME;
    }
    else
    {
      strcpy(tempString, s);
      CONNECTIONS.fromTimeOfDay = cTime(tempString);
    }
//
//  To time of day
//
    s = pSDIGridGRID->GetCellContents(nI, 2);
    if(s.IsEmpty())
    {
      CONNECTIONS.toTimeOfDay = CONNECTIONS.fromTimeOfDay;
    }
    else
    {
      strcpy(tempString, s);
      CONNECTIONS.toTimeOfDay = cTime(tempString);
    }
//
//  Flags
//
    CONNECTIONS.flags = 0;
//
//  One or Two-Way
//
    if(pButtonTWOWAY->GetCheck())
    {
      CONNECTIONS.flags |= CONNECTIONS_FLAG_TWOWAY;
    }
//
//  Running time flag
//
    if(pButtonRUNNINGTIME->GetCheck())
    {
      CONNECTIONS.flags |= CONNECTIONS_FLAG_RUNNINGTIME;
    }
//
//  Travel time flag
//
    if(pButtonTRAVELTIME->GetCheck())
    {
      CONNECTIONS.flags |= CONNECTIONS_FLAG_TRAVELTIME;
    }
//
//  Deadhead time flag
//
    if(pButtonDEADHEADTIME->GetCheck())
    {
      CONNECTIONS.flags |= CONNECTIONS_FLAG_DEADHEADTIME;
    }
//
//  Forward pointer to ROUTINGS
//
    CONNECTIONS.ROUTINGSrecordID = NO_RECORD;
//
//  Insert the record
//
//  First, make sure there isn't any contention
//
    CONNECTIONSDef tempCONN;
    long newRecID = CONNECTIONS.recordID;
    int  counter = 0;

    while(counter < 500)
    {
      rcode2 = btrieve(B_GETLAST, TMS_CONNECTIONS, &tempCONN, &CONNECTIONSKey0, 0);
      CONNECTIONS.recordID = AssignRecID(rcode2, tempCONN.recordID);
      if(CONNECTIONS.recordID == newRecID)
      {
        rcode2 = btrieve(B_INSERT, TMS_CONNECTIONS, &CONNECTIONS, &CONNECTIONSKey0, 0);
        if(rcode2 == 0)
        {
          m_pAddConnectionSDData->recordIDs[nI - 1] = CONNECTIONS.recordID;
          m_pAddConnectionSDData->numRecs = nI;
          break;
        }
      }
      counter++;
      newRecID = tempCONN.recordID;
    }
//
//  Add it to the list, if necessary
//
    bFound = FALSE;
    if(bAddToList)
    {
      for(nJ = 0; nJ < CONN.numConnections; nJ++)
      {
        if((bFound = CONN.startRecordID[nJ] == CONNECTIONS.recordID) == TRUE)
        {
          break;
        }
      }
    }
    if(!bFound)
    {
      CONN.startRecordID[CONN.numConnections++] = CONNECTIONS.recordID;
    }
  }  // nI
//
//  Done
//
  m_bEstablishRUNTIMES = TRUE;

	CDialog::OnOK();
}