bool CGUIWindowPrograms::OnChooseVideoModeAndLaunch(int item)
{
  if (item < 0 || item >= m_vecItems->Size()) return false;
  // calculate our position
  float posX = 200;
  float posY = 100;
  const CGUIControl *pList = GetControl(CONTROL_LIST);
  if (pList)
  {
    posX = pList->GetXPosition() + pList->GetWidth() / 2;
    posY = pList->GetYPosition() + pList->GetHeight() / 2;
  }

  // grab the context menu
  CGUIDialogContextMenu *pMenu = (CGUIDialogContextMenu *)g_windowManager.GetWindow(WINDOW_DIALOG_CONTEXT_MENU);
  if (!pMenu) return false;

  pMenu->Initialize();

  int btn_PAL;
  int btn_NTSCM;
  int btn_NTSCJ;
  int btn_PAL60;
  CStdString strPAL, strNTSCJ, strNTSCM, strPAL60;
  strPAL = "PAL";
  strNTSCM = "NTSC-M";
  strNTSCJ = "NTSC-J";
  strPAL60 = "PAL-60";
  int iRegion = GetRegion(item,true);

  if (iRegion == VIDEO_NTSCM)
    strNTSCM += " (default)";
  if (iRegion == VIDEO_NTSCJ)
    strNTSCJ += " (default)";
  if (iRegion == VIDEO_PAL50)
    strPAL += " (default)";

  btn_PAL = pMenu->AddButton(strPAL);
  btn_NTSCM = pMenu->AddButton(strNTSCM);
  btn_NTSCJ = pMenu->AddButton(strNTSCJ);
  btn_PAL60 = pMenu->AddButton(strPAL60);

  pMenu->OffsetPosition(posX, posY);
  pMenu->DoModal();
  int btnid = pMenu->GetButton();

  if (btnid == btn_NTSCM)
  {
    m_iRegionSet = VIDEO_NTSCM;
    m_database.SetRegion(m_vecItems->Get(item)->GetPath(),1);
  }
  if (btnid == btn_NTSCJ)
  {
    m_iRegionSet = VIDEO_NTSCJ;
    m_database.SetRegion(m_vecItems->Get(item)->GetPath(),2);
  }
  if (btnid == btn_PAL)
  {
    m_iRegionSet = VIDEO_PAL50;
    m_database.SetRegion(m_vecItems->Get(item)->GetPath(),4);
  }
  if (btnid == btn_PAL60)
  {
    m_iRegionSet = VIDEO_PAL60;
    m_database.SetRegion(m_vecItems->Get(item)->GetPath(),8);
  }

  if (btnid > -1)
    return OnClick(item);

  return true;
}