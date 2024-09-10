BOOL CCCFrontEnd::OnInitDialog() 
{
 	CDialog::OnInitDialog();

  CString s;
//
//  Default to no display of cancelled records
//
  m_bDisplayCancelled = FALSE;
//
//  Make all future memory pointers NULL
//
  pCCFESORT = NULL;
  CCFE.pCCREFER = NULL;
//
//  Set up the pointers to the controls
//
  pButtonNEW = (CButton *)GetDlgItem(CCFE_NEW);
  pButtonEXISTING = (CButton *)GetDlgItem(CCFE_EXISTING);
  pListCtrlLIST = (CListCtrl *)GetDlgItem(CCFE_LIST);
  pButtonTHISISA = (CButton *)GetDlgItem(CCFE_THISISA);
 	pWndDATETIME = GetDlgItem(CCFE_DATETIME);
  pWndRECEIVEDBY = GetDlgItem(CCFE_RECEIVEDBY);
  pButtonCOMPLAINT = (CButton *)GetDlgItem(CCFE_COMPLAINT);
  pButtonCOMMENDATION = (CButton *)GetDlgItem(CCFE_COMMENDATION);
  pButtonSERVICEREQUEST = (CButton *)GetDlgItem(CCFE_SERVICEREQUEST);
  pButtonMISCELLANEOUS = (CButton *)GetDlgItem(CCFE_MISCELLANEOUS);
  pStaticJUMPTO_TEXT = (CStatic *)GetDlgItem(CCFE_JUMPTO_TEXT);
  pEditJUMPTO = (CEdit *)GetDlgItem(CCFE_JUMPTO);
  pButtonDISPLAYCANCELLED = (CButton *)GetDlgItem(CCFE_DISPLAYCANCELLED);
  pButtonREOPEN = (CButton *)GetDlgItem(IDREOPEN);

  DWORD dwExStyles = pListCtrlLIST->GetExtendedStyle();
  pListCtrlLIST->SetExtendedStyle(dwExStyles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP);
//
//  Set up the characters that the "referenceNumber" is prefixed by
//
//  Complaint, Commendation, or Service Request
//
  strncpy(cPrefix, "CMSL", 4);
//
//  Get the current date and time and put it on the group box
//  
  CTime time = CTime::GetCurrentTime();
 	CString strTime = time.Format(_T("%A, %B %d, %Y at %I:%M:%S%p"));
//
//  Set up the timer to update the date/time
//
  pWndDATETIME->SetWindowText(strTime);
 	pWndDATETIME->SetTimer(0x1000, 1000, TimerProc);
//
//  Display the user name
//
  pWndRECEIVEDBY->SetWindowText(userName);
//
//  Set up the list control
//
  LVCOLUMN LVC;
  LVC.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
  LVC.fmt = LVCFMT_LEFT;
  LVC.cx = 100;
  LVC.pszText = "Number";
  pListCtrlLIST->InsertColumn(0, &LVC);
  LVC.cx = 100;
  LVC.pszText = "Status";
  pListCtrlLIST->InsertColumn(1, &LVC);
  LVC.cx = 300;
  LVC.pszText = "Name";
  pListCtrlLIST->InsertColumn(2, &LVC);
  bSortForward[0] = TRUE;
  bSortForward[1] = TRUE;
  bSortForward[2] = TRUE;
  PopulateListCtrl();
//
//  Disable the list control for now
//
  pListCtrlLIST->EnableWindow(FALSE);
  pStaticJUMPTO_TEXT->EnableWindow(FALSE);
  pEditJUMPTO->EnableWindow(FALSE);

  pButtonNEW->SetCheck(TRUE);
  pButtonCOMPLAINT->SetCheck(TRUE);
  pButtonCOMPLAINT->SetFocus();
//
//  Set up the referral structure
//
  int nI;

  CCFE.numReferrals = m_numReferrals;

  if(m_numReferrals == 0)
  {
    CCFE.pCCREFER = NULL;
  }
  else
  {
    CCFE.pCCREFER = (CCREFERDef *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(CCREFERDef) * m_numReferrals); 
    if(CCFE.pCCREFER == NULL)
    {
      AllocationError(__FILE__, __LINE__, FALSE);
    }
    else
    {
      for(nI = 0; nI < m_numReferrals; nI++)
      {
        strcpy(CCFE.pCCREFER[nI].szName, m_Referrals[nI].szName);
        strcpy(CCFE.pCCREFER[nI].szDepartment, m_Referrals[nI].szDepartment);
        strcpy(CCFE.pCCREFER[nI].szEmailAddress, m_Referrals[nI].szEmailAddress);
        CCFE.pCCREFER[nI].flags = 0;
      }
    }
  }

  ReleaseCapture();


 	return FALSE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}