bool CGUIDialogSubtitles::SetService(const std::string &service)
{
  if (service != m_currentService)
  {
    m_currentService = service;
    CLog::Log(LOGDEBUG, "New Service [%s] ", m_currentService.c_str());

    CFileItemPtr currentService = GetService();
    // highlight this item in the skin
    for (int i = 0; i < m_serviceItems->Size(); i++)
    {
      CFileItemPtr pItem = m_serviceItems->Get(i);
      pItem->Select(pItem == currentService);
    }

    SET_CONTROL_LABEL(CONTROL_NAMELABEL, currentService->GetLabel());

    if (currentService->HasAddonInfo())
    {
      std::string icon = URIUtils::AddFileToFolder(currentService->GetAddonInfo()->Path(), "logo.png");
      SET_CONTROL_FILENAME(CONTROL_NAMELOGO, icon);
    }

    if (g_application.m_pPlayer->GetSubtitleCount() == 0)
      SET_CONTROL_HIDDEN(CONTROL_SUBSEXIST);
    else
      SET_CONTROL_VISIBLE(CONTROL_SUBSEXIST);

    return true;
  }
  return false;
}