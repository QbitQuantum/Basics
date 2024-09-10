bool CGUIWindowAddonBrowser::GetDirectory(const CStdString& strDirectory,
                                          CFileItemList& items)
{
  bool result;
  if (strDirectory.Equals("addons://downloading/"))
  {
    VECADDONS addons;
    CAddonInstaller::Get().GetInstallList(addons);

    CURL url(strDirectory);
    CAddonsDirectory::GenerateListing(url,addons,items);
    result = true;
    items.SetProperty("reponame",g_localizeStrings.Get(24067));
    items.SetPath(strDirectory);

    if (m_guiState.get() && !m_guiState->HideParentDirItems())
    {
      CFileItemPtr pItem(new CFileItem(".."));
      pItem->SetPath(m_history.GetParentPath());
      pItem->m_bIsFolder = true;
      pItem->m_bIsShareOrDrive = false;
      items.AddFront(pItem, 0);
    }

  }
  else
  {
    result = CGUIMediaWindow::GetDirectory(strDirectory,items);
    if (CSettings::Get().GetBool("general.addonforeignfilter"))
    {
      int i=0;
      while (i < items.Size())
      {
        if (!FilterVar(CSettings::Get().GetBool("general.addonforeignfilter"),
                      items[i]->GetProperty("Addon.Language"), "en") ||
            !FilterVar(CSettings::Get().GetBool("general.addonforeignfilter"),
                      items[i]->GetProperty("Addon.Language"),
                      g_langInfo.GetLanguageLocale()))
        {
          i++;
        }
        else
          items.Remove(i);
      }
    }
  }

  if (strDirectory.IsEmpty() && CAddonInstaller::Get().IsDownloading())
  {
    CFileItemPtr item(new CFileItem("addons://downloading/",true));
    item->SetLabel(g_localizeStrings.Get(24067));
    item->SetLabelPreformated(true);
    item->SetIconImage("DefaultNetwork.png");
    items.Add(item);
  }

  items.SetContent("addons");

  for (int i=0;i<items.Size();++i)
    SetItemLabel2(items[i]);

  return result;
}