void CGUIDialogVideoBookmarks::AddEpisodeBookmark()
{
  vector<CVideoInfoTag> episodes;
  CVideoDatabase videoDatabase;
  CPoint pos;
  videoDatabase.Open();
  videoDatabase.GetEpisodesByFile(g_application.CurrentFile(), episodes);
  videoDatabase.Close();
  if(episodes.size() > 0)
  {
    CGUIDialogContextMenu *pMenu = (CGUIDialogContextMenu *)g_windowManager.GetWindow(WINDOW_DIALOG_CONTEXT_MENU);
    map<int, CVideoInfoTag*> buttons;
    const CGUIControl *pList = GetControl(CONTROL_ADD_EPISODE_BOOKMARK);
    if (pList)
      pos = pList->GetRenderPosition() + CPoint(pList->GetWidth() * 0.5f, pList->GetHeight() * 0.5f);
    if (pMenu)
    {
      pMenu->Initialize();
      for (unsigned int i=0; i < episodes.size(); ++i)
      {
        CStdString strButton;
        strButton.Format("%s %i, %s %i", g_localizeStrings.Get(20373), episodes[i].m_iSeason, g_localizeStrings.Get(20359).c_str(), episodes[i].m_iEpisode);
        buttons[pMenu->AddButton(strButton)] = &episodes[i];
      }

      pMenu->OffsetPosition(pos.x, pos.y);
      pMenu->DoModal(GetID());

      int pressed = pMenu->GetButton();
      if (buttons.find(pressed) != buttons.end())
        AddBookmark(buttons[pressed]);
    }
  }
}