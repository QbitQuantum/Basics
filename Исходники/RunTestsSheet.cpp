BOOL CRunTestsSheet::OnInitDialog() 
{
  if(!m_bHideTarget){
    m_prop.Add(_T("Platform"),m_strTarget);
  }
  m_prop.Add(_T("Active timeout"),m_nTimeout);
  m_prop.Add(_T("Download timeout"),m_nDownloadTimeout);
  m_prop.Add(_T("Active timeout type"),m_nTimeoutType);
  m_prop.Add(_T("Download timeout type"),m_nDownloadTimeoutType);
  m_prop.Add(_T("Remote"),m_bRemote);
  m_prop.Add(_T("Serial"),m_bSerial);
  m_prop.Add(_T("Port"),m_strPort);
  m_prop.Add(_T("Baud"),m_nBaud);
  m_prop.Add(_T("Local TCPIP Host"),m_strLocalTCPIPHost);
  m_prop.Add(_T("Local TCPIP Port"),m_nLocalTCPIPPort);
  m_prop.Add(_T("Reset Type"),m_nReset);
  m_prop.Add(_T("Reset String"),m_strReset);
  m_prop.Add(_T("Resource Host"),m_strResourceHost);
  m_prop.Add(_T("Resource Port"),m_nResourcePort);
  m_prop.Add(_T("Remote Host"),m_strRemoteHost);
  m_prop.Add(_T("Remote Port"),m_nRemotePort);
  m_prop.Add(_T("Recurse"),executionpage.m_bRecurse);
  //m_prop.Add(_T("Loadfromdir"),executionpage.m_strLoaddir);
  m_prop.Add(_T("Farmed"),m_bFarmed);
  m_prop.Add(_T("Extension"),executionpage.m_strExtension);
  
  CeCosTrace::SetOutput(TestOutputCallback,this);
  CeCosTrace::SetError (TestOutputCallback,this);
  
  // m_psh can only be used to set the small icon.  Set the large one here.
  m_psh.hIcon=AfxGetApp()->LoadIcon(IDR_TT_MAINFRAME);
  //sheet.m_psh.dwFlags|=PSH_USEHICON/*|PSH_HASHELP*/;
  if(m_psh.hIcon){
    SetIcon(m_psh.hIcon,FALSE);
    SetIcon(m_psh.hIcon,TRUE);
  }
  GetWindowRect(m_rcPrev);
#ifdef _DEBUG
  CeCosTrace::EnableTracing(CeCosTrace::TRACE_LEVEL_TRACE);
#endif
  CeCosTrace::SetInteractive(true);
  
  if(m_pInitFunc){
    m_pInitFunc(&m_prop,false);
  }
  
  GetDlgItem(IDCANCEL)->SetWindowText(_T("&Close"));
  
  m_nTestsToComplete=0;
  BOOL bResult = CeCosPropertySheet::OnInitDialog();
  SetDlgItemText(IDOK,_T("&Run"));
  SetDlgItemText(ID_APPLY_NOW,_T("&Properties"));
  GetDlgItem(ID_APPLY_NOW)->EnableWindow(TRUE);
  GetDlgItem(IDCANCEL)->EnableWindow(TRUE); // required for modeless case
  
  SetActivePage(&outputpage);
  SetActivePage(&summarypage);
  SetActivePage(&executionpage);
 	
  if(m_pInitFunc){
    m_pInitFunc(&m_prop,false);
    outputpage.UpdateData(FALSE);
    summarypage.UpdateData(FALSE);
    executionpage.UpdateData(FALSE);
  }
  /*
  CString strCaption = _T("Output");
  TC_ITEM tcItem;
  tcItem.mask = TCIF_TEXT;
  tcItem.pszText = (LPTSTR)((LPCTSTR)strCaption);
  GetTabControl()->SetItem(2, &tcItem );
  strCaption=_T("Summary");
  GetTabControl()->SetItem(3, &tcItem );
  */
  // Allow resizing
  
  // WS_OVERLAPPEDWINDOW would preclude caption bar help button
  ModifyStyle(0,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME ,0);
  
  CRect rect;
  GetWindowRect(rect);
  m_rcPrev=rect;
  
  m_cxMin=rect.Width();
  m_cyMin=rect.Height();
  
  m_bAllowResizing=true;
  
  WINDOWPLACEMENT wndpl;
  if (5==_stscanf(m_strPlacement,_T("%d %d %d %d %d"),&rect.left,&rect.top,&rect.right,&rect.bottom,&wndpl.showCmd)){
    CRect rcMax;
    SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)(RECT *)rcMax, 0);
    
    if(rect.Width()<100 || rect.Height()<100 || rect.Width()>rcMax.Width() || rect.Height()>rcMax.Height()){
      rect=CFrameWnd::rectDefault;
    }
    
    wndpl.length = sizeof(WINDOWPLACEMENT);
    wndpl.flags = 0;
    
    wndpl.ptMinPosition = CPoint(0, 0);
    wndpl.ptMaxPosition =CPoint(-::GetSystemMetrics(SM_CXBORDER),-::GetSystemMetrics(SM_CYBORDER));
    wndpl.rcNormalPosition = rect;
    
    // sets window's position and iconized/maximized status
    SetWindowPlacement(&wndpl);
  }
  
  // Hack: force an initial sizing (without which the tab control is badly sized)
  m_rcOffset.left=m_rcOffset.right=m_rcOffset.top=0;
  
  m_rcOffset.bottom=m_bModal?50:-50;
  MoveWindow(GetTabControl(),Stretch);
  for(int i=0;i<GetPageCount();i++){
    MoveWindow(GetPage(i),Stretch);
  }
#ifdef _DEBUG
    for(CWnd *p=GetWindow(GW_CHILD);p;p=p->GetWindow(GW_HWNDNEXT)){
      TCHAR buf[256];
      ::GetClassName(p->m_hWnd,buf,sizeof buf);
      TRACE(_T("Window %x id=%d class=%s\n"),p,p->GetDlgCtrlID(),buf);
    }
#endif
  for(i=0;i<sizeof(arIds)/sizeof(arIds[0]);i++){
    CWnd *pWnd=GetDlgItem(arIds[i]);
    if(pWnd){
      MoveWindow(pWnd,BottomRight);
      pWnd->ShowWindow(SW_SHOW); // necessary in the modeless case
    } else {
      TRACE(_T("Failed to find window id=%x\n"),arIds[i]);
    }
  }

  // hack to lay buttons out correctly in application case
  if(this==AfxGetMainWnd()){
    CRect rect1,rect2;
    GetDlgItem(IDOK)->GetWindowRect(rect1);
    GetDlgItem(IDCANCEL)->GetWindowRect(rect2);
    CRect rect(rect1);
    rect.left-=(rect2.left-rect1.left);
    rect.right-=(rect2.right-rect1.right);
    ScreenToClient(rect);
    GetDlgItem(ID_APPLY_NOW)->MoveWindow(rect);
    GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_SHOW);
  }

  if(!m_bModal){
    SetTimer(0,100,0);
  }
  BringWindowToTop();
  return bResult;
}