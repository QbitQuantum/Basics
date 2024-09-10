void CGUIWindowVideoNav::OnLinkMovieToTvShow(int itemnumber, bool bRemove)
{
  CFileItemList list;
  if (bRemove)
  {
    vector<int> ids;
    if (!m_database.GetLinksToTvShow(m_vecItems->Get(itemnumber)->GetVideoInfoTag()->m_iDbId,ids))
      return;
    for (unsigned int i=0;i<ids.size();++i)
    {
      CVideoInfoTag tag;
      m_database.GetTvShowInfo("",tag,ids[i]);
      CFileItemPtr show(new CFileItem(tag));
      list.Add(show);
    }
  }
  else
  {
    m_database.GetTvShowsNav("videodb://2/2",list);

    // remove already linked shows
    vector<int> ids;
    if (!m_database.GetLinksToTvShow(m_vecItems->Get(itemnumber)->GetVideoInfoTag()->m_iDbId,ids))
      return;
    for (int i=0;i<list.Size();)
    {
      unsigned int j;
      for (j=0;j<ids.size();++j)
      {
        if (list[i]->GetVideoInfoTag()->m_iDbId == ids[j])
          break;
      }
      if (j == ids.size())
        i++;
      else
        list.Remove(i);
    }
  }
  int iSelectedLabel = 0;
  if (list.Size() > 1)
  {
    list.Sort(g_guiSettings.GetBool("filelists.ignorethewhensorting") ? SORT_METHOD_LABEL_IGNORE_THE : SORT_METHOD_LABEL, SORT_ORDER_ASC);
    CGUIDialogSelect* pDialog = (CGUIDialogSelect*)g_windowManager.GetWindow(WINDOW_DIALOG_SELECT);
    pDialog->Reset();
    pDialog->SetItems(&list);
    pDialog->SetHeading(20356);
    pDialog->DoModal();
    iSelectedLabel = pDialog->GetSelectedLabel();
  }
  if (iSelectedLabel > -1)
  {
    m_database.LinkMovieToTvshow(m_vecItems->Get(itemnumber)->GetVideoInfoTag()->m_iDbId,
                                 list[iSelectedLabel]->GetVideoInfoTag()->m_iDbId, bRemove);
    CUtil::DeleteVideoDatabaseDirectoryCache();
  }
}