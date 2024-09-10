/*!
  \brief Overwrite to fill fileitems from a source
  \param strDirectory Path to read
  \param items Fill with items specified in \e strDirectory
  */
bool CGUIMediaWindow::GetDirectory(const CStdString &strDirectory, CFileItemList &items)
{
  // cleanup items
  if (items.Size())
    items.Clear();

  CStdString strParentPath=m_history.GetParentPath();

  CLog::Log(LOGDEBUG,"CGUIMediaWindow::GetDirectory (%s)", strDirectory.c_str());
  CLog::Log(LOGDEBUG,"  ParentPath = [%s]", strParentPath.c_str());

  // see if we can load a previously cached folder
  CFileItemList cachedItems(strDirectory);
  if (!strDirectory.IsEmpty() && cachedItems.Load())
  {
    items.Assign(cachedItems);
  }
  else
  {
    DWORD time = timeGetTime();

    if (!m_rootDir.GetDirectory(strDirectory, items))
      return false;

    // took over a second, and not normally cached, so cache it
    if (time + 1000 < timeGetTime() && items.CacheToDiscIfSlow())
      items.Save();

    // if these items should replace the current listing, then pop it off the top
    if (items.GetReplaceListing())
      m_history.RemoveParentPath();
  }

  if (m_guiState.get() && !m_guiState->HideParentDirItems() && !items.m_strPath.IsEmpty())
  {
    CFileItemPtr pItem(new CFileItem(".."));
    pItem->m_strPath = strParentPath;
    pItem->m_bIsFolder = true;
    pItem->m_bIsShareOrDrive = false;
    items.AddFront(pItem, 0);
  }

  int iWindow = GetID();
  CStdStringArray regexps;

  if (iWindow == WINDOW_VIDEO_FILES)
    regexps = g_advancedSettings.m_videoExcludeFromListingRegExps;
  if (iWindow == WINDOW_MUSIC_FILES)
    regexps = g_advancedSettings.m_audioExcludeFromListingRegExps;
  if (iWindow == WINDOW_PICTURES)
    regexps = g_advancedSettings.m_pictureExcludeFromListingRegExps;

  if (regexps.size())
  {
    for (int i=0; i < items.Size();)
    {
      if (CUtil::ExcludeFileOrFolder(items[i]->m_strPath, regexps))
        items.Remove(i);
      else
        i++;
    }
  }

  // clear window properties at root or plugin root
  if (items.IsVirtualDirectoryRoot() || items.IsPluginRoot())
    ClearProperties();

  return true;
}