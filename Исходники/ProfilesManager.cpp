bool CProfilesManager::DeleteProfile(size_t index)
{
  CSingleLock lock(m_critical);
  const CProfile *profile = GetProfile(index);
  if (profile == NULL)
    return false;

  CGUIDialogYesNo* dlgYesNo = (CGUIDialogYesNo*)g_windowManager.GetWindow(WINDOW_DIALOG_YES_NO);
  if (dlgYesNo == NULL)
    return false;

  string message;
  string str = g_localizeStrings.Get(13201);
  message = StringUtils::Format(str.c_str(), profile->getName().c_str());
  dlgYesNo->SetHeading(13200);
  dlgYesNo->SetLine(0, message);
  dlgYesNo->SetLine(1, "");
  dlgYesNo->SetLine(2, "");
  dlgYesNo->DoModal();

  if (!dlgYesNo->IsConfirmed())
    return false;

  // fall back to master profile if necessary
  if ((int)index == m_autoLoginProfile)
    m_autoLoginProfile = 0;

  // delete profile
  string strDirectory = profile->getDirectory();
  m_profiles.erase(m_profiles.begin() + index);

  // fall back to master profile if necessary
  if (index == m_currentProfile)
  {
    LoadProfile(0);
    CSettings::Get().Save();
  }

  CFileItemPtr item = CFileItemPtr(new CFileItem(URIUtils::AddFileToFolder(GetUserDataFolder(), strDirectory)));
  item->SetPath(URIUtils::AddFileToFolder(GetUserDataFolder(), strDirectory + "/"));
  item->m_bIsFolder = true;
  item->Select(true);
  CFileUtils::DeleteItem(item);

  return Save();
}