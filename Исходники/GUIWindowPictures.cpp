void CGUIWindowPictures::OnPrepareFileItems(CFileItemList& items)
{
  CGUIMediaWindow::OnPrepareFileItems(items);

  for (int i=0;i<items.Size();++i )
    if (StringUtils::EqualsNoCase(items[i]->GetLabel(), "folder.jpg"))
      items.Remove(i);

  if (items.GetFolderCount() == items.Size() || !CServiceBroker::GetSettings().GetBool(CSettings::SETTING_PICTURES_USETAGS))
    return;

  // Start the music info loader thread
  CPictureInfoLoader loader;
  loader.SetProgressCallback(m_dlgProgress);
  loader.Load(items);

  bool bShowProgress = !CServiceBroker::GetGUI()->GetWindowManager().HasModalDialog(true);
  bool bProgressVisible = false;

  unsigned int tick=XbmcThreads::SystemClockMillis();

  while (loader.IsLoading() && m_dlgProgress && !m_dlgProgress->IsCanceled())
  {
    if (bShowProgress)
    { // Do we have to init a progress dialog?
      unsigned int elapsed=XbmcThreads::SystemClockMillis()-tick;

      if (!bProgressVisible && elapsed>1500 && m_dlgProgress)
      { // tag loading takes more then 1.5 secs, show a progress dialog
        CURL url(items.GetPath());

        m_dlgProgress->SetHeading(CVariant{189});
        m_dlgProgress->SetLine(0, CVariant{505});
        m_dlgProgress->SetLine(1, CVariant{""});
        m_dlgProgress->SetLine(2, CVariant{url.GetWithoutUserDetails()});
        m_dlgProgress->Open();
        m_dlgProgress->ShowProgressBar(true);
        bProgressVisible = true;
      }

      if (bProgressVisible && m_dlgProgress)
      { // keep GUI alive
        m_dlgProgress->Progress();
      }
    } // if (bShowProgress)
    Sleep(1);
  } // while (loader.IsLoading())

  if (bProgressVisible && m_dlgProgress)
    m_dlgProgress->Close();
}