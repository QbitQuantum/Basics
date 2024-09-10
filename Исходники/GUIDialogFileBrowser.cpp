bool CGUIDialogFileBrowser::OnMessage(CGUIMessage& message)
{
  switch ( message.GetMessage() )
  {
  case GUI_MSG_WINDOW_DEINIT:
    {
      if (m_thumbLoader.IsLoading())
        m_thumbLoader.StopThread();
      CGUIDialog::OnMessage(message);
      ClearFileItems();
      m_addNetworkShareEnabled = false;
      return true;
    }
    break;

  case GUI_MSG_WINDOW_INIT:
    {
      m_bConfirmed = false;
      m_bFlip = false;
      bool bIsDir = false;
      // this code allows two different selection modes for directories
      // end the path with a slash to start inside the directory
      if (URIUtils::HasSlashAtEnd(m_selectedPath))
      {
        bIsDir = true;
        bool bFool;
        int iSource = CUtil::GetMatchingSource(m_selectedPath,m_shares,bFool);
        bFool = true;
        if (iSource > -1 && iSource < (int)m_shares.size())
        {
          if (URIUtils::PathEquals(m_shares[iSource].strPath, m_selectedPath))
            bFool = false;
        }

        if (bFool && !CDirectory::Exists(m_selectedPath))
          m_selectedPath.clear();
      }
      else
      {
        if (!CFile::Exists(m_selectedPath) && !CDirectory::Exists(m_selectedPath))
            m_selectedPath.clear();
      }

      // find the parent folder if we are a file browser (don't do this for folders)
      m_Directory->SetPath(m_selectedPath);
      if (!m_browsingForFolders && !bIsDir)
        m_Directory->SetPath(URIUtils::GetParentPath(m_selectedPath));
      Update(m_Directory->GetPath());
      m_viewControl.SetSelectedItem(m_selectedPath);
      return CGUIDialog::OnMessage(message);
    }
    break;

  case GUI_MSG_CLICKED:
    {
      if (m_viewControl.HasControl(message.GetSenderId()))  // list control
      {
        int iItem = m_viewControl.GetSelectedItem();
        int iAction = message.GetParam1();
        if (iItem < 0) break;
        CFileItemPtr pItem = (*m_vecItems)[iItem];
        if ((iAction == ACTION_SELECT_ITEM || iAction == ACTION_MOUSE_LEFT_CLICK) &&
           (!m_multipleSelection || pItem->m_bIsShareOrDrive || pItem->m_bIsFolder))
        {
          OnClick(iItem);
          return true;
        }
        else if ((iAction == ACTION_HIGHLIGHT_ITEM || iAction == ACTION_MOUSE_LEFT_CLICK || iAction == ACTION_SELECT_ITEM) &&
                (m_multipleSelection && !pItem->m_bIsShareOrDrive && !pItem->m_bIsFolder))
        {
          pItem->Select(!pItem->IsSelected());
          CGUIMessage msg(GUI_MSG_ITEM_SELECT, GetID(), message.GetSenderId(), iItem + 1);
          OnMessage(msg);
        }
      }
      else if (message.GetSenderId() == CONTROL_OK)
      {
        if (m_browsingForFolders == 2)
        {
          int iItem = m_viewControl.GetSelectedItem();

          std::string strPath;
          if (iItem == 0)
            strPath = m_selectedPath;
          else
            strPath = (*m_vecItems)[iItem]->GetPath();

          std::string strTest = URIUtils::AddFileToFolder(strPath, "1");
          CFile file;
          if (file.OpenForWrite(strTest,true))
          {
            file.Close();
            CFile::Delete(strTest);
            m_bConfirmed = true;
            Close();
          }
          else
            HELPERS::ShowOKDialogText(CVariant{257}, CVariant{20072});
        }
        else
        {
          if (m_multipleSelection)
          {
            for (int iItem = 0; iItem < m_vecItems->Size(); ++iItem)
            {
              CFileItemPtr pItem = (*m_vecItems)[iItem];
              if (pItem->IsSelected())
                m_markedPath.push_back(pItem->GetPath());
            }
          }
          m_bConfirmed = true;
          Close();
        }
        return true;
      }
      else if (message.GetSenderId() == CONTROL_CANCEL)
      {
        Close();
        return true;
      }
      else if (message.GetSenderId() == CONTROL_NEWFOLDER)
      {
        std::string strInput;
        if (CGUIKeyboardFactory::ShowAndGetInput(strInput, CVariant{g_localizeStrings.Get(119)}, false))
        {
          std::string strPath = URIUtils::AddFileToFolder(m_vecItems->GetPath(), strInput);
          if (CDirectory::Create(strPath))
            Update(m_vecItems->GetPath());
          else
            HELPERS::ShowOKDialogText(CVariant{20069}, CVariant{20072});
        }
      }
      else if (message.GetSenderId() == CONTROL_FLIP)
        m_bFlip = !m_bFlip;
    }
    break;
  case GUI_MSG_SETFOCUS:
    {
      if (m_viewControl.HasControl(message.GetControlId()) && m_viewControl.GetCurrentControl() != message.GetControlId())
      {
        m_viewControl.SetFocused();
        return true;
      }
    }
    break;
  case GUI_MSG_NOTIFY_ALL:
    { // Message is received only if this window is active
      if (message.GetParam1() == GUI_MSG_REMOVED_MEDIA)
      {
        if (m_Directory->IsVirtualDirectoryRoot() && IsActive())
        {
          int iItem = m_viewControl.GetSelectedItem();
          Update(m_Directory->GetPath());
          m_viewControl.SetSelectedItem(iItem);
        }
        else if (m_Directory->IsRemovable())
        { // check that we have this removable share still
          if (!m_rootDir.IsInSource(m_Directory->GetPath()))
          { // don't have this share any more
            if (IsActive()) Update("");
            else
            {
              m_history.ClearPathHistory();
              m_Directory->SetPath("");
            }
          }
        }
        return true;
      }
      else if (message.GetParam1()==GUI_MSG_UPDATE_SOURCES)
      { // State of the sources changed, so update our view
        if (m_Directory->IsVirtualDirectoryRoot() && IsActive())
        {
          int iItem = m_viewControl.GetSelectedItem();
          Update(m_Directory->GetPath());
          m_viewControl.SetSelectedItem(iItem);
        }
        return true;
      }
      else if (message.GetParam1()==GUI_MSG_UPDATE_PATH)
      {
        if (IsActive())
        {
          if((message.GetStringParam() == m_Directory->GetPath()) ||
             (m_Directory->IsMultiPath() && XFILE::CMultiPathDirectory::HasPath(m_Directory->GetPath(), message.GetStringParam())))
          {
            int iItem = m_viewControl.GetSelectedItem();
            Update(m_Directory->GetPath());
            m_viewControl.SetSelectedItem(iItem);
          }
        }
      }
    }
    break;

  }
  return CGUIDialog::OnMessage(message);
}