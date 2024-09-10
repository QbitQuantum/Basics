void CGUIWindowFileManager::OnPopupMenu(int list, int item, bool bContextDriven /* = true */)
{
  if (list < 0 || list > 2) return ;
  bool bDeselect = SelectItem(list, item);
  // calculate the position for our menu
  float posX = 200;
  float posY = 100;
  const CGUIControl *pList = GetControl(CONTROL_LEFT_LIST + list);
  if (pList)
  {
    posX = pList->GetXPosition() + pList->GetWidth() / 2;
    posY = pList->GetYPosition() + pList->GetHeight() / 2;
  }

  CFileItemPtr pItem = m_vecItems[list]->Get(item);
  if (!pItem.get())
    return;

  if (m_Directory[list]->IsVirtualDirectoryRoot())
  {
    if (item < 0)
    { // TODO: We should add the option here for shares to be added if there aren't any
      return ;
    }

    // and do the popup menu
    if (CGUIDialogContextMenu::SourcesMenu("files", pItem, posX, posY))
    {
      m_rootDir.SetSources(g_settings.m_fileSources);
      if (m_Directory[1 - list]->IsVirtualDirectoryRoot())
        Refresh();
      else
        Refresh(list);
      return ;
    }
    pItem->Select(false);
    return ;
  }
  // popup the context menu
  CGUIDialogContextMenu *pMenu = (CGUIDialogContextMenu *)m_gWindowManager.GetWindow(WINDOW_DIALOG_CONTEXT_MENU);
  if (pMenu)
  {
    bool showEntry = false;
    if (item >= m_vecItems[list]->Size()) item = -1;
    if (item >= 0)
      showEntry=(!pItem->IsParentFolder() || (pItem->IsParentFolder() && m_vecItems[list]->GetSelectedCount()>0));

    // determine available players
    VECPLAYERCORES vecCores;
    CPlayerCoreFactory::GetPlayers(*pItem, vecCores);

    // load our menu
    pMenu->Initialize();
    // add the needed buttons
    int btn_SelectAll = pMenu->AddButton(188); // SelectAll

    int btn_HandleFavourite;  // Add/Remove Favourite
    if (CFavourites::IsFavourite(pItem.get(), GetID()))
      btn_HandleFavourite = pMenu->AddButton(14077);
    else
      btn_HandleFavourite = pMenu->AddButton(14076);

    int btn_PlayUsing = pMenu->AddButton(15213); // Play Using ..
    int btn_Rename = pMenu->AddButton(118); // Rename
    int btn_Delete = pMenu->AddButton(117); // Delete
    int btn_Copy = pMenu->AddButton(115); // Copy
    int btn_Move = pMenu->AddButton(116); // Move
    int btn_NewFolder = pMenu->AddButton(20309); // New Folder
    int btn_Size = pMenu->AddButton(13393); // Calculate Size
    int btn_Settings = pMenu->AddButton(5);     // Settings
    int btn_GoToRoot = pMenu->AddButton(20128); // Go To Root
    int btn_Switch = pMenu->AddButton(523);     // switch media

    pMenu->EnableButton(btn_SelectAll, item >= 0);
    pMenu->EnableButton(btn_HandleFavourite, item >=0 && !pItem->IsParentFolder());
    pMenu->EnableButton(btn_PlayUsing, item >= 0 && vecCores.size() > 1);
    pMenu->EnableButton(btn_Rename, item >= 0 && CanRename(list) && !pItem->IsParentFolder());
    pMenu->EnableButton(btn_Delete, item >= 0 && CanDelete(list) && showEntry);
    pMenu->EnableButton(btn_Copy, item >= 0 && CanCopy(list) && showEntry);
    pMenu->EnableButton(btn_Move, item >= 0 && CanMove(list) && showEntry);
    pMenu->EnableButton(btn_NewFolder, CanNewFolder(list));
    pMenu->EnableButton(btn_Size, item >=0 && pItem->m_bIsFolder && !pItem->IsParentFolder());

    // position it correctly
    pMenu->OffsetPosition(posX, posY);
    pMenu->DoModal();
    int btnid = pMenu->GetButton();
    if (btnid == btn_SelectAll)
    {
      OnSelectAll(list);
      bDeselect=false;
    }
    if (btnid == btn_HandleFavourite)
    {
      CFavourites::AddOrRemove(pItem.get(), GetID());
      return;
    }
    if (btnid == btn_PlayUsing)
    {
      VECPLAYERCORES vecCores;
      CPlayerCoreFactory::GetPlayers(*pItem, vecCores);
      g_application.m_eForcedNextPlayer = CPlayerCoreFactory::SelectPlayerDialog(vecCores);
      if (g_application.m_eForcedNextPlayer != EPC_NONE)
        OnStart(pItem.get());
    }
    if (btnid == btn_Rename)
      OnRename(list);
    if (btnid == btn_Delete)
      OnDelete(list);
    if (btnid == btn_Copy)
      OnCopy(list);
    if (btnid == btn_Move)
      OnMove(list);
    if (btnid == btn_NewFolder)
      OnNewFolder(list);
    if (btnid == btn_Size)
    {
      // setup the progress dialog, and show it
      CGUIDialogProgress *progress = (CGUIDialogProgress *)m_gWindowManager.GetWindow(WINDOW_DIALOG_PROGRESS);
      if (progress)
      {
        progress->SetHeading(13394);
        for (int i=0; i < 3; i++)
          progress->SetLine(i, "");
        progress->StartModal();
      }

      //  Calculate folder size for each selected item
      for (int i=0; i<m_vecItems[list]->Size(); ++i)
      {
        CFileItemPtr pItem2=m_vecItems[list]->Get(i);
        if (pItem2->m_bIsFolder && pItem2->IsSelected())
        {
          __int64 folderSize = CalculateFolderSize(pItem2->m_strPath, progress);
          if (folderSize >= 0)
          {
            pItem2->m_dwSize = folderSize;
            if (folderSize == 0)
              pItem2->SetLabel2(StringUtils::SizeToString(folderSize));
            else
              pItem2->SetFileSizeLabel();
          }
        }
      }
      if (progress)
        progress->Close();
    }
    if (btnid == btn_Settings)
    {
      m_gWindowManager.ActivateWindow(WINDOW_SETTINGS_MENU);
      return;
    }
    if (btnid == btn_GoToRoot)
    {
      Update(list,"");
      return;
    }
    if (btnid == btn_Switch)
    {
      CGUIDialogContextMenu::SwitchMedia("files", m_vecItems[list]->m_strPath);
      return;
    }

    if (bDeselect && item >= 0 && item < m_vecItems[list]->Size())
    { // deselect item as we didn't do anything
      pItem->Select(false);
    }
  }
}