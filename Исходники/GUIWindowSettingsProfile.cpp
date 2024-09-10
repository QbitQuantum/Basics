void CGUIWindowSettingsProfile::OnPopupMenu(int iItem)
{
  // calculate our position
  float posX = 200;
  float posY = 100;
  const CGUIControl *pList = GetControl(CONTROL_PROFILES);
  if (pList)
  {
    posX = pList->GetXPosition() + pList->GetWidth() / 2;
    posY = pList->GetYPosition() + pList->GetHeight() / 2;
  }
  // popup the context menu
  CGUIDialogContextMenu *pMenu = (CGUIDialogContextMenu *)g_windowManager.GetWindow(WINDOW_DIALOG_CONTEXT_MENU);
  if (!pMenu) return ;
  // load our menu
  pMenu->Initialize();
  if (iItem == (int)g_settings.m_vecProfiles.size())
    return;

  // add the needed buttons
  int btnLoad = pMenu->AddButton(20092); // load profile
  int btnDelete=0;
  if (iItem > 0)
    btnDelete = pMenu->AddButton(117); // Delete

  // position it correctly
  pMenu->OffsetPosition(posX, posY);
  pMenu->DoModal();
  int iButton = pMenu->GetButton();
  if (iButton == btnLoad)
  {
    unsigned iCtrlID = GetFocusedControlID();
    g_application.StopPlaying();
    CGUIMessage msg2(GUI_MSG_ITEM_SELECTED, g_windowManager.GetActiveWindow(), iCtrlID);
    g_windowManager.SendMessage(msg2);
    g_application.getNetwork().NetworkMessage(CNetwork::SERVICES_DOWN,1);
#ifdef HAS_XBOX_NETWORK
    g_network.Deinitialize();
#endif
    bool bOldMaster = g_passwordManager.bMasterUser;
    g_passwordManager.bMasterUser = true;
    g_settings.LoadProfile(iItem);
    g_application.StartEventServer(); // event server could be needed in some situations

    g_settings.m_vecProfiles[g_settings.m_iLastLoadedProfileIndex].setDate();
    g_settings.SaveProfiles(PROFILES_FILE); // to set last loaded

    g_passwordManager.bMasterUser = bOldMaster;
    CGUIMessage msg3(GUI_MSG_SETFOCUS, g_windowManager.GetActiveWindow(), iCtrlID, 0);
    OnMessage(msg3);
    CGUIMessage msgSelect(GUI_MSG_ITEM_SELECT, g_windowManager.GetActiveWindow(), iCtrlID, msg2.GetParam1(), msg2.GetParam2());
    OnMessage(msgSelect);
    CWeather::GetInstance().Refresh();
  }

  if (iButton == btnDelete)
  {
    if (g_settings.DeleteProfile(iItem))
      iItem--;
  }

  LoadList();
  CGUIMessage msg(GUI_MSG_ITEM_SELECT, GetID(),CONTROL_PROFILES,iItem);
  OnMessage(msg);
}