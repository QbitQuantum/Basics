bool CGUIWindowLoginScreen::OnPopupMenu(int iItem)
{
  if ( iItem < 0 || iItem >= m_vecItems->Size() ) return false;
  // calculate our position
  float posX = 200, posY = 100;
  const CGUIControl *pList = GetControl(CONTROL_BIG_LIST);
  if (pList)
  {
    posX = pList->GetXPosition() + pList->GetWidth() / 2;
    posY = pList->GetYPosition() + pList->GetHeight() / 2;
  }

  bool bSelect = m_vecItems->Get(iItem)->IsSelected();
  // mark the item
  m_vecItems->Get(iItem)->Select(true);

  // popup the context menu
  CGUIDialogContextMenu *pMenu = (CGUIDialogContextMenu *)m_gWindowManager.GetWindow(WINDOW_DIALOG_CONTEXT_MENU);
  if (!pMenu) return false;

  // initialize the menu (loaded on demand)
  pMenu->Initialize();

  int btn_EditProfile   = pMenu->AddButton(20067);
  int btn_DeleteProfile = 0;
  int btn_ResetLock = 0;
/*  if (m_viewControl.GetSelectedItem() != 0) // no deleting the default profile
    btn_DeleteProfile = pMenu->AddButton(117); */
  if (iItem == 0 && g_passwordManager.iMasterLockRetriesLeft == 0)
    btn_ResetLock = pMenu->AddButton(12334);

  // position it correctly
  pMenu->SetPosition(posX - pMenu->GetWidth() / 2, posY - pMenu->GetHeight() / 2);
  pMenu->DoModal();

  int btnid = pMenu->GetButton();
  if (btnid > 0)
  {
    if (btnid == btn_ResetLock)
    {
      if (g_passwordManager.CheckLock(g_settings.m_vecProfiles[0].getLockMode(),g_settings.m_vecProfiles[0].getLockCode(),20075))
        g_passwordManager.iMasterLockRetriesLeft = g_guiSettings.GetInt("masterlock.maxretries");
      else // be inconvenient
        g_application.getApplicationMessenger().Shutdown();

      return true;
    }
    if (!g_passwordManager.IsMasterLockUnlocked(true))
      return false;

    if (btnid == btn_EditProfile)
      CGUIDialogProfileSettings::ShowForProfile(m_viewControl.GetSelectedItem());
    if (btnid == btn_DeleteProfile)
    {
      int iDelete = m_viewControl.GetSelectedItem();
      m_viewControl.Clear();
      g_settings.DeleteProfile(iDelete);
      Update();
      m_viewControl.SetSelectedItem(0);
    }
  }
  //NOTE: this can potentially (de)select the wrong item if the filelisting has changed because of an action above.
  if (iItem < (int)g_settings.m_vecProfiles.size())
    m_vecItems->Get(iItem)->Select(bSelect);

  return (btnid > 0);
}