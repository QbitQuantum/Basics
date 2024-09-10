void CAddCrewOnly::OnOK() 
{
  CString s;
  int  rcode2;
  int  opCode;
  int  nI;
  long runNumber;
  long pieceNumber;
  long cutAsRuntype;
  long startNODESrecordID;
  long startTime;
  long endNODESrecordID;
  long endTime;

//
//  Nothing can be blank or zero
//
//  Run number
//
  pEditRUNNUMBER->GetWindowText(s);
  runNumber = atol(s);
  if(s.IsEmpty() || runNumber == 0)
  {
    TMSError(m_hWnd, MB_ICONSTOP, ERROR_305, pEditRUNNUMBER->m_hWnd);
    return;
  }
//
//  Piece number
//
  pEditPIECENUMBER->GetWindowText(s);  
  pieceNumber = atol(s);
  if(s.IsEmpty() || pieceNumber == 0)
  {
    TMSError(m_hWnd, MB_ICONSTOP, ERROR_306, pEditPIECENUMBER->m_hWnd);
    return;
  }
//
//  Runtype
//
  nI = pComboBoxRUNTYPE->GetCurSel();
  if(nI == CB_ERR)
  {
    TMSError(m_hWnd, MB_ICONSTOP, ERROR_307, pComboBoxRUNTYPE->m_hWnd);
    return;
  }
  cutAsRuntype = pComboBoxRUNTYPE->GetItemData(nI);
//
//  Start node
//
  nI = pComboBoxSTARTNODE->GetCurSel();
  if(nI == CB_ERR)
  {
    TMSError(m_hWnd, MB_ICONSTOP, ERROR_308, pComboBoxSTARTNODE->m_hWnd);
    return;
  }
  startNODESrecordID = pComboBoxSTARTNODE->GetItemData(nI);
//
//  Start time
//
  pEditSTARTTIME->GetWindowText(s);
  if(s.IsEmpty())
  {
    TMSError(m_hWnd, MB_ICONSTOP, ERROR_309, pEditSTARTTIME->m_hWnd);
    return;
  }
  strcpy(tempString, s);
  startTime = cTime(tempString);
//
//  End node
//
  nI = pComboBoxENDNODE->GetCurSel();
  if(nI == CB_ERR)
  {
    TMSError(m_hWnd, MB_ICONSTOP, ERROR_310, pComboBoxENDNODE->m_hWnd);
    return;
  }
  endNODESrecordID = pComboBoxENDNODE->GetItemData(nI);
//
//  Start time
//
  pEditENDTIME->GetWindowText(s);
  if(s.IsEmpty())
  {
    TMSError(m_hWnd, MB_ICONSTOP, ERROR_311, pEditENDTIME->m_hWnd);
    return;
  }
  strcpy(tempString, s);
  endTime = cTime(tempString);
//
//  Build the record
//
  memset(&CREWONLY, 0x00, sizeof(CREWONLYDef));
//
//  Insert / update?
//
  if(*m_pUpdateRecordID == NO_RECORD)
  {
    rcode2 = btrieve(B_GETLAST, TMS_CREWONLY, &CREWONLY, &CREWONLYKey0, 0);
    CREWONLY.recordID = AssignRecID(rcode2, CREWONLY.recordID);
    CREWONLY.SERVICESrecordID = m_ServiceRecordID;
    CREWONLY.DIVISIONSrecordID = m_DivisionRecordID;
    opCode = B_INSERT;
  }
  else
  {
    CREWONLYKey0.recordID = *m_pUpdateRecordID;
    btrieve(B_GETEQUAL, TMS_CREWONLY, &CREWONLY, &CREWONLYKey0, 0);
    opCode = B_UPDATE;
  }
//
//  Set up the balance of CREWONLY
//
//  Comment code
//
  if(pButtonNA->GetCheck())
    CREWONLY.COMMENTSrecordID = NO_RECORD;
  else
  {
    nI = (int)pComboBoxCOMMENTCODE->GetCurSel();
    CREWONLY.COMMENTSrecordID =
          (nI == CB_ERR ? NO_RECORD : pComboBoxCOMMENTCODE->GetItemData(nI));
  }
//
//  Run number
//
  CREWONLY.runNumber = runNumber;
//
//  Piece number
//
  CREWONLY.pieceNumber = pieceNumber;
//
//  Runtype
//
  CREWONLY.cutAsRuntype = cutAsRuntype;
//
//  Start node
//
  CREWONLY.startNODESrecordID = startNODESrecordID;
//
//  Start time
//
  CREWONLY.startTime = startTime;
//
//  End node
//
  CREWONLY.endNODESrecordID = endNODESrecordID;
//
//  End time
//
  CREWONLY.endTime = endTime;
//
//  Insert / update and leave
//
  btrieve(opCode, TMS_CREWONLY, &CREWONLY, &CREWONLYKey0, 0);
  *m_pUpdateRecordID = CREWONLY.recordID;
	
	CDialog::OnOK();
}