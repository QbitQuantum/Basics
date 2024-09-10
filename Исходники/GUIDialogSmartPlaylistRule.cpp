void CGUIDialogSmartPlaylistRule::OnBrowse()
{
  CFileItemList items;
  CMusicDatabase database;
  database.Open();
  CVideoDatabase videodatabase;
  videodatabase.Open();

  std::string basePath;
  if (CSmartPlaylist::IsMusicType(m_type))
    basePath = "musicdb://";
  else
    basePath = "videodb://";

  VIDEODB_CONTENT_TYPE type = VIDEODB_CONTENT_MOVIES;
  if (m_type == "movies")
    basePath += "movies/";
  else if (m_type == "tvshows")
  {
    type = VIDEODB_CONTENT_TVSHOWS;
    basePath += "tvshows/";
  }
  else if (m_type == "musicvideos")
  {
    type = VIDEODB_CONTENT_MUSICVIDEOS;
    basePath += "musicvideos/";
  }
  else if (m_type == "episodes")
  {
    if (m_rule.m_field == FieldGenre || m_rule.m_field == FieldYear ||
        m_rule.m_field == FieldStudio)
      type = VIDEODB_CONTENT_TVSHOWS;
    else
      type = VIDEODB_CONTENT_EPISODES;
    basePath += "tvshows/";
  }

  int iLabel = 0;
  if (m_rule.m_field == FieldGenre)
  {
    if (m_type == "tvshows" ||
        m_type == "episodes" ||
        m_type == "movies")
      videodatabase.GetGenresNav(basePath + "genres/", items, type);
    else if (m_type == "songs" ||
             m_type == "albums" ||
             m_type == "artists" ||
             m_type == "mixed")
      database.GetGenresNav("musicdb://genres/",items);
    if (m_type == "musicvideos" ||
        m_type == "mixed")
    {
      CFileItemList items2;
      videodatabase.GetGenresNav("videodb://musicvideos/genres/",items2,VIDEODB_CONTENT_MUSICVIDEOS);
      items.Append(items2);
    }
    iLabel = 515;
  }
  else if (m_rule.m_field == FieldCountry)
  {
    videodatabase.GetCountriesNav(basePath, items, type);
    iLabel = 574;
  }
  else if (m_rule.m_field == FieldArtist || m_rule.m_field == FieldAlbumArtist)
  {
    if (CSmartPlaylist::IsMusicType(m_type))
      database.GetArtistsNav("musicdb://artists/", items, m_rule.m_field == FieldAlbumArtist, -1);
    if (m_type == "musicvideos" ||
        m_type == "mixed")
    {
      CFileItemList items2;
      videodatabase.GetMusicVideoArtistsByName("", items2);
      items.Append(items2);
    }
    iLabel = 557;
  }
  else if (m_rule.m_field == FieldAlbum)
  {
    if (CSmartPlaylist::IsMusicType(m_type))
      database.GetAlbumsNav("musicdb://albums/", items);
    if (m_type == "musicvideos" ||
        m_type == "mixed")
    {
      CFileItemList items2;
      videodatabase.GetMusicVideoAlbumsByName("", items2);
      items.Append(items2);
    }
    iLabel = 558;
  }
  else if (m_rule.m_field == FieldActor)
  {
    videodatabase.GetActorsNav(basePath + "actors/",items,type);
    iLabel = 20337;
  }
  else if (m_rule.m_field == FieldYear)
  {
    if (CSmartPlaylist::IsMusicType(m_type))
      database.GetYearsNav("musicdb://years/", items);
    if (CSmartPlaylist::IsVideoType(m_type))
    {
      CFileItemList items2;
      videodatabase.GetYearsNav(basePath + "years/", items2, type);
      items.Append(items2);
    }
    iLabel = 562;
  }
  else if (m_rule.m_field == FieldDirector)
  {
    videodatabase.GetDirectorsNav(basePath + "directors/", items, type);
    iLabel = 20339;
  }
  else if (m_rule.m_field == FieldStudio)
  {
    videodatabase.GetStudiosNav(basePath + "studios/", items, type);
    iLabel = 572;
  }
  else if (m_rule.m_field == FieldWriter)
  {
    videodatabase.GetWritersNav(basePath, items, type);
    iLabel = 20417;
  }
  else if (m_rule.m_field == FieldTvShowTitle ||
          (m_type == "tvshows" && m_rule.m_field == FieldTitle))
  {
    videodatabase.GetTvShowsNav(basePath + "titles/", items);
    iLabel = 20343;
  }
  else if (m_rule.m_field == FieldTitle)
  {
    if (m_type == "songs" || m_type == "mixed")
    {
      database.GetSongsNav("musicdb://songs/", items, -1, -1, -1);
      iLabel = 134;
    }
    if (m_type == "movies")
    {
      videodatabase.GetMoviesNav(basePath + "titles/", items);
      iLabel = 20342;
    }
    if (m_type == "episodes")
    {
      videodatabase.GetEpisodesNav(basePath + "titles/-1/-1/", items);
      // we need to replace the db label (<season>x<episode> <title>) with the title only
      CLabelFormatter format("%T", "");
      for (int i = 0; i < items.Size(); i++)
        format.FormatLabel(items[i].get());
      iLabel = 20360;
    }
    if (m_type == "musicvideos" || m_type == "mixed")
    {
      videodatabase.GetMusicVideosNav(basePath + "titles/", items);
      iLabel = 20389;
    }
  }
  else if (m_rule.m_field == FieldPlaylist || m_rule.m_field == FieldVirtualFolder)
  {
    // use filebrowser to grab another smart playlist

    // Note: This can cause infinite loops (playlist that refers to the same playlist) but I don't
    //       think there's any decent way to deal with this, as the infinite loop may be an arbitrary
    //       number of playlists deep, eg playlist1 -> playlist2 -> playlist3 ... -> playlistn -> playlist1
    if (CSmartPlaylist::IsVideoType(m_type))
      XFILE::CDirectory::GetDirectory("special://videoplaylists/", items, ".xsp", XFILE::DIR_FLAG_NO_FILE_DIRS);
    if (CSmartPlaylist::IsMusicType(m_type))
    {
      CFileItemList items2;
      XFILE::CDirectory::GetDirectory("special://musicplaylists/", items2, ".xsp", XFILE::DIR_FLAG_NO_FILE_DIRS);
      items.Append(items2);
    }

    for (int i = 0; i < items.Size(); i++)
    {
      CFileItemPtr item = items[i];
      CSmartPlaylist playlist;
      // don't list unloadable smartplaylists or any referencable smartplaylists
      // which do not match the type of the current smartplaylist
      if (!playlist.Load(item->GetPath()) ||
         (m_rule.m_field == FieldPlaylist &&
         (!CSmartPlaylist::CheckTypeCompatibility(m_type, playlist.GetType()) ||
         (!playlist.GetGroup().empty() || playlist.IsGroupMixed()))))
      {
        items.Remove(i);
        i -= 1;
        continue;
      }

      if (!playlist.GetName().empty())
        item->SetLabel(playlist.GetName());
    }
    iLabel = 559;
  }
  else if (m_rule.m_field == FieldPath)
  {
    VECSOURCES sources;
    if (m_type == "songs" || m_type == "mixed")
      sources = *CMediaSourceSettings::GetInstance().GetSources("music");
    if (CSmartPlaylist::IsVideoType(m_type))
    {
      VECSOURCES sources2 = *CMediaSourceSettings::GetInstance().GetSources("video");
      sources.insert(sources.end(),sources2.begin(),sources2.end());
    }
    g_mediaManager.GetLocalDrives(sources);
    
    std::string path = m_rule.GetParameter();
    CGUIDialogFileBrowser::ShowAndGetDirectory(sources, g_localizeStrings.Get(657), path, false);
    if (m_rule.m_parameter.size() > 0)
      m_rule.m_parameter.clear();
    if (!path.empty())
      m_rule.m_parameter.push_back(path);

    UpdateButtons();
    return;
  }
  else if (m_rule.m_field == FieldSet)
  {
    videodatabase.GetSetsNav("videodb://movies/sets/", items, VIDEODB_CONTENT_MOVIES);
    iLabel = 20434;
  }
  else if (m_rule.m_field == FieldTag)
  {
    VIDEODB_CONTENT_TYPE type = VIDEODB_CONTENT_MOVIES;
    if (m_type == "tvshows" ||
        m_type == "episodes")
      type = VIDEODB_CONTENT_TVSHOWS;
    else if (m_type == "musicvideos")
      type = VIDEODB_CONTENT_MUSICVIDEOS;
    else if (m_type != "movies")
      return;

    videodatabase.GetTagsNav(basePath + "tags/", items, type);
    iLabel = 20459;
  }
  else
  { // TODO: Add browseability in here.
    assert(false);
  }

  // sort the items
  items.Sort(SortByLabel, SortOrderAscending, CSettings::GetInstance().GetBool(CSettings::SETTING_FILELISTS_IGNORETHEWHENSORTING) ? SortAttributeIgnoreArticle : SortAttributeNone);

  CGUIDialogSelect* pDialog = (CGUIDialogSelect*)g_windowManager.GetWindow(WINDOW_DIALOG_SELECT);
  pDialog->Reset();
  pDialog->SetItems(&items);
  std::string strHeading = StringUtils::Format(g_localizeStrings.Get(13401).c_str(), g_localizeStrings.Get(iLabel).c_str());
  pDialog->SetHeading(CVariant{std::move(strHeading)});
  pDialog->SetMultiSelection(m_rule.m_field != FieldPlaylist && m_rule.m_field != FieldVirtualFolder);

  if (!m_rule.m_parameter.empty())
    pDialog->SetSelected(m_rule.m_parameter);

  pDialog->Open();
  if (pDialog->IsConfirmed())
  {
    m_rule.m_parameter.clear();
    for (int i : pDialog->GetSelectedItems())
      m_rule.m_parameter.push_back(items.Get(i)->GetLabel());

    UpdateButtons();
  }
  pDialog->Reset();
}