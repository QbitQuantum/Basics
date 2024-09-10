void InitCOMscopeBufferSize(HWND hwndDlg,ULONG ulBuffLen,int iResDevider)
  {
  USHORT  usCount;
  SLDCDATA  SliderData;
  WNDPARAMS wprm;
  CHAR   acBuffer[10];
  int iExtent = 249;

  if (iResDevider == 2)
    iExtent = 125;
  SliderData.cbSize = sizeof(SLDCDATA);
  SliderData.usScale1Increments = iExtent;
  SliderData.usScale1Spacing = 1;
  SliderData.usScale2Increments = iExtent; // 249
  SliderData.usScale2Spacing = 1;

  wprm.fsStatus = WPM_CTLDATA;
  wprm.cchText = 0;
  wprm.cbPresParams = 0;
  wprm.cbCtlData = 0;
  wprm.pCtlData = &SliderData;
  WinSendDlgItemMsg(hwndDlg,PCFG_BUFF_SLIDER,
                    WM_SETWINDOWPARAMS,(MPARAM)&wprm,(MPARAM)NULL ) ;

  WinSendDlgItemMsg(hwndDlg,PCFG_BUFF_SLIDER,SLM_SETSLIDERINFO,
                    MPFROM2SHORT(SMA_SLIDERARMPOSITION,SMA_RANGEVALUE),MPFROMSHORT((ulBuffLen / 128 / iResDevider) - (8 / iResDevider)));

  WinSendDlgItemMsg(hwndDlg,PCFG_BUFF_SLIDER,
                    SLM_SETTICKSIZE,MPFROM2SHORT(0,5),NULL);
  WinSendDlgItemMsg(hwndDlg,PCFG_BUFF_SLIDER,SLM_SETSCALETEXT,
                    MPFROMSHORT(0), MPFROMP("1k"));
  for (usCount = 1; usCount < 4; usCount++ )
    {
    WinSendDlgItemMsg(hwndDlg,PCFG_BUFF_SLIDER,
                      SLM_SETTICKSIZE,MPFROM2SHORT(((usCount * 64 / iResDevider) - (8 / iResDevider)),5),NULL);
    sprintf(acBuffer,"%uK",(usCount * 8));
    WinSendDlgItemMsg(hwndDlg,PCFG_BUFF_SLIDER,SLM_SETSCALETEXT,
                      MPFROMSHORT(((usCount * 64 / iResDevider) - (8 / iResDevider))), MPFROMP(acBuffer));
    }
  WinSendDlgItemMsg(hwndDlg,PCFG_BUFF_SLIDER,
                    SLM_SETTICKSIZE,MPFROM2SHORT((iExtent - 1),5),NULL);
  WinSendDlgItemMsg(hwndDlg,PCFG_BUFF_SLIDER,SLM_SETSCALETEXT,
                    MPFROMSHORT(iExtent - 1), MPFROMP("32K"));

  WinSetDlgItemText(hwndDlg,PCFG_BUFF_DATA,
                    ltoa(ulBuffLen,acBuffer,10));
  }