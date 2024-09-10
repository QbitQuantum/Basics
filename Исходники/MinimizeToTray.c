void Hide()
{
  EDITINFO ei;
  const wchar_t *wpFileName=NULL;

  //Get tip
  if (SendMessage(hMainWnd, AKD_GETEDITINFO, (WPARAM)NULL, (LPARAM)&ei))
  {
    if (*ei.wszFile)
      wpFileName=GetFileName(ei.wszFile, -1);
  }
  xprintfW(wszBuffer, L"%s%s%s", wpFileName, wpFileName?L" - ":NULL, L"AkelPad");

  if (bOldWindows)
  {
    NOTIFYICONDATAA nid;

    //Set tip
    WideCharToMultiByte(CP_ACP, 0, wszBuffer, -1, nid.szTip, 64, NULL, NULL);
    nid.szTip[63]='\0';

    //Add notify icon
    nid.cbSize=sizeof(nid);
    nid.hWnd=hMainWnd;
    nid.uID=0;
    nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
    nid.uCallbackMessage=nMinimizeToTrayMessage;
    nid.hIcon=(HICON)hMainSmallIcon;
    Shell_NotifyIconA(NIM_ADD, &nid);
  }
  else
  {
    NOTIFYICONDATAW nid;

    //Set tip
    xstrcpynW(nid.szTip, wszBuffer, 64);

    //Add notify icon
    nid.cbSize=sizeof(nid);
    nid.hWnd=hMainWnd;
    nid.uID=0;
    nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
    nid.uCallbackMessage=nMinimizeToTrayMessage;
    nid.hIcon=(HICON)hMainSmallIcon;
    Shell_NotifyIconW(NIM_ADD, &nid);
  }

  if (!bCmdShow)
  {
    //Hide main window
    ShowWindow(hMainWnd, SW_MINIMIZE);
    ShowWindow(hMainWnd, SW_HIDE);
  }
}