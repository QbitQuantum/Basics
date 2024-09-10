/*** Will be called before the first display of the dialog *******************/
BOOL CCalendarDlg2::OnInitDialog()
{
    m_mcMonthCal.SetHolidaysFromFile(_T("HOLIDAYS.INI"));
    m_mcMonthCal.pDelegates=this;
    CResizeableDialog::OnInitDialog();
    // ֿאנסטל פאיכ
    CString sContent;
    ReadFile(sMainFile,sContent);
    sContent.Replace("\r\n","\n");
    sContent=CString("\n")+sContent+"\n";
    while(sContent!="") {
        CString sLine=sContent.SpanExcluding("\n");
        if(sLine!="") {
            aItems.Add(sLine);
            if(sContent.GetLength()>sLine.GetLength()) {
                sContent=sContent.Mid(sLine.GetLength()+1);
            } else {
                sContent="";
            }
        }
        sContent.TrimLeft();
    }
    LRESULT lRes=0;
    NMDAYSTATE pDayState;
    SYSTEMTIME stMinRange, stMaxRange;
    memset(&pDayState,0,sizeof(pDayState));
    m_mcMonthCal.GetMonthRange(&stMinRange, &stMaxRange, GMR_DAYSTATE);
    pDayState.cDayState=(stMaxRange.wYear - stMinRange.wYear) * 12 + stMaxRange.wMonth - stMinRange.wMonth + 1;
    memcpy(&pDayState.stStart,&stMinRange,sizeof(SYSTEMTIME));
    OnGetdaystate((NMHDR*)&pDayState,&lRes);
    //pDayState.prgDayState[0]=0xffff;
    //memset(pDayState.prgDayState,555,5*sizeof(MONTHDAYSTATE));
    m_mcMonthCal.SetDayState(pDayState.cDayState,pDayState.prgDayState);
    m_mcMonthCal.Invalidate();

    //-----------------------------------
    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon
    GetDlgItem(IDC_STATIC1)->SetWindowText(_l(sStatic1));
    GetDlgItem(IDC_STATIC2)->SetWindowText(_l(sStatic2));
    SetWindowText(_l(sTitle));
    GetDlgItem(IDOK)->SetWindowText(_l(sButton));
    GetDlgItem(IDCLEAR)->SetWindowText(_l("Clear field"));
    // Register resizable controls
    RegisterControl(IDC_STATIC1, ATTACH_TO_TOP_EDGE | ATTACH_TO_VERTICAL_EDGES);
    RegisterControl(IDC_MONTHCALENDAR1, ATTACH_TO_TOP_EDGE | ATTACH_TO_VERTICAL_EDGES);
    RegisterControl(IDC_STATIC2, ATTACH_TO_TOP_EDGE | ATTACH_TO_VERTICAL_EDGES);
    RegisterControl(IDC_EDIT_TXT, ATTACH_TO_TOP_EDGE | ATTACH_TO_VERTICAL_EDGES);
    RegisterControl(IDC_STATIC3, ATTACH_TO_BOTTOM_EDGE | ATTACH_TO_LEFT_EDGE);
    RegisterControl(IDCLEAR, ATTACH_TO_BOTTOM_EDGE | ATTACH_TO_LEFT_EDGE);
    RegisterControl(IDOK, ATTACH_TO_BOTTOM_EDGE | ATTACH_TO_RIGHT_EDGE);
    // Calculate minimum and maximum size of calendar window
    CRect rect;
    m_mcMonthCal.GetClientRect(rect);
    int nWidth  = rect.Width();
    int nHeight = rect.Height();

    if (m_mcMonthCal.GetMinReqRect(rect))
    {
        int   nMinWidth   = rect.Width();
        int   nMinHeight  = rect.Height();
        int   nDiffWidth  = nMinWidth  - nWidth;
        int   nDiffHeight = nMinHeight - nHeight;
        CRect rectOffset(nDiffWidth/2, nDiffHeight/2, nDiffWidth/2 + nDiffWidth%2,
                         nDiffHeight/2 + nDiffHeight%2);

        GetWindowRect(rect);
        rect += rectOffset;
        MoveWindow(rect);
        ThisSizeIsMinSize();

        int nMaxWidth  = nMinWidth  * 2 +  6*(3-1);
        int nMaxHeight = nMinHeight * 2 + 13*(4-1);

        nDiffWidth  = nMaxWidth  - nWidth;
        nDiffHeight = nMaxHeight - nHeight;
        rectOffset  = CRect(nDiffWidth/2, nDiffHeight/2,
                            nDiffWidth/2 + nDiffWidth%2,
                            nDiffHeight/2 + nDiffHeight%2);

        GetWindowRect(rect);
        rect += rectOffset;

        int nScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
        int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
        if (rect.Width() > nScreenWidth)
        {
            rect.left  = 0;
            rect.right = nScreenWidth-1;
        }
        if (rect.Height() > nScreenHeight)
        {
            rect.top    = 0;
            rect.bottom = nScreenHeight-1;
        }
        m_nMaxWidth  = m_nMinWidth*2;
        m_nMaxHeight = m_nMinHeight;
        /*
        MoveWindow(rect);
        ThisSizeIsMaxSize();

        CRect rtBegin(rect);
        MoveWindow(rtBegin);
        */
    }
    SYSTEMTIME sysTime;
    GetSystemTime(&sysTime);
    BOOL bResult = (BOOL)::SendMessage(m_mcMonthCal, MCM_SETCURSEL, 0, (LPARAM) &sysTime);
    SetTextForDay(&sysTime);
    return TRUE;  // return TRUE  unless you set the focus to a control
}