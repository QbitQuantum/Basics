//  Add an "* All ..." folder to the CFileItemList
//  depending on the child node
void CDirectoryNode::AddQueuingFolder(CFileItemList& items) const
{
  CFileItemPtr pItem;

  // always show "all" items by default
  if (!CSettings::Get().GetBool(CSettings::SETTING_VIDEOLIBRARY_SHOWALLITEMS))
    return;

  // no need for "all" item when only one item
  if (items.GetObjectCount() <= 1)
    return;

  CVideoDbUrl videoUrl;
  if (!videoUrl.FromString(BuildPath()))
    return;

  // hack - as the season node might return episodes
  unique_ptr<CDirectoryNode> pNode(ParseURL(items.GetPath()));

  switch (pNode->GetChildType())
  {
    case NODE_TYPE_SEASONS:
      {
        std::string strLabel = g_localizeStrings.Get(20366);
        pItem.reset(new CFileItem(strLabel));  // "All Seasons"
        videoUrl.AppendPath("-1/");
        pItem->SetPath(videoUrl.ToString());
        // set the number of watched and unwatched items accordingly
        int watched = 0;
        int unwatched = 0;
        for (int i = 0; i < items.Size(); i++)
        {
          CFileItemPtr item = items[i];
          watched += (int)item->GetProperty("watchedepisodes").asInteger();
          unwatched += (int)item->GetProperty("unwatchedepisodes").asInteger();
        }
        pItem->SetProperty("totalepisodes", watched + unwatched);
        pItem->SetProperty("numepisodes", watched + unwatched); // will be changed later to reflect watchmode setting
        pItem->SetProperty("watchedepisodes", watched);
        pItem->SetProperty("unwatchedepisodes", unwatched);
        if (items.Size() && items[0]->GetVideoInfoTag())
        {
          *pItem->GetVideoInfoTag() = *items[0]->GetVideoInfoTag();
          pItem->GetVideoInfoTag()->m_iSeason = -1;
        }
        pItem->GetVideoInfoTag()->m_strTitle = strLabel;
        pItem->GetVideoInfoTag()->m_iEpisode = watched + unwatched;
        pItem->GetVideoInfoTag()->m_playCount = (unwatched == 0) ? 1 : 0;
        CVideoDatabase db;
        if (db.Open())
        {
          pItem->GetVideoInfoTag()->m_iDbId = db.GetSeasonId(pItem->GetVideoInfoTag()->m_iIdShow, -1);
          db.Close();
        }
        pItem->GetVideoInfoTag()->m_type = MediaTypeSeason;
      }
      break;
    case NODE_TYPE_MUSICVIDEOS_ALBUM:
      pItem.reset(new CFileItem(g_localizeStrings.Get(15102)));  // "All Albums"
      videoUrl.AppendPath("-1/");
      pItem->SetPath(videoUrl.ToString());
      break;
    default:
      break;
  }

  if (pItem)
  {
    pItem->m_bIsFolder = true;
    pItem->SetSpecialSort(g_advancedSettings.m_bVideoLibraryAllItemsOnBottom ? SortSpecialOnBottom : SortSpecialOnTop);
    pItem->SetCanQueue(false);
    items.Add(pItem);
  }
}